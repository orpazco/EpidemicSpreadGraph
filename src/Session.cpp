#include <fstream>
#include <iostream>
#include "../include/Session.h"
#include "../include/json.hpp"

// for convenience
using json = nlohmann::json;

Session::Session(const std::string &path) {
    std::ifstream input(path);
    json j;
    input >> j;
    std::vector<std::vector<int>> matrix1=j["graph"];
    jsonprintsection(matrix1);

}

void  Session::jsonprintsection(std::vector<std::vector<int>> mat) {
    std::cout << mat[1][1] ;
}

void Session::simulate() {}

void Session::addAgent(const Agent &agent) {}

void Session::setGraph(const Graph &graph) {}

void Session::enqueueInfected(int) {}

int Session::dequeueInfected() {}

int Session::getCycle() const {}

TreeType Session::getTreeType() const {}

void jsonPrint();
void jsonOutput();