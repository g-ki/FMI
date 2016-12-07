#include "city_map.hpp"

bool CityMap::has_path(const Crossroad& A, const Crossroad& B) const {
  return graph::has_path(map, A, B);
}

CityMap::path CityMap::shortest_path(const Crossroad& A, const Crossroad& B) const {
  return graph::shortest_path(map, A, B);
}

CityMap::path CityMap::shortest_path(const Crossroad& A, const Crossroad& B, const path& closed) const {
  path::const_iterator it = closed.begin();
  StreetMap tmp = map;

  for(; it != closed.end(); ++it)
    tmp.remove_vertex(*it);

  return graph::shortest_path(tmp, A, B);
}

bool CityMap::short_tour(const Crossroad& A) const {
  return graph::has_cycle_from(map, A);
}

CityMap::path CityMap::full_tour() const {
  return graph::eulerian_path(map);
}

bool CityMap::is_connected(const Crossroad& A) const {
  return graph::all_reachable_from(map, A);
}

list<CityMap::street> CityMap::dead_streets() const {
  return graph::dead_ends(map);
}

void CityMap::load_map(const StreetMap& _map) {
  map = _map;
}
