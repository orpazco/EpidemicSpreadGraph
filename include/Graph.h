#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "Tree.h"
//#include "Session.h"

class Graph{
public:
    // ctor
    Graph(std::vector<std::vector<int>> matrix);
    // copy ctor
    Graph(const Graph& other);
    // setters

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd) const;

    Graph* clone() const;
    const std::vector<std::vector<int>> &getEdges() const;
    int getLeftChildNotInf(int nodeInd);
    void isolateNode(int node);
    const std::vector<bool> & getInfectedVector() const;
    Tree* BFS(Session &session, int root);

    // assignment op
    Graph& operator=(const Graph& other);
    // move ctor
    Graph(Graph&& other);
    //move assignment op
    Graph& operator=(Graph&& other);

private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> infectedNodesVector;
    void removeEdge(int sourceNode, int destinationNode);
};

#endif