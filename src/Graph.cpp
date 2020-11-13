#include "../include/Graph.h"
using namespace std;
// ctor
Graph::Graph(vector<vector<int>> matrix): edges(std::move(matrix)), infectedNodesVector({}){
    infectedNodesVector.resize(edges.size());
}

// copy ctor
Graph::Graph(const Graph &other): edges(other.edges), infectedNodesVector(other.infectedNodesVector){}

// assignment op
Graph& Graph::operator=(const Graph &other) {
    edges = other.getEdges();
    return *this;
}

Graph* Graph::clone() const {
    return new Graph(*this);
}

void Graph::infectNode(int nodeInd) {
    infectedNodesVector[nodeInd] = true;
}

bool Graph::isInfected(int nodeInd) const{
    return infectedNodesVector[nodeInd];
}

const vector<bool> & Graph::getInfectedVector() const {
    return infectedNodesVector;
}

// get the most left child (the smallest) of the given node
int Graph::getLeftChildNotInf(int nodeInd) const{
    vector<int> nodeEdges = getEdges()[nodeInd];
    for (int i = 0; i < nodeEdges.size(); i++) {
        // if the node isn't infected return the node id
        if (i != nodeInd && !isInfected(nodeEdges[i])){
            return i;
        }
    }
    return -1;
}

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


