#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <deque>
#include "Graph.h"
#include "../include/json.hpp"

using json = nlohmann::json;

class Agent;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:
    Session(const std::string& path); // parse the json file, init graph, tree type and agents list

    void simulate(); // start the game
    void addAgent(const Agent& agent); // add agent to the list
    void addAgent(Agent* agent); // add agent to the list
    void setGraph(const Graph& graph); // init the graph
    void setGraph(Graph* graph); // init the graph

    void enqueueInfected(int);
    int dequeueInfected();

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd) const;
    int getLeftChildNotInf(const int nodeInd) const;
    int getCycle() const;
    TreeType getTreeType() const;
    const std::vector<Agent*> & getAgents() const;
    void isolateNode(int &node);

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    int cycle;
    json parsedJson;
    std::deque<int> infectionQueue;
    bool notTerminated;
    void terminationCheck(int& numOfAgents);
    const std::deque<int> &getInfectionQueue() const;    // TODO - review with orpaz
    void jsonPrint(); //TODO DELETEME
    void jsonOutput();
    void addParsedAgents();
    void setParsedTreeType();
    void setTreeType(TreeType type);
    void initGraph();
    void jsonInit(const std::string &path);
};

#endif