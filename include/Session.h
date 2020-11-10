#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <deque>
#include "Graph.h"
#include "../include/json.hpp"

using json = nlohmann::json;
using namespace std;

class Agent;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:
    Session(); // TODO delete (for tests)
    Session(const std::string& path); // parse the json file, init graph, tree type and agents list

    void simulate(); // start the game
    void addAgent(const Agent& agent); // add agent to the list
    void addAgent(Agent* agent); // add agent to the list
    void setGraph(const Graph& graph); // init the graph
    void setGraph(Graph* graph); // init the graph

    void enqueueInfected(int);
    int dequeueInfected();
    int getCycle() const;

    TreeType getTreeType() const;
    const std::vector<Agent*> getAgents() const;

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    int cycle;
    json parsedJson;
    deque<int> infectionQueue;
public:

private:
    const deque<int> &getInfectionQueue() const;    // TODO - review with orpaz
    void jsonPrint(); //TODO DELETEME
    void jsonprintsection(vector<string> mat); //TODO DELETEME
    void jsonOutput();
    void addParsedAgents();
    void setParsedTreeType();
    void setTreeType(TreeType type);
    void initGraph();
};

#endif