#include "../include/Graph.h"

Graph::Graph(std::vector<std::vector<int>> matrix){};
Graph::Graph() {}


void Graph::isolateNode(int isoNode) { //TODO - keep neighbors in better data structure?
    for (int i = 0; i < getEdges().size() ; ++i) { // for every node in the graph, remove the edge to and from isoNode if exists
        removeEdge(isoNode, i);
    }
}

void Graph::removeEdge(int sourceNode, int destinationNode) {
    if (edges[sourceNode][destinationNode]&& sourceNode!=destinationNode) // remove e = (s,d) and s!=d
        edges[sourceNode][destinationNode] = false;
    if (edges[destinationNode][sourceNode]&& sourceNode!=destinationNode) // remove e = (d,s) and d!=s
        edges[destinationNode][sourceNode] = false;
}
const std::vector<std::vector<int>> &Graph::getEdges() const {
    return edges;
}
