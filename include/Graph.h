#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:
    Graph(); //TODO delete
    Graph(std::vector<std::vector<int>> matrix);
    Graph(const Graph &graph);

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    Graph* clone() const;
    const std::vector<std::vector<int>> &getEdges() const;

private:
    std::vector<std::vector<int>> edges;
};

#endif