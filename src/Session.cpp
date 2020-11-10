#include <fstream>
#include <iostream>
#include "../include/Session.h"
#include "../include/Agent.h"


Session::Session(const std::string &path) : cycle(0) {
    jsonInit(path); // initializes config Json
    addParsedAgents(); // adds agents from the config
    setParsedTreeType(); // sets tree type according to config
    initGraph(); // inits graph according to config
    //TODO finish
}

void Session::simulate() {}


void Session::addAgent(const Agent &agent) {
    //clone agent
}

void Session::addAgent(Agent* agent) {
    //add agent by pointer
}

void Session::setGraph(const Graph &graph) {
    // clone graph
}

void Session::setGraph(Graph* graph) {
    // set graph by pointer
}

void Session::enqueueInfected(int) {}

int Session::dequeueInfected() {}

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

void Session::jsonPrint() {}
