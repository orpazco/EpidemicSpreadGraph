#include "../include/Graph.h"

using namespace std;

Graph::Graph() {}

Graph::Graph(vector<vector<int>> matrix): edges(std::move(matrix)), infectedNodesVector({}){
    infectedNodesVector.resize(edges.size());
}

Graph::Graph(const Graph &graph) {
    vector<vector<int>> newEdges(getEdges());
    edges = newEdges;
    infectedNodesVector = graph.infectedNodesVector;
}

Graph * Graph::clone() const {
    return new Graph(*this);
}

void Graph::infectNode(int nodeInd) {
    infectedNodesVector[nodeInd] = true;
}

bool Graph::isInfected(int nodeInd) {
    return infectedNodesVector[0];
}

// get the most left child (the smallest) of the given node
int Graph::getLeftChildNotInf(const int nodeInd) {
    vector<int> nodeEdges = getEdges()[nodeInd];
    for (int i = 0; i < nodeEdges.size(); i++) {
        // if the node isn't infected return the node id
        if (i != nodeInd && !isInfected(nodeEdges[i])){
            return i;
        }
    }
    return -1;
}

const std::vector<std::vector<int>> &Graph::getEdges() const {
    return edges;
}
