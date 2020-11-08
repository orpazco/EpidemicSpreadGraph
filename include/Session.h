#ifndef SESSION_H_
#define SESSION_H_


#include "../include/json.hpp"

// for convenience
using json = nlohmann::json;
using namespace std;
#include <vector>
#include <string>
#include "Graph.h"
#include "Agent.h"

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
    void setGraph(const Graph& graph); // init the graph

    void enqueueInfected(int);
    int dequeueInfected();
    int getCycle() const;
    TreeType getTreeType() const;

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    int cycle;
    json parsedJson;
    void jsonPrint(); //TODO DELETEME
    void jsonprintsection(vector<string> mat); //TODO DELETEME
    void jsonOutput();
    void addParsedAgents();
    void initGraph(vector<vector<int>>);
};

#endif