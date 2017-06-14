#include <ctime>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <chrono>
#include <gmpxx.h>
#include <gmp.h>
#include <pthread.h>
#include "cxxopts.hpp"

using namespace std;

#define MAX_THREADS 248
typedef std::chrono::milliseconds ms;
bool quite_mode = false;

// factorial
pthread_mutex_t fact_mem_mutex = PTHREAD_MUTEX_INITIALIZER;
std::map<const unsigned, mpz_class> fact_mem;
unsigned biggest_fact = 0;
unsigned prec = 64;

mpz_class fact(const unsigned &n) {
  if (biggest_fact < n) {
    pthread_mutex_lock( &fact_mem_mutex );
      for(unsigned i = biggest_fact; i < n; ++i) {
        fact_mem[i + 1] = (i + 1) * fact_mem[i];
        if (i > prec && i % 3 != 0)
          fact_mem.erase(i);
      }
      if (biggest_fact < n)
        biggest_fact = n;
    pthread_mutex_unlock( &fact_mem_mutex );
  }

  return fact_mem[n];
}
// factorial ******

// chudnovsky
mpz_class q(const unsigned &k) {
  mpz_class a = 545140134, b = 13591409;
  return fact(6*k) * (a*k + b);
}

mpz_class t(const unsigned &k) {
  mpz_class a = 545140134, b = 13591409;
  mpz_class fk = fact(k);
  mpz_class d;
  mpz_ui_pow_ui(d.get_mpz_t(), -262537412640768000, k);

  return fact(3*k) * (fk*fk*fk) * d;
}

mpf_class sum_term(const unsigned &k, unsigned precision = 64) {
  mpf_class a(q(k), precision);
  mpf_class b(t(k), precision);
  return a / b;
}
// chudnovsky ******

// threading
struct thread_data {
  int  thread_id;
  vector<int> terms;
  mpf_class result;
};

inline void sum_from_thread_data(struct thread_data *data) {
  data->result = 0;
  for (int i=0; i < data->terms.size(); ++i)
    data->result += sum_term(data->terms[i], data->result.get_prec());
}

void *thread_sum(void *threadarg) {
  struct thread_data *data;
  data = (struct thread_data *) threadarg;

  if (!quite_mode)
    cout << "Thread-" << data->thread_id << " started." << endl;
  auto start = std::chrono::steady_clock::now();

  sum_from_thread_data(data); // work is done here

  if (!quite_mode) {
    auto end = std::chrono::steady_clock::now();
    chrono::duration<double> diff = end - start;
    ms d = std::chrono::duration_cast<ms>(diff);
    cout << "Thread-" << data->thread_id << " stopped. (" << d.count() << "ms)" << endl;
  }

  pthread_exit(NULL);
}

void setup_threads_data(thread_data* td, const int num_threads, int precision) {
  for(int i = 0; i < num_threads; ++i ) {
    td[i].thread_id = i;
    td[i].result.set_prec(precision);

    // give to each thread part of the sum terms
    for (int j=0; j < precision; ++j)
      if (j % num_threads == i)
        td[i].terms.push_back(j);
  }
}

void start_threads(pthread_t* const threads, thread_data* const td, const int num_threads, pthread_attr_t* const joinable_attr = NULL) {
  int rc;

  for(int i = 0; i < num_threads; ++i ) {
    rc = pthread_create(&threads[i], joinable_attr, thread_sum, (void *)&td[i]);

    if (rc){
       cerr << "Error: unable to create thread," << rc << endl;
       exit(-1);
    }
  }
}

void join_threads(pthread_t* const threads, const int num_threads) {
  void *status;
  int rc;

  for(int i = 0; i < num_threads; ++i ) {
    rc = pthread_join(threads[i], &status);

    if (rc){
       cerr << "Error: unable to join," << rc << endl;
       exit(-1);
    }
  }
}

mpf_class pi_from_threads_data(const thread_data* const td, const int num_threads) {
  mpf_class result_sum(0, td[0].result.get_prec());
  for(int i = 0; i < num_threads; ++i)
    result_sum += td[i].result;

  mpf_class f_sqrt;
  f_sqrt.set_prec(result_sum.get_prec());
  mpf_sqrt_ui(f_sqrt.get_mpf_t(), 10005);
  mpf_class pi = 426880 * f_sqrt / result_sum;

  return pi;
}
// threading ******

int main(int argc, char **argv) {
  fact_mem[0] = 1; // set factorial bottom

  cxxopts::Options options("Chudnovsky PI", "Pi computed by Chudnovsky Algorithm using many threads");
  options.add_options()
    ("p,precision", "Number of interations", cxxopts::value<int>()->default_value("64"))
    ("t,tasks", "Number of threads", cxxopts::value<int>()->default_value("1"))
    ("o,output", "Output file", cxxopts::value<string>()->default_value("pi.txt"))
    ("q,quite", "Quite mode")
  ;
  options.parse(argc, argv);

  prec = options["precision"].as<int>();
  const int num_threads = options["tasks"].as<int>();
  const string output_file = options["output"].as<string>();
  quite_mode = options["quite"].as<bool>();

  if (!quite_mode)
    cout << "Threads used in current run: " << num_threads << endl;

  pthread_t threads[num_threads];
  struct thread_data td[MAX_THREADS];

  // Set thread joinable
  pthread_attr_t joinable_attr;
  pthread_attr_init(&joinable_attr);
  pthread_attr_setdetachstate(&joinable_attr, PTHREAD_CREATE_JOINABLE);

  // start clock
  auto start = std::chrono::steady_clock::now();

  // fact(prec*6);
  setup_threads_data(td, num_threads, prec);
  start_threads(threads, td, num_threads - 1, &joinable_attr);

  // free attribute and wait for the other threads
  pthread_attr_destroy(&joinable_attr);

  // start main thread
  if (!quite_mode)
    cout << "Main::Thread started." << endl;
  sum_from_thread_data(&td[num_threads - 1]); // last thread is the main thread
  if (!quite_mode)
    cout << "Main::Thread stopped." << endl;
  join_threads(threads, num_threads - 1); // join all but last

  // final result
  mpf_class pi = pi_from_threads_data(td, num_threads);
  // stop clock
  typedef std::chrono::milliseconds ms;
  auto end = std::chrono::steady_clock::now();
  chrono::duration<double> diff = end - start;

  ofstream pi_file(output_file, ios::out);
  if (pi_file.is_open()) {
    pi_file.precision(prec);
    pi_file << pi;
    pi_file.close();
  }

  if (!quite_mode) {
    std::cout.precision(prec);
    cout << pi << endl;
  }

  ms d = std::chrono::duration_cast<ms>(diff);
  std::cout<<"Total execution time: "<< d.count() << "ms" << endl;

  pthread_exit(NULL);
  return 0;
}
