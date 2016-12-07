#ifndef CITY_MAP_HPP
#define CITY_MAP_HPP

#include <string>
#include <list>
#include "graph/weight_graph.hpp"
#include "graph/algorithm.hpp"
using namespace std;

class CityMap {
public:
  typedef string Crossroad;
  typedef graph::WGraph<Crossroad> StreetMap;
  typedef list<Crossroad> path;
  typedef pair<Crossroad, Crossroad> street;

  bool has_path(const Crossroad&, const Crossroad&) const;

  path shortest_path(const Crossroad&, const Crossroad&) const;

  path shortest_path(const Crossroad&, const Crossroad&, const path&) const;

  bool short_tour(const Crossroad&) const;

  path full_tour() const;

  bool is_connected(const Crossroad&) const;

  list<street> dead_streets() const;

  void load_map(const StreetMap&);

protected:
  StreetMap map;
};

#endif
