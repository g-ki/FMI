import random


class BooleanChromosome():
  def __init__(self, chromosome):
    self._chromosome = chromosome


  @classmethod
  def random(cls, lenght):
    chromosome = [random.randint(0, 1) for i in range(lenght)]
    return cls(chromosome)


  def mutate(self, prob):
    for i,val in enumerate(self._chromosome):
      if random.random() <= prob:
        self._chromosome[i] = 1 - val # flip


  def __len__(self):
    return len(self._chromosome)


  def __str__(self):
    return str(self._chromosome)


  def crossover(self, other):
    rand_index = random.choice(range(len(self)))

    self_left, self_right = self._chromosome[:rand_index], self._chromosome[:rand_index]
    other_left, other_right = other._chromosome[:rand_index], other._chromosome[:rand_index]

    self_class = self.__class__

    return (self_class(self_left + other_right), self_class(other_left + self_right))


  def __add__(self, other):
    return self.crossover(other)

  def fitness(self):
    pass


class Knapsack():
  def __init__(self, capacity, chromosome):
    self._chromosome = BooleanChromosome(chromosome)
    self._capacity = capacity


  def value(self, values):
    return sum([x*v for x,v in zip(self._chromosome, values)])


  def weight(self, weights):
    return sum([x*w for x,w in zip(self._chromosome, weights)])


  def fitness(self, values, weights):
    if self.weight(weights) > self._capacity:
      return 0

    return self.value(values)


  @classmethod
  def random(cls, capacity, lenght):
    chromosome = [random.randint(0, 1) for i in range(lenght)]
    return cls(capacity, chromosome)


def pick_index(array):
  # array_sum = sum(array)
  # if array_sum != 1:
  #   norm_array = [el / array_sum for el in array]

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
      offspring_a, offspring_b = parent_a.crossover(parent_b)
      parent_a = offspring_a
      parent_b = offspring_b

    # mutate
    parent_a.mutate(mut_prob)
    parent_b.mutate(mut_prob)

    new_population.append(parent_a)
    new_population.append(parent_b)

  return new_population


def random_population(size, capacity, lenght):
  return [Knapsack.random(capacity, lenght) for i in range(size)]


def max_n_indices(array, n):
  return [i for i,val in sorted(enumerate(array), key=lambda el: el[1])[:n]]


def main(population_size, values, weights, cross_prob, mut_prob, max_iter=1000):
  # init random population
  population = random_population(population_size, 5000, len(values))

  for i in range(max_iter):
    # evaluate the population
    fitness = [k.fitness(values, weights) for k in population]
    population_fitness = sum(fitness)
    print(population_fitness, 'avg_fitness', population_fitness / len(population))

    # show the best knapsacks
    print('top 5 knapsacks')
    top_indices = max_n_indices(fitness, 5)
    for index in top_indices:
      print(population[index], fitness[index])

    population = next_population(population, fitness, cross_prob, mut_prob)



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
    ('T-shirt',240,150),
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

  main(40, values, weights, cross_prob=0.7, mut_prob=0.001)







