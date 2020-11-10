#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
using namespace std;

class Graph{
public:
    Graph(); //TODO delete
    Graph(vector<vector<int>> matrix);
    Graph(const Graph &graph);

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    Graph* clone() const;
    const vector<vector<int>> &getEdges() const;
    int getLeftChildNotInf(const int nodeInd);

private:
    vector<vector<int>> edges;
    vector<bool> infectedNodesVector;
};

#endif