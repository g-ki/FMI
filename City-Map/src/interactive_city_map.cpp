#include "interactive_city_map.hpp"

void InteractiveCityMap::loaction() const {
  cout << "Your current loaction is "<< current_location << "." << endl;
}
void InteractiveCityMap::change(const Crossroad& A) {
  current_location = A;
  loaction();
}

void InteractiveCityMap::neighbours() const {
  unordered_set<Crossroad> n = CityMap::map.neighbors(current_location);
  if (n.empty()) {
    cout << "~ NO Neighbours ~" << endl;
    return;
  }

  cout << "~~~~Neighbours~~~~" << endl;
  for(unordered_set<Crossroad>::iterator it = n.begin(); it != n.end(); ++it)
    cout << "\t> " << *it << " : " << map.weight(current_location, *it )<< endl;
  cout << "~~~~Neighbours~~~~" << endl;
}


void InteractiveCityMap::move(const Crossroad& B) {
  path p = shortest_path(current_location, B);

  if (p.empty()) {
    cerr << "Path between " << current_location;
    cerr << " and " << B << " does not exists!!!" << endl;
    return;
  }

  cout << "~~~~~~~Path~~~~~~~" << endl;
  for (path::iterator it = p.begin(); it != p.end(); ++it)
    cout << " > " << *it;
  cout<< endl;
  cout << "~~~~~~~Path~~~~~~~" << endl;

  current_location = B;
}

void InteractiveCityMap::close(const Crossroad& A) {
  closed_crossreads.insert(A);

  StreetMap &map = this->map;
  StreetMap &closed_map = this->closed_map;

  closed_map.add_vertex(A);

  map.for_each_vertex([&A, &map, &closed_map](const Crossroad& cr) {
    if (map.adjacent(A, cr)) {
      closed_map.add_vertex(cr);
      closed_map.add_edge(A, cr, map.weight(A, cr));
      map.remove_edge(A, cr);
    }
    else if (map.adjacent(cr, A)) {
      closed_map.add_vertex(cr);
      closed_map.add_edge(cr, A, map.weight(cr, A));
      map.remove_edge(cr, A);
    }
  });
}

void InteractiveCityMap::open(const Crossroad& A) {
  closed_crossreads.erase(A);

  StreetMap &map = this->map;
  StreetMap &closed_map = this->closed_map;

  closed_map.for_each_vertex([&map, &closed_map, &A](const Crossroad& cr) {
    if (closed_map.adjacent(A, cr)) {
      map.add_edge(A, cr, closed_map.weight(A, cr));
      closed_map.remove_edge(A, cr);
    } else if (closed_map.adjacent(cr, A)) {
      map.add_edge(cr, A, closed_map.weight(cr, A));
      closed_map.remove_edge(cr, A);
    }
  });
}

void InteractiveCityMap::closed() const {

  if (closed_crossreads.empty()) {
    cout << "~ NO Closed Crossroads ~" << endl;
    return;
  }

  cout << "~Closed Crossroads~" << endl;
  unordered_set<Crossroad>::iterator it = closed_crossreads.begin();
  for (; it != closed_crossreads.end(); ++it)
    cout << "\t> " << *it << endl;
  cout << "~Closed Crossroads~" << endl;
}

void InteractiveCityMap::tour() const {
  path p = eulerian_path(map);

  if (p.empty()) {
    cout << "~ NO Tour ~" << endl;
    return;
  }

  cout << "~~~~~~~Tour~~~~~~~" << endl;
  for (path::iterator it = p.begin(); it != p.end(); ++it)
    cout << " > " << *it;
  cout<< endl;
  cout << "~~~~~~~Tour~~~~~~~" << endl;
}
