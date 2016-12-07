#ifndef W_GRAPH_2_HPP
#define W_GRAPH_2_HPP

#include "graph.hpp"

namespace std {
  template <typename T, typename U> struct hash<pair<T, U>> {
    typedef pair<T, U> argument_type;
    typedef std::size_t result_type;
    result_type operator()(argument_type const& s) const
    {
      result_type const h1 ( std::hash<T>()(s.first) );
      result_type const h2 ( std::hash<U>()(s.second) );
      return h1 ^ (h2 << 1);
    }
  };
}

namespace graph {

  template <typename Vertex>
  class WGraph : public Graph<Vertex> {
  protected:
    unordered_map<pair<Vertex, Vertex>, double> _weight;

  public:

    double weight(const Vertex& x, const Vertex& y) const {
      return _weight.at(make_pair(x, y));
    }

    void weight(const Vertex& x, const Vertex& y, double w) {
      _weight[make_pair(x, y)] = w;
    }

    void add_edge(const Vertex& x, const Vertex& y, double w) {
      weight(x, y, w);
      Graph<Vertex>::add_edge(x, y);
    }

    void remove_edge(const Vertex& x, const Vertex& y) {
      _weight.erase(make_pair(x, y));
      Graph<Vertex>::remove_edge(x, y);
    }

    void remove_vertex(const Vertex& x) {

      Graph<Vertex>::for_each_vertex([this, &x](const Vertex& y){
        if (this->adjacent(x, y))
          this->_weight.erase(make_pair(x, y));
        else if (this->adjacent(y, x))
          this->_weight.erase(make_pair(y, x));
      });

      Graph<Vertex>::remove_vertex(x);
    }

  };
}
#endif
