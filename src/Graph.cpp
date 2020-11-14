#include <queue>
#include "../include/Graph.h"

using namespace std;

Graph::Graph() {}

Graph::Graph(vector<vector<int>> matrix): edges(std::move(matrix)), infectedNodesVector({}){
    infectedNodesVector.resize(edges.size());
}

Graph::Graph(const Graph &graph) {
    vector<vector<int>> newEdges(getEdges());
    edges = newEdges;
    infectedNodesVector = graph.getInfectedVector();
}

Graph * Graph::clone() const {
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
        if (i != nodeInd && nodeEdges[i] && !isInfected(i)){
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

Tree * Graph::BFS(Session &session, int root) const {
   Tree *tree = Tree::createTree(session, root);

   // initialize visited nodes vector
    vector<bool> visitedNodes(getEdges().size());
    for (int i = 0; i < getEdges().size(); i++) {
        visitedNodes[i] = false;
    }

    std::queue<Tree*> queue;
    // initialize queue
    queue.push(tree);
    visitedNodes[root] = true;

    while (!queue.empty()){
        //dequeue first node
        Tree* currNode = queue.front();
        queue.pop();
        vector<int> neighbors = getEdges()[currNode->getNode()];
        for (int i = 0; i < neighbors.size(); i++) {
            if (neighbors[i] && i != currNode->getNode()) {
                if(!visitedNodes[i]) {
                    Tree *childNode = Tree::createTree(session, i);
                    currNode->addChild(childNode);
                    queue.push(childNode);
                    visitedNodes[i] = true;
                }
            }
        }
    }
    return tree;
}