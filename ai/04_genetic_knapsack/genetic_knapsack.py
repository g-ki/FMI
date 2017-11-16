import random


def random_chromosome(lenght):
  return [random.randint(0, 1) for i in range(lenght)]


def random_population(size, lenght):
  return [random_chromosome(lenght) for i in range(size)]


def crossover(chromosome_a, chromosome_b):
  rand_index = random.choice(range(len(chromosome_a)))

  a_left, a_right = chromosome_a[:rand_index], chromosome_a[rand_index:]
  b_left, b_right = chromosome_b[:rand_index], chromosome_b[rand_index:]

  return (a_left + b_right, b_left + a_right)


def mutate(chromosome, prob):
  result = []
  for val in chromosome:
    mutated_val = 1 - val if random.random() <= prob else val
    result.append(mutated_val)

  return result


def pick_index(array):
  rand_num = random.random()
  index = 0

  while rand_num > 0:
    rand_num -= array[index]
    index += 1

  return index - 1


def next_population(population, fitness, cross_prob, mut_prob):
  sum_fitness = sum(fitness)
  normed_fitness = [f / sum_fitness for f in fitness]

  new_population = []
  while len(new_population) < len(population):
    # select
    parent_a = population[pick_index(normed_fitness)]
    parent_b = population[pick_index(normed_fitness)]

    # crossover
    if random.random() <= cross_prob:
      offspring_a, offspring_b = crossover(parent_a, parent_b)
      parent_a = offspring_a
      parent_b = offspring_b

    # mutate
    parent_a = mutate(parent_a, mut_prob)
    parent_b = mutate(parent_b, mut_prob)

    new_population.append(parent_a)
    new_population.append(parent_b)

  return new_population


def chromosome_sum(chromosome, values):
  return sum([x * val for x,val in zip(chromosome, values)])


def knapsack_fitness(chromosome, capacity, values, weights):
  weight = chromosome_sum(chromosome, weights)
  if weight > capacity:
    return 0

  return chromosome_sum(chromosome, values)


def max_n_indices(array, n):
  sorted_array = sorted(enumerate(array), key=lambda el: el[1], reverse=True)
  return [i for i,val in sorted_array[:n]]


def main(population_size, values, weights, cross_prob, mut_prob, max_iter=1000):
  # init random population
  capacity = 5000
  population = random_population(population_size, len(values))

  best_solution = population[0]
  best_solution_fitness = knapsack_fitness(best_solution, capacity, values, weights)

  for i in range(max_iter):
    # evaluate the population
    fitness = [knapsack_fitness(k, capacity, values, weights) for k in population]

    max_index = max(enumerate(fitness), key=lambda e_f: e_f[1])[0]
    current_best = population[max_index]
    current_best_fitness = fitness[max_index]

    if best_solution_fitness < current_best_fitness:
      best_solution = current_best
      best_solution_fitness = current_best_fitness

    population = next_population(population, fitness, cross_prob, mut_prob)


  return best_solution


if __name__ == '__main__':
  items = [
    ('map',90,150),
    ('compass',130,35),
    ('water',1530,200),
    ('sandwich',500,160),
    ('glucose',150,60),
    ('tin',680,45),
    ('banana',270,60),
    ('apple',390,40),
    ('cheese',230,30),
    ('beer',520,10),
    ('suntan cream', 110, 70),
    ('camera',320,30),
    ('T-shirt',240,15),
    ('trousers',480,10),
    ('umbrella',730,40),
    ('waterproof trousers',420,70),
    ('waterproof overclothes',430,75),
    ('note-case',220,80),
    ('sunglasses',70,20),
    ('towel',180,12),
    ('socks',40,50),
    ('book',300,10),
    ('notebook',900,1),
    ('tent',2000,150)
  ]
  weights = [item[1] for item in items]
  values = [item[2] for item in items]

  solution = main(46, values, weights, cross_prob=0.7, mut_prob=0.01, max_iter=100)

  solution_fitness = knapsack_fitness(solution, 5000, values, weights)
  solution_weight = chromosome_sum(solution, weights)

  for index,item in enumerate(solution):
    if item == 1:
      print(index, items[index][0])

  print('-----------------')
  print('weight', solution_weight, solution_weight / 5000)
  print('value', solution_fitness, solution_fitness / sum(values))
