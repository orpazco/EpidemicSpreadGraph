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
    }
}

// Virus

Virus::Virus(int nodeInd): nodeInd(nodeInd) {}

void Virus::act(Session &session) {

    // add current node to infected queue if this node wasnt enqueue already
    if (!session.isInfected(getNodeInd())){
        session.enqueueInfected(getNodeInd());
        session.infectNode(getNodeInd());
    }

    // spread the virus to the left most child
    int leftChild = session.getLeftChildNotInf(getNodeInd());
    if (leftChild != -1) {
        session.addAgent(Virus(leftChild));
        // finish
        session.virusActed();
    }
}

// destructor
Virus::~Virus(){}

Virus::Virus(const Virus &other): nodeInd(other.nodeInd) {}

int Virus::getNodeInd() const {
    return nodeInd;
}

Agent * Virus::clone() const {
    return new Virus(nodeInd);
}
