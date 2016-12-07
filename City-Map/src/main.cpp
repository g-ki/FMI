#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "graph/weight_graph.hpp"
#include "graph/algorithm.hpp"

#include "interactive_city_map.hpp"

using namespace std;
using namespace graph;

template <typename T>
void load_WGraph(const char* filename, WGraph<T>& g) {
  ifstream file(filename);
  //file.imbue( std::locale("") );
  string line;

  while (getline(file, line)) {
    istringstream str(line);

    string cross_name;
    str >> cross_name;

    g.add_vertex(cross_name);
    string neighbour;
    double distance;

    while (str >> neighbour >> distance) {
      g.add_vertex(neighbour);
      g.add_edge(cross_name, neighbour, distance);
    }
  }
  file.close();
}

bool run(InteractiveCityMap& icm) {
  string command;
  cout << ">  "; cin >> command;

  if (command == "location") {
    icm.loaction();
  } else if (command == "change") {
    string value;
    cin >> value;
    icm.change(value);
  } else if (command == "neighbours") {
    icm.neighbours();
  } else if (command == "move") {
    string value;
    cin >> value;
    icm.move(value);
  } else if (command == "close") {
    string value;
    cin >> value;
    icm.close(value);
  } else if (command == "open") {
    string value;
    cin >> value;
    icm.open(value);
  } else if (command == "closed") {
    icm.closed();
  } else if (command == "tour") {
    icm.tour();
  } else if (command == "exit") {
    return 0;
  } else {
    cout << "> Wrong command <" << endl;
  }

  return 1;
}


int main(int argc, char const *argv[]) {

  //wcout.imbue( std::locale("") );

  if (argc == 4 && strcmp(argv[1], "-i") == 0) {

    WGraph<string> city_map;
    load_WGraph(argv[2], city_map);

    InteractiveCityMap im;
    im.load_map(city_map);
    im.change(argv[3]);

    while (run(im));

    return 0;
  }

  return 0;
}
