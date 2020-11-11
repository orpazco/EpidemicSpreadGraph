#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "Tree.h"
#include "Session.h"

class Graph{
public:
    Graph(); //TODO delete
    Graph(std::vector<std::vector<int>> matrix);
    Graph(const Graph &graph);

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd) const;

    Graph* clone() const;
    const std::vector<std::vector<int>> &getEdges() const;
    int getLeftChildNotInf(int nodeInd) const;
    void isolateNode(int node);
    const std::vector<bool> & getInfectedVector() const;
    Tree* BFS(Session &session, int root) const;

private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> infectedNodesVector;
    void removeEdge(int sourceNode, int destinationNode);
};

#endif