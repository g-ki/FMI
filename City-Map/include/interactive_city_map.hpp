#ifndef INTERACTIVE_CITY_MAP
#define INTERACTIVE_CITY_MAP

#include "city_map.hpp"
#include <iostream>


class InteractiveCityMap : public CityMap {
public:

  void loaction() const;
  void change(const Crossroad&);

  void neighbours() const;

  void move(const Crossroad&);

  void close(const Crossroad&);
  void open(const Crossroad&);

  void closed() const;

  void tour() const;

private:
  Crossroad current_location;
  StreetMap closed_map;
  unordered_set<Crossroad> closed_crossreads;
};

#endif
