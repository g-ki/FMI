#ifndef GRAPH_ALGO_HPP
#define GRAPH_ALGO_HPP


#include "graph.hpp"
#include "weight_graph.hpp"

#include <stack>
#include <queue>
#include <list>
#include <unordered_set>
#include <unordered_map>

namespace graph {

  template <typename T>
  bool has_path(const Graph<T>& g, const T& a, const T& b) {
    stack<T> s;
    unordered_set<T> visited;

    s.push(a);

    while (!s.empty()) {
      T current = s.top(); s.pop();

      if (current == b) return true;

      if (visited.find(current) == visited.end()) {
        visited.insert(current);

        g.for_each_neighbor_of(current, [&s](const T& v) { s.push(v); });
      }
    }

    return false;
  }

  template <typename T>
  list<T> shortest_path(const WGraph<T> g, const T& a, const T& b) {
    list<T> path;
    unordered_map<T, double> distance;
    unordered_map<T, T> prev;

    typedef pair<double, T> queue_el;
    priority_queue<queue_el, vector<queue_el>, greater<queue_el> > Q;
    unordered_set<T> inQ;

    distance[a] = 0;

    Q.push(make_pair(0, a));
    inQ.insert(a);

    g.for_each_vertex([&a, &distance, &prev, &Q](const T& v){
      if (a != v) {
        distance[v] = HUGE_VAL;
        prev[v] = T();
      }
    });

    while (!Q.empty()) {
      T u = Q.top().second;
      inQ.erase(u);
      Q.pop();

      if (u == b) { // recover path
        while ( prev[u] != T()) {
          path.push_front(u);
          u = prev[u];
        }
        path.push_front(u);
        return path;
      }

      g.for_each_neighbor_of(u, [&](const T& v) {
        double new_dist = distance[u] + g.weight(u, v);

        if (new_dist < distance[v]) {
          distance[v] = new_dist;
          prev[v] = u;

          if (inQ.find(v) == inQ.end()) {
            Q.push(make_pair(new_dist, v));
            inQ.insert(v);
          }
        }
      }); // for_each_neighbor_of

    } // while (!Q.empty())

    return path;
  }



  template <typename T>
  bool has_cycle_from(const Graph<T>& g, const T& a) {
    stack<T> s;
    unordered_set<T> visited;

    visited.insert(a);
    g.for_each_neighbor_of(a, [&s](const T& v) { s.push(v); });

    while (!s.empty()) {
      T current = s.top(); s.pop();

      if (a == current) return true;

      if (visited.find(current) == visited.end()) {
        visited.insert(current);

        g.for_each_neighbor_of(current, [&s](const T& v) { s.push(v); });
      }
    }

    return false;
  }

  template <typename T>
  bool all_reachable_from(const Graph<T>& g, const T& a) {
    stack<T> s;
    unordered_set<T> visited;

    s.push(a);

    while (!s.empty()) {
      T current = s.top(); s.pop();

      if (visited.find(current) == visited.end()) {
        visited.insert(current);

        g.for_each_neighbor_of(current, [&s](const T& v) { s.push(v); });
      }
    }

    return visited.size() == g.vertex_count();
  }

  template <typename T>
  list<pair<T, T>> dead_ends(const Graph<T>& g) {
    list<pair<T, T>> dead;

    g.for_each_vertex([&g, &dead](const T& v) {
      g.for_each_neighbor_of(v, [&g, &dead, &v](const T& u){
        if (g.neighbors(u).size() == 0)
          dead.push_back(make_pair(v, u));
      });
    });

    return dead;
  }

  template <typename T>
  list<T> eulerian_path(Graph<T> g) {
    
    bool is_cycle = true, is_path = true;
    int diff_count = 0;
    g.for_each_vertex([&g, &is_cycle, &is_path, &diff_count](const T& v) {
      int degree_diff = g.in_degree(v) - g.out_degree(v);

      if (is_cycle && degree_diff != 0)
          is_cycle = false;

      if (is_path && degree_diff != 0) {
        ++diff_count;
        if (diff_count > 2 || (degree_diff != -1 && degree_diff != 1))
          is_path = false;
      }
    });

    if (diff_count < 2) is_path = false;

    if (!is_cycle && !is_path)
      return list<T>();

    T current;

    if (is_cycle)
      current = g.graph().begin()->first;
    else
      g.for_each_vertex([&g, &current](const T& v) {
        int degree_diff = g.in_degree(v) - g.out_degree(v);
        if (degree_diff == -1)
          current = v;
      });

    stack<T> st;
    list<T> path;

    while (!g.neighbors(current).empty() || !st.empty()) {
      if (g.neighbors(current).empty()) {
        path.push_front(current);
        current = st.top(); st.pop();
      } else {
        st.push(current);
        T next = *(g.neighbors(current).begin());
        g.remove_edge(current, next);
        current = next;
      }
    }

    path.push_front(current);

    return path;
  }
}
#endif
