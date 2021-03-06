#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

class Agent{
public:
    virtual void act(Session& session)=0;
    // destructor
    virtual ~Agent()=default;
    virtual Agent* clone() const=0;

    virtual int canInfect(Session& session) =0;
    virtual int canInfectSelf(Session& session) =0;
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual ~ContactTracer();

    virtual void act(Session& session);
    virtual Agent* clone() const;

    virtual int canInfect(Session& session);
    virtual int canInfectSelf(Session& session);
};



class Virus: public Agent{
public:
    Virus(int nodeInd);
    // copy ctor
    Virus(const Virus& other);
    virtual ~Virus();

    virtual void act(Session& session);
    virtual Agent* clone() const;

    int getNodeInd() const;
    virtual int canInfect(Session& session);
    virtual int canInfectSelf(Session& session);

private:
    const int nodeInd;
};

#endif