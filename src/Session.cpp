#include <fstream>
#include <iostream>
#include "../include/Session.h"
#include "../include/Agent.h"
using namespace std;

Session::Session(const std::string &path): cycle(0), notTerminated(true), g({}), parsedJson({}), infectionQueue({}), agents({}) {
    jsonInit(path); // initializes config Json
    initGraph(); // inits graph according to config
    addParsedAgents(); // adds agents from the config
    setParsedTreeType(); // sets tree type according to config
}

// destructor
Session::~Session() {
    clear();
}

void Session::clear(){
    if (!getAgents().empty()){
        for (int i = 0; i < getAgents().size(); i++) {
            if (agents[i])
                delete agents[i];
        }
        agents.clear();
    }
    if (!parsedJson.empty())
        parsedJson.clear();
}

// copy ctor
Session::Session(const Session& other): g({}), parsedJson({}), infectionQueue({}), agents({}) {
    g = (*(other.g.clone()));
    copyAgents(other);
    treeType = other.treeType;
    cycle = other.cycle;
    parsedJson = other.parsedJson; //TODO: test deep copy
    infectionQueue = other.infectionQueue;
    notTerminated = other.notTerminated;
}

// assignment
Session& Session::operator=(const Session &other) {
     if (this != &other){
         clear();
         treeType = other.treeType;
         cycle = other.cycle;
         parsedJson = other.parsedJson;
         infectionQueue = other.infectionQueue;
         notTerminated = other.notTerminated;
         g = other.g;
         copyAgents(other);
     }
    return *this;
}

// move ctor
Session::Session(Session&& other): g({}), parsedJson({}), infectionQueue({}), agents({}){
    treeType = other.treeType;
    cycle = other.cycle;
    parsedJson = other.parsedJson;
    infectionQueue = other.infectionQueue;
    notTerminated = other.notTerminated;
    agents = std::move(other.agents);
    g = other.g; //TODO check
}

// move assignment
Session& Session::operator=(Session&& other){
    treeType = other.treeType;
    cycle = other.cycle;
    parsedJson = other.parsedJson;
    infectionQueue = other.infectionQueue;
    notTerminated = other.notTerminated;
    // empty the agents list before steal the list from other
    if (!agents.empty()){
        for (int i = 0; i < agents.size(); i++) {
            if (agents[i])
                delete agents[i];
        }
        agents.clear();
    }
    agents = std::move(other.agents);
    g = other.g;
    return *this;
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
        terminationCheck();
    }
    jsonOutput();
}


void Session::terminationCheck() {
    for (int i = 0; i < agents.size(); i++) { // out of all active agents (not carrier nodes)
        // activate each agent
        int node = getAgents()[i]->canInfect(*this); // canInfect returns the node id the virus will infect in the next cycle
        if (node!=-1)// returns any node at all
            notTerminated = true;
    }
}

// update the infected node in graph and add new virus to agent list
void Session::infectNode(int nodeInd) {
    g.infectNode(nodeInd);
    addAgent(new Virus(nodeInd));
}

void Session::spreadToNode(int nodeInd) {
    addAgent(new Virus(nodeInd));
    g.spreadToNode(nodeInd);
}

// return is the given node is infected
bool Session::isInfected(int nodeInd) const {
    return g.isInfected(nodeInd);
}

int Session::getLeftChildNotInf(int nodeInd) {
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
        int toRet = infectionQueue.front();
        infectionQueue.pop_front();
        return toRet;
    }
    return -1;
}

bool Session::infQIsEmpty() const {
    return infectionQueue.empty();
}

Tree * Session::BFS(Session &session, int root) {
    return g.BFS(session, root);
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

const std::vector<Agent *> & Session::getAgents() const {
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
        if(agents[i][0]=="V") {
            //infectNode(agents[i][1]); // create a new virus using the entry
            addAgent(new Virus(agents[i][1])); // create a new virus using the entry - pass by pointer
        }
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
    // write to json file the infected nodes
    vector<int> infectedToJson;
    for (int i = 0; i < g.getInfectedVector().size(); i++) {
        if (g.getInfectedVector()[i])
            infectedToJson.push_back(i);
    }
    output["infected"] = infectedToJson;
    std::ofstream outpath("output.json");
    outpath << output;
}

void Session::isolateNode(int &node){
    g.isolateNode(node);
}

void Session::copyAgents(const Session &other) {
    for (std::vector<Agent*>::const_iterator it = other.agents.begin(); it != other.agents.end(); it++) {
        addAgent(*(*it));
    }
}
