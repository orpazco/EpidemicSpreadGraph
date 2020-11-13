#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:
    // ctor
    Graph(std::vector<std::vector<int>> matrix);
    // copy ctor
    Graph(const Graph& other);
    // setters
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    void isolateNode(int node);
    const std::vector<std::vector<int>> &getEdges() const;

    // assignment op
    Graph& operator=(const Graph& other);
    //move assignment
    // move ctor

private:
    void removeEdge(int sourceNode, int destinationNode);
    std::vector<std::vector<int>> edges;
};

#endif