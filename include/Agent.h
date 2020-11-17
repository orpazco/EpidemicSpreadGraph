#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

class Agent{
public:
    virtual void act(Session& session)=0;
    virtual Agent* clone() const=0;

    // destructor
    virtual ~Agent()=default;
};

class ContactTracer: public Agent{
public:
    ContactTracer();

    virtual void act(Session& session);
    virtual Agent* clone() const;
    virtual ~ContactTracer();
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
    virtual void act(Session& session);
    virtual Agent* clone() const;
    virtual ~Virus();
    // copy ctor
    Virus(const Virus& other);

    int getNodeInd() const;
private:
    const int nodeInd;
};

#endif