#ifndef WEIGHT_GRAPH_HPP
#define WEIGHT_GRAPH_HPP

#include "graph/graph.hpp"

template <typename T>
struct WVertex {
  T vertex;
  double weight;

  WVertex() {}

  WVertex(const T& v, double w = 0) : vertex(v), weight(w) {}

  bool operator==(const WVertex& other) const
  {
    return vertex == other.vertex;
  }

  bool operator!=(const WVertex& other) const
  {
    return !(*this == other.vertex);
  }

  bool operator<(const WVertex& other) const
  {
    return weight < other.weight;
  }

  operator T() const { return vertex; }

};

namespace std {

  template <typename T> struct hash<WVertex<T>> {
    typedef WVertex<T> argument_type;
    typedef std::size_t result_type;
    result_type operator()(argument_type const& s) const
    {
      result_type const h1 ( std::hash<T>()(s.vertex) );
      result_type const h2 ( std::hash<double>()(s.weight) );
      return h1 ^ (h2 << 1);
    }
  };
}

template <typename T>
class WGraph : public Graph<WVertex<T>> {
  typedef WVertex<T> vertex;
  typedef Graph<vertex> graph;

public:
  void add_edge(const T& x, const T& y, double w) {
    graph::add_edge(x, vertex(y, w));
  }


  list<T> shortest_path(const T& source, const T& finish) {
    unordered_map<T, double> dist;
    unordered_map<T, T> prev;
    priority_queue<vertex> Q;

    dist[source] = 0;

    for (auto &vert : graph::table) {
      if (source != vert.first) {
        dist[vert.first] = HUGE_VAL;
        prev[vert.first] = T();
      }
      Q.push(vertex(vert.first, dist[vert.first]));
    }


    return list<T>();
  }

};

#endif
