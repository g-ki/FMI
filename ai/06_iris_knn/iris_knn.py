import csv
import random

# string -> [dict]
def read_data(path):
  with open(path, 'r') as csvfile:
    reader = csv.DictReader(csvfile, delimiter=',')
    for row in reader:
      yield row


# [_], int -> ([_], [_])
def train_test_split(data, test_size):
  suffled_data = random.sample(data, len(data))
  train = suffled_data[test_size:]
  test = suffled_data[:test_size]

  return train, test


# [_], distance(_,_), label(_) -> model([_], int)
def knn(data, distance, label):
  # [_], int -> [label(_)]
  def knn_model(predict, k):
    for p_el in predict:
      el_dist = [distance(p_el, d_el) for d_el in data] # compute distance
      k_neighbours = sorted(zip(data, el_dist), key=lambda i: i[1])[:k] # get k-nearest neighbors
      hist = {}
      for n,_ in k_neighbours:
        hist[label(n)] = hist.get(label(n), 0) + 1 # count k-nearest labels

      yield max(hist.items(), key=lambda e: e[1])[0] # return label with max value

  return knn_model


# [_], [_] -> float
def score(values, predicted):
  matches = [v == p for v,p in zip(values, predicted)]
  return matches.count(True) / len(values)


# dict, dict -> float
def iris_distance(a, b):
  keys = ['SepalLengthCm', 'SepalWidthCm', 'PetalLengthCm', 'PetalWidthCm']
  dist = lambda key: (float(a[key]) - float(b[key]))**2

  return sum([dist(k) for k in keys])

# dict -> string
def iris_label(x):
  return x['Species']


if __name__ == '__main__':
  dataset = list(read_data('./data.csv'))
  train, test = train_test_split(dataset, test_size=20)

  model = knn(train, iris_distance, iris_label)
  labels = list(model(test, k=2))

  for t,predicted_label in zip(test, labels):
    print('Id:', t['Id'], 'is', predicted_label)

  true_labels = list(map(iris_label, test))
  print('Accuracy: %f' % score(true_labels, labels))
