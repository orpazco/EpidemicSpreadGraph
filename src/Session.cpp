#include <fstream>
#include <iostream>
#include "../include/Session.h"
#include "../include/Agent.h"

Session::Session() {}

Session::Session(const std::string &path) : cycle(0), notTerminated(true) {
    jsonInit(path); // initializes config Json
    addParsedAgents(); // adds agents from the config
    setParsedTreeType(); // sets tree type according to config
    initGraph(); // inits graph according to config
    //TODO finish
}

void Session::simulate() {
    while (notTerminated){
        cycle++;
        notTerminated = false;
        // get agents list size so the for will loop on the current agents
        int agentsSize = getAgents().size();
        for (int i = 0; i < agentsSize; i++) {
            // activate each agent
            getAgents()[i]->act(*this);
        }
    }
}

void Session::virusActed() {
    notTerminated = true;
}

// update the infected node in graph and add new virus to agent list
void Session::infectNode(int nodeInd) {
    g.infectNode(nodeInd);
    addAgent(new Virus(nodeInd));
}

// return is the given node is infected
bool Session::isInfected(int nodeInd) {
    return g.isInfected(nodeInd);
}

int Session::getLeftChildNotInf(const int nodeInd) {
    return g.getLeftChildNotInf(nodeInd);
}

void Session::addAgent(const Agent &agent) {
    //clone agent and add to agent list
    Agent* newAgent = agent.clone();
    agents.push_back(newAgent);
}

void Session::addAgent(Agent* agent) {
    agents.push_back(agent);
}

void Session::setGraph(const Graph &graph) {
    // clone graph
    Graph* newGraph = graph.clone();
    g = *newGraph;
}

void Session::setGraph(Graph* graph) {
    // set graph by pointer
    g = *graph;
}

void Session::enqueueInfected(int nId) {
    infectionQueue.push_back(nId);
}

int Session::dequeueInfected() {
    if (!infectionQueue.empty()){
        return infectionQueue.front();
    }
    return -1;
}

//getters

int Session::getCycle() const {
    return cycle;
}

TreeType Session::getTreeType() const {
    return treeType;
}

const deque<int> &Session::getInfectionQueue() const {
    return infectionQueue;
}

const std::vector<Agent *> Session::getAgents() const {
    return agents;
}

// setters

void Session::setTreeType(TreeType type) {
    treeType = type;
}

// json parser functions

void Session::jsonInit(const string &path) {
    std::ifstream input(path);//gets the json config path and serializes it to input as a string
    input >> parsedJson; // initialize the json with string stream (convention and not choice)

}

void Session::setParsedTreeType() {
   std::string type=parsedJson["tree"].get<std::string>(); //TODO - handle json errors
   if (type=="R") setTreeType(Root);
   else if (type=="C") setTreeType(Cycle);
   else if (type=="M") setTreeType(MaxRank);
}

void Session::addParsedAgents() {
    json& agents=parsedJson["agents"];
    for (int i = 0; i < agents.size(); ++i) { // iterate over agents section
        if(agents[i][0]=="V")
            addAgent(new Virus(agents[i][1])); // create a new virus using the entry - pass by pointer
        else if(agents[i][0]=="C")
            addAgent(new ContactTracer()); // create a new CT pass by pointer
    }
}

void Session::initGraph() {
    vector<vector<int>> matrix=parsedJson["graph"];
    setGraph(new Graph(matrix));
}

void Session::jsonOutput() {
    // write the output to json:
    // graph - according to last iteration under "graph": (vector of int vector matrix)
    // infected queue under "infected": [array of all infected nodes]
    json output;
    output["graph"] = g.getEdges();
    output["infected"] = getInfectionQueue();
    std::ofstream outpath("../jsons/outputs/output.json");
    outpath << output;
}

void Session::isolateNode(int &node){
    g.isolateNode(node);
}

void Session::jsonPrint() {}
