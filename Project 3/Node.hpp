#pragma once
#include <cmath>
struct Node {
  // The id, x-coordinate, & y-coordinate of the given Node
  size_t id; double x; double y;

  /**
   * Constructs a node with a non-negative identifier and 2D coordinates.
   * 
   * @param id_ The non-negative identifier for the node.
   * @param x_ The x-coordinate of the node.
   * @param y_ The y-coordinate of the node.
   */
  Node(const size_t& id_, const double& x_, const double& y_);

  /**
   * Calculates the Euclidean distance to another node, rounded to the nearest integer.
   * 
   * @param other The node to calculate the distance to.
   * @return The distance as an integer.
   */
  size_t distance(const Node& other) const;
};