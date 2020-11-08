#include "../include/Session.h"

Session::Session(const std::string &path) {}

void Session::simulate() {}

void Session::addAgent(const Agent &agent) {}

void Session::setGraph(const Graph &graph) {}

void Session::enqueueInfected(int) {}

int Session::dequeueInfected() {}

int Session::getCycle() const {}

TreeType Session::getTreeType() const {}