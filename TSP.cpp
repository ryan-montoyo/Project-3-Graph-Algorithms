#include "TSP.hpp"
#include <limits>
#include <unordered_set>
#include <algorithm>

/**
 * Displays the edges and total distance of the tour.
 * Each edge is printed in the format: "EDGE start_id -> end_id | WEIGHT: weight".
 */
void TSP::Tour::display() const {
  for (size_t i = 1; i < path.size(); i++) {
    std::cout << "EDGE " << path[i-1].id << " -> " << path[i].id << " | WEIGHT : " << weights[i] << std::endl;
  }
  std::cout << "TOTAL DISTANCE: " << total_distance << std::endl;
}

/**
 * Reads a .tsp file and constructs a list of cities as nodes.
 * The file should have a section labeled "NODE_COORD_SECTION" followed by lines with the format: ID x-coordinate y-coordinate.
 * 
 * @param filename The path to the TSP file.
 * @return A list of `Node` objects representing cities and their coordinates.
 * @throws std::runtime_error If the file cannot be read or parsed.
 * 
 * @pre The file specified by `filename` exists and follows the TSP format.
 */
std::list<Node> TSP::constructCities(const std::string& filename) {
  // Read past metadata
  std::ifstream fin(filename);
  if (fin.fail()) {
    std::cerr << "ERROR: Could not read file: " << filename << std::endl;
    throw std::runtime_error("Failed to read file. Terminating.");
  }

  std::string line;
  do { std::getline(fin, line); }
  while (line.find("NODE_COORD_SECTION"));

  // Read data from file into Node list "cities"
  std::list<Node> cities;
  size_t ID;
  double x, y;
  while (!fin.eof()){
    if (!(fin >> ID >> x >> y)) break;
    cities.push_back(Node(ID, x, y));
  }
  return cities;
}

  /**
 * Constructs a tour using the nearest neighbor heuristic for the traveling salesperson problem (TSP).
 * Starting from the city of the given ID, it iteratively visits the nearest unvisited city and returns to the start.
 *
 * @param cities A list of `Node` objects representing the cities to be visited.
 * @param start_id The unique identifier of the starting city.
 * @return A `TSP::Tour` object representing the path, edge weights, and total distance of the computed tour.
 * 
 * @pre `start_id` must be a valid city ID within the range of IDs in `cities`.
 * @note The ith weight in `weights` is the distance traveled from the previous (i-1) city to the current i city (represented by the ith city in the returned Tour.path)
 *       As such, the first weight will ALWAYS equal 0, since there is no edge from the start city to itself
 *
 */
namespace TSP {
TSP::Tour nearestNeighbor(std::list<Node> cities, const size_t& start_id) {

  // Initialize our tour object
  TSP::Tour tour;

  std::list<Node>::iterator start_it = cities.end();

  // search cities for start node
  for (auto it = cities.begin(); it != cities.end(); it++) {
    if (it->id == start_id) {
      start_it = it;
      break;  // found, so break
    }
  }

  // if not found, throw error
  if (start_it == cities.end()) {
    throw std::runtime_error("Starting node not found.");
  }


  // set current node as starting node
  Node current = *start_it;

  // add start/current to path
  tour.path.push_back(current);

  // track visited in set
  std::unordered_set<size_t> visited;  
  
  // mark current as visted
  visited.insert(current.id);

  // initialize distance as 0 
  size_t total_distance = 0;

  // first weight is 0 since the tour starts here
  tour.weights.push_back(0);  

  // visit all cities
  while (visited.size() < cities.size()) {
    // set minimum distance to a really large value
    double min_distance = std::numeric_limits<double>::max();  
    // set nearest node iterator to end 
    auto nearest_it = cities.end();                            

    // Find the nearest unvisited node
    for (auto it = cities.begin(); it != cities.end(); it++) {
      // If noed isnt visited
      if (visited.find(it->id) == visited.end()) {
        // Calculate distance to the current node
        double distance = current.distance(*it);

        //  Check if distance is smallest weve seen, if so update it
        if (distance < min_distance) {
          min_distance = distance;
          nearest_it = it;
        }
      }
    }

    // Add the nearest node to the tour
    if (nearest_it != cities.end()) {
      // Set current node to the nearest node
      current = *nearest_it;
      // Add the nearest node to the path
      tour.path.push_back(current);
      // Add the distance to the weights
      tour.weights.push_back(min_distance);
      // Update the total distance
      total_distance += min_distance;
      // Mark the nearest node as visited
      visited.insert(current.id);
    }
  }

  // Calculate the distance back to the starting node
  size_t return_distance = current.distance(*start_it);
  // Push startin gnode to the end of the path vector
  tour.path.push_back(*start_it);
  // Add the return distance to the weights
  tour.weights.push_back(return_distance);
  // Update the total distance
  total_distance += return_distance;

  // Set the total distance of the tour
  tour.total_distance = total_distance;

  return tour;
}
}


