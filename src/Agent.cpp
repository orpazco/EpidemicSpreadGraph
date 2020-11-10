#include "../include/Agent.h"
#include "../include/Session.h"

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

void Virus::act(Session &session) {}

int Virus::getNodeInd() const {
    return nodeInd;
}

Agent * Virus::clone() const {
    return new Virus(nodeInd);
}
