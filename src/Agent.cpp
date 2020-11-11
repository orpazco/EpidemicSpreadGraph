#include "../include/Agent.h"
#include "../include/Session.h"
#include "../include/Tree.h"

Virus::Virus(int nodeInd): nodeInd(nodeInd) {}
ContactTracer::ContactTracer() {}
Agent::Agent() {}
void Virus::act(Session &session) {}

void ContactTracer::act(Session &session) {
    Tree* tree = Tree::createTree(session, session.dequeueInfected()); // create a bfs tree
    int toIsolate = tree->traceTree(); // get the node to isolate
    session.isolateNode(toIsolate); // isolate the node
}
