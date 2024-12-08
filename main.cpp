#include "TSP.hpp"
#include "Time.hpp"
#include <iostream>

int main() {
  std::string filename = "test_data/mu1979.tsp";
  std::list<Node> cities = TSP::constructCities(filename);
  auto result = Time::timeAndExecute<TSP::Tour, std::list<Node>, size_t>(TSP::nearestNeighbor, cities, 1022);
  // result.summarize();

  return 0;
}