#include "Node.hpp"
#include <iostream>

/**
 * Constructs a node with a non-negative identifier and 2D coordinates.
 * 
 * @param id_ The non-negative identifier for the node.
 * @param x_ The x-coordinate of the node.
 * @param y_ The y-coordinate of the node.
 */
Node::Node(const size_t& id_, const double& x_, const double& y_) : 
    id{id_}, x{x_}, y{y_} {}

/**
 * Calculates the Euclidean distance to another node, rounded to the nearest integer.
 * 
 * @param other The node to calculate the distance to.
 * @return The distance as an integer.
 */
size_t Node::distance(const Node& other) const {
    double dx = (x - other.x);
    double dy = (y - other.y);
    return std::round(sqrt(dx * dx + dy * dy));
}