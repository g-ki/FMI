#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <unordered_set>

using namespace std;
namespace graph {

  template <typename Vertex>
  class Graph {
  protected:
    unordered_map<Vertex, unordered_set<Vertex>> table;
  public:

    typedef unordered_set<Vertex> vertexSet;
    typedef unordered_map<Vertex, vertexSet> vertexTable;
    typedef typename vertexTable::iterator vertex_table_iterator;
    typedef typename vertexSet::iterator vertex_set_iterator;

    const vertexTable& graph() const {
      return table;
    }

    // vertex methods

    template <typename Function>
    void for_each_vertex(Function fn) const {
      // vertex_table_iterator ...
      auto first = table.begin(), last = table.end();

      while (first != last) {
        fn (first->first);
        ++first;
      }
    }

    template <typename Function>
    void for_each_neighbor_of(const Vertex& x , Function fn) const {
      vertex_set_iterator first = table.at(x).begin(),
                          last  = table.at(x).end();

      while (first != last) {
        fn (*first);
        ++first;
      }
    }

    size_t vertex_count() const {
      return table.size();
    }

    void add_vertex(const Vertex& x) {
      table.insert(make_pair(x, vertexSet()));
    }

    void remove_vertex(const Vertex& x) {
      for(auto it = table.begin(); it != table.end(); ++it)
        it->second.erase(x);

      table.erase(x);
    }

    bool has_vertex(const Vertex& x) const {
      return table.find(x) != table.end();
    }

    bool adjacent(const Vertex& x, const Vertex& y) const {
        return table.at(x).find(y) != table.at(x).end();
    }

    int out_degree(const Vertex& x) const {
      return table.at(x).size();
    }

    int in_degree(const Vertex& x) const  {
      int _degree = 0;
      for_each_vertex([&x, &_degree, this](const Vertex& y) {
        if (y != x)
          _degree += this->table.at(y).count(x);
      });
      return _degree;
    }

    int degree(const Vertex& x) const {
      return in_degree(x) + out_degree(x);
    }

    const vertexSet& neighbors(const Vertex& x) const {
      return table.at(x);
    }

    // edge methods

    void add_edge(const Vertex& x, const Vertex& y) {
      table.at(x).insert(y);
    }

    void remove_edge(const Vertex& x, const Vertex& y) {
      table.at(x).erase(y);
    }

    size_t edge_count() const {
      size_t sum = 0;
      for_each_vertex([&sum, this](const Vertex& v){
        sum += this->neighbors(v).size();
      });
      return sum;
    }

    void clear() {
      table.clear();
    }

  };
}
#endif
