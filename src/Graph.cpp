#include "../include/Graph.h"

Graph::Graph(std::vector<std::vector<int>> matrix){};
Graph::Graph() {}

const std::vector<std::vector<int>> &Graph::getEdges() const {
    return edges;
}
