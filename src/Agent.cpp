#include "../include/Agent.h"
#include "../include/Session.h"
#include "../include/Tree.h"

Agent::Agent() {}

// Contact Tracer

ContactTracer::ContactTracer() {}

Agent * ContactTracer::clone() const {
    return new ContactTracer(*this);
}

void ContactTracer::act(Session &session) {
    Tree* tree = Tree::createTree(session, session.dequeueInfected()); // create a bfs tree
    int toIsolate = tree->traceTree(); // get the node to isolate
    session.isolateNode(toIsolate); // isolate the node
}

int ContactTracer::canInfect(Session& session) {return -1;} // can never infect

// Virus

Virus::Virus(int nodeInd): nodeInd(nodeInd) {}

void Virus::act(Session &session) {

    // add current node to infected queue if this node wasnt enqueue already
    if (!session.isInfected(getNodeInd())){
        session.enqueueInfected(getNodeInd());
    }

    // spread the virus to the left most child
    int toInfect = canInfect(session);
    if (toInfect != -1) {
        session.infectNode(toInfect);
        // finish
    }
}

int Virus::getNodeInd() const {
    return nodeInd;
}

Agent * Virus::clone() const {
    return new Virus(nodeInd);
}

int Virus::canInfect(Session& session) {
    int leftChild = session.getLeftChildNotInf(getNodeInd()); // return the node id of the next node this virus can infect
    return leftChild;
}
