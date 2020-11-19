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
    //Ctor
    Session(const std::string& path); // parse the json file, init graph, tree type and agents list
    // destructor
    virtual ~Session();
    void clear();
    // copy ctor
    Session(const Session& other);
    // assignment
    Session& operator=(const Session& other);
    // move ctor
    Session(Session&& other);
    // move assignment
    Session& operator=(Session&& other);

    void simulate();
    void addAgent(const Agent& agent);
    void addAgent(Agent* agent);
    void setGraph(const Graph& graph);
    void setGraph(Graph* graph);

    void enqueueInfected(int);
    int dequeueInfected();

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd) const;
    bool infQIsEmpty() const;
    Tree* BFS(Session &session, int root);
    int getLeftChildNotInf(const int nodeInd);
    int getCycle() const;
    TreeType getTreeType() const;
    const std::vector<Agent*> & getAgents() const;
    void isolateNode(int &node);
    void spreadToNode(int nodeInd);

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    int cycle;
    json parsedJson;
    std::deque<int> infectionQueue;
    bool notTerminated;
    void terminationCheck();
    const std::deque<int> &getInfectionQueue() const;
    void jsonOutput();
    void addParsedAgents();
    void setParsedTreeType();
    void setTreeType(TreeType type);
    void initGraph();
    void jsonInit(const std::string &path);
    void copyAgents(const Session &other);
    void moveAgents(Session&& other);
};

#endif