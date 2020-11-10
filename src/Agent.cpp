#include "../include/Agent.h"

// Ctor
Agent::Agent() {}

// Contact Tracer

ContactTracer::ContactTracer() {}

void ContactTracer::act(Session &session) {}

Agent * ContactTracer::clone() const {
    return new ContactTracer;
}

// Virus

Virus::Virus(int nodeInd): nodeInd(nodeInd) {}

void Virus::act(Session &session) {

    // add current node to infected queue
    session.enqueueInfected(getNodeInd());

    // spread the virus to the left most child
    int leftChild = session.getLeftChildNotInf(getNodeInd());
    if (leftChild != -1) {
        session.infectNode(leftChild);
        // finish
        session.virusActed();
    }
}

int Virus::getNodeInd() const {
    return nodeInd;
}

Agent * Virus::clone() const {
    return new Virus(nodeInd);
}
