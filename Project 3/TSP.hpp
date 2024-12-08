#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>

#include "Node.hpp"

namespace TSP {
  /**
   * Represents a tour for the traveling salesperson problem (TSP), including the sequence of cities visited,
   * the edge weights between them, and the total distance traveled.
   *
   * @details 
   * - The `path` vector contains the sequence of `Node` objects representing the cities in the order they are visited.
   * - The `weights` vector stores the distances between consecutive cities in the `path`.
   * - The first weight in `weights` is always 0, as the tour starts at the initial city without traveling.
   * - The `total_distance` represents the sum of all edge weights, including the return trip to the starting city.
   */
  struct Tour {
    std::vector<Node> path;
    std::vector<size_t> weights;
    size_t total_distance;

    Tour() : path{std::vector<Node>()}, weights{std::vector<size_t>()}, total_distance{0} {};

    /**
     * Displays the edges and total distance of the tour.
     * Each edge is printed in the format: "EDGE start_id -> end_id | WEIGHT: weight".
     */
    void display() const;
  };

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
  std::list<Node> constructCities(const std::string& filename);
  
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
  Tour nearestNeighbor(std::list<Node> cities, const size_t& start_id = 1);
};
