#include <fstream>
#include <iostream>
#include "../include/Session.h"


// for convenience
using json = nlohmann::json;

Session::Session(const std::string &path) {
    std::ifstream input(path);
    input >> parsedJson;
    addParsedAgents();
    treeType = getTreeType();
    //TODO finish
}

void  Session::jsonprintsection(std::vector<std::string> mat) {
    std::cout << mat[1];
}

void Session::simulate() {}

void Session::addAgent(const Agent &agent) {}

void Session::setGraph(const Graph &graph) {}

void Session::enqueueInfected(int) {}

int Session::dequeueInfected() {}

int Session::getCycle() const {
}

TreeType Session::getTreeType() const {
   std::string type =parsedJson["tree"].get<std::string>(); //TODO - handle json errors
   if (type=="R") return Root;
   if (type=="C") return Cycle;
   if (type=="M") return MaxRank;
}


void Session::addParsedAgents() {
    json& agents = parsedJson["agents"];
    for (int i = 0; i < agents.size(); ++i) { // iterate over agents section
        if(agents[i][0]=="V")
            addAgent(*(new Virus(agents[i][1]))); // create a new virus using the entry
        else if(agents[i][0]=="C")
            addAgent(*(new ContactTracer())); // create a new CT
    }
}
void Session::jsonOutput() {}
void Session::jsonPrint() {}