#include "../include/Graph.h"

#include <utility>
using namespace std;

Graph::Graph() {}

Graph::Graph(vector<vector<int>> matrix){
    edges = std::move(matrix);
}

Graph::Graph(const Graph &graph) {
    vector<vector<int>> newEdges(getEdges());
    edges = newEdges;
}

Graph * Graph::clone() const {
    return new Graph(*this);
}

const std::vector<std::vector<int>> &Graph::getEdges() const {
    return edges;
}
