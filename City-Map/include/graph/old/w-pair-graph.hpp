#ifndef PAIR_GRAPH_HPP
#define PAIR_GRAPH_HPP

#include <unordered_map>
#include <unordered_set>
#include <iostream>
using namespace std;


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

template <typename Vertex>
class Graph {
private:
  typedef unordered_set<pair<Vertex, double>> vertexSet;
  unordered_map<Vertex, vertexSet> table;
public:

  typedef typename vertexSet::iterator adjecent_iterator;
  typedef pair<adjecent_iterator, adjecent_iterator> vertex_set;


  bool adjacent(const Vertex& x, const Vertex& y) {
      auto x_y = table.at(x).find(y);
      return x_y != table.at(x).end();
  }

  vertex_set neighbors(const Vertex& x) {
    return make_pair(table.at(x).begin(), table.at(x).end());
  }

  void add_vertex(const Vertex& x) {
    table.insert(make_pair(x, vertexSet()));
  }

  void remove_vertex(const Vertex& x) {
    for(auto it = table.begin(); it != table.end(); ++it)
      it->second.erase(x);

    table.erase(x);
  }

  void add_edge(const Vertex& x, const Vertex& y, double w) {
    table.at(x).insert(make_pair(y, w));
  }

  void remove_edge(const Vertex& x, const Vertex& y)
  {
    vertexSet& s = table.at(x);
    for (auto it = s.begin(); it != s.end(); ++it)
      if (it->first == y)
        s.erase(it);
  }
};
#endif
