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

#define MAX_THREADS 128
typedef std::chrono::milliseconds ms;
bool quite_mode = false;
const mpz_class C3_OVER_24 = -262537412640768000;
unsigned prec = 1000;


struct bs_pi {
  mpz_class P, Q, T;
};

void combine(const bs_pi& am, const bs_pi& mb, bs_pi& ab) {
  ab.P = am.P * mb.P;
  ab.Q = am.Q * mb.Q;
  ab.T = mb.Q * am.T + am.P * mb.T;
}

// factorial
bs_pi bs_chudnovsky(const mpz_class& a, const mpz_class& b) {
  struct bs_pi ab;

  if (b - a == 1) {
    if (a == 0) {
      ab.P = ab.Q = 1;
    } else {
      ab.P = (6*a-5)*(2*a-1)*(6*a-1);
      ab.Q = a*a*a*C3_OVER_24;
    }
    ab.T = ab.P * (13591409 + 545140134*a);
    if (a.get_ui() & 1)
      ab.T = -ab.T;
  } else {
    // m is the midpoint of a and b
    mpz_class m = (a + b) / 2;
    // Recursively calculate [a, m]
    struct bs_pi am = bs_chudnovsky(a, m);
    // Recursively calculate [m, b]
    struct bs_pi mb = bs_chudnovsky(m, b);
    // combine
    combine(am, mb, ab);
  }

  return ab;
}
// chudnovsky ******
struct thread_data {
  int thread_id;
  mpz_class a, b;
  mpf_class result;
};

void *worker(void *threadarg) {
  struct thread_data *data;
  data = (struct thread_data *) threadarg;

  if (!quite_mode)
    cout << "Thread-" << data->thread_id << " started." << endl;

  auto start = std::chrono::steady_clock::now();

  bs_pi r = bs_chudnovsky(data->a, data->b); // work is done here

  data->result = mpf_class(r.T, prec) / mpf_class(r.Q, prec);

  // if (!quite_mode) {
    auto end = std::chrono::steady_clock::now();
    chrono::duration<double> diff = end - start;
    ms d = std::chrono::duration_cast<ms>(diff);
    cout << "Thread-" << data->thread_id << " stopped. (" << d.count() << "ms)" << endl;
  // }

  pthread_exit(NULL);
}

void setup_threads_data(thread_data* td, const int num_threads, int N) {
  unsigned size = N / num_threads;
  for(int i = 0; i < num_threads; ++i ) {
    td[i].thread_id = i;
    td[i].a = i*size;
    td[i].b = i*size + size;
    td[i].result.set_prec(prec);
  }
}

void start_threads(pthread_t* const threads, thread_data* const td, const int num_threads, pthread_attr_t* const joinable_attr = NULL) {
  int rc;

  for(int i = 0; i < num_threads; ++i ) {
    rc = pthread_create(&threads[i], joinable_attr, worker, (void *)&td[i]);

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
  bs_pi ab, r;
  // ab = td[0].result;
  mpf_class s(0, prec);
  for(int i = 0; i < num_threads; ++i ) {
    // combine(ab, td[i].result, r);
    // ab = r;
    s += td[i].result;
  }

  mpf_class f_sqrt;
  f_sqrt.set_prec(prec);
  mpf_sqrt_ui(f_sqrt.get_mpf_t(), 10005);

  mpf_class pi = (426880 * f_sqrt) / s;
  return pi;
}

int main(int argc, char **argv) {

  cxxopts::Options options("Chudnovsky PI", "Pi computed by Chudnovsky Algorithm using many threads");
  options.add_options()
    ("p,precision", "Number of interations", cxxopts::value<unsigned>()->default_value("64"))
    ("t,tasks", "Number of threads", cxxopts::value<int>()->default_value("1"))
    ("o,output", "Output file", cxxopts::value<string>()->default_value("pi.txt"))
    ("q,quite", "Quite mode")
  ;
  options.parse(argc, argv);

  prec = options["precision"].as<unsigned>();
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
  start_threads(threads, td, num_threads, &joinable_attr);

  // free attribute and wait for the other threads
  pthread_attr_destroy(&joinable_attr);

  // start main thread
  join_threads(threads, num_threads); // join all but last

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
  return 0;
}
