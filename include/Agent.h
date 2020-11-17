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
    virtual int canInfect(Session& session) =0;
};

class ContactTracer: public Agent{
public:
    ContactTracer();

    virtual void act(Session& session);
    virtual Agent* clone() const;

    virtual ~ContactTracer();
    virtual int canInfect(Session& session);
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
    virtual int canInfect(Session& session);
private:
    const int nodeInd;
};

#endif