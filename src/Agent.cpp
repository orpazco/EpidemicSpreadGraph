#include "../include/Agent.h"

// Contact Tracer
ContactTracer::ContactTracer() {}

// destructor
ContactTracer::~ContactTracer() {}

Agent * ContactTracer::clone() const {
    return new ContactTracer(*this);
}

void ContactTracer::act(Session &session) {
    if(!session.infQIsEmpty()){
        Tree* tree = session.BFS(session, session.dequeueInfected()); // create a bfs tree
        int toIsolate = tree->traceTree(); // get the node to isolate
        session.isolateNode(toIsolate); // isolate the node
        delete tree;
    }
}

int ContactTracer::canInfect(Session& session) {return -1;} // can never infect
int ContactTracer::canInfectSelf(Session &session) {return -1;}

// Virus

Virus::Virus(int nodeInd): nodeInd(nodeInd){}

void Virus::act(Session &session) {

    // add current node to infected queue if this node wasnt enqueue already
    if (!session.isInfected(getNodeInd())){
        session.enqueueInfected(getNodeInd());
        session.infectNode(getNodeInd());
    }

    // spread the virus to the left most child
    int toInfect = canInfect(session);
    if (toInfect != -1) {
        session.spreadToNode(toInfect);
    }
}

// destructor
Virus::~Virus(){}

Virus::Virus(const Virus &other): nodeInd(other.nodeInd){}

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

int Virus::canInfectSelf(Session &session) {
    if (!session.isInfected(nodeInd)){
        return getNodeInd();
    }
    return -1;
}
