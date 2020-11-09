#include "../include/Graph.h"

Graph::Graph() {}

const std::vector<std::vector<int>> &Graph::getEdges() const {
    return edges;
}
