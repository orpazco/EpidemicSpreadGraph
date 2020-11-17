//
// Created by Orpaz on 09/11/2020.
//

#include "../include/SessionTests.h"
#include "../../include/Agent.h"

using namespace std;

SessionTests::SessionTests(): isPass(true), errors({}) {
    startTests();
}

void SessionTests::startTests() {
//    addAgentByPointer();
//    addAgentClone();
}

void SessionTests::initializeParams() {
    isPass = true;
    errors = {};
}

//void SessionTests::addAgentByPointer() {
//    initializeParams();
//    ContactTracer* a1 = new ContactTracer();
//    Session* mainSess = new Session();
//    mainSess->addAgent(a1);
//    vector<Agent*> agentsList = mainSess->getAgents();
//    if (agentsList.size() != 1){
//        isPass = false;
//        errors.push_back("Expected agents size: 1, actual: " + to_string(agentsList.size()));
//    }
//    if (a1 != agentsList[0]){
//        isPass = false;
//        errors.push_back("Agent doesnt added to agents list with pointer, a1: " + to_string(
//                reinterpret_cast<int>(&a1)) + " agent in list: " + to_string(reinterpret_cast<int>(agentsList[0])) + to_string(agentsList.size()));
//    }
//
//    TestMain::assert1(isPass, __FUNCTION__ , errors);
//}

//void SessionTests::addAgentClone() {
//    initializeParams();
//    Agent* a1 = new ContactTracer();
//    Agent* v1 = new Virus(1);
//    Session* mainSess = new Session();
//    mainSess->addAgent(*a1);
//    mainSess->addAgent(*v1);
//    vector<Agent*> agentsList = mainSess->getAgents();
//    if (agentsList.size() != 2){
//        isPass = false;
//        errors.push_back("Expected agents size: 2, actual: " + to_string(agentsList.size()));
//    }
//    for (int i = 0; i < agentsList.size(); ++i) {
//        Agent* agent = agentsList[i];
//        //std::is_base_of<Agent, ContactTracer>::value
//        if (dynamic_cast<ContactTracer*>(agent)){
//            if (agent == a1){
//                isPass = false;
//                errors.push_back("Contact tracer a1 added to list by ref and not by val");
//            }
//        } else if (dynamic_cast<Virus*>(agent)){
//            if (agent == v1){
//                isPass = false;
//                errors.push_back("Virus s1 added to list by ref and not by val");
//            }
//            if (((Virus*)agent)->getNodeInd() != ((Virus*)v1)->getNodeInd()){
//                isPass = false;
//                errors.push_back("virus node not as expected. actual: " + to_string(((Virus*)agent)->getNodeInd()) + " expected: " + to_string(((Virus*)v1)->getNodeInd()));
//            }
//        } else{
//            isPass = false;
//            errors.push_back("agent added id different from contact trace id and virus id");
//        }
//    }
//    TestMain::assert1(isPass, __FUNCTION__ , errors);
//}

void SessionTests::addAgentClone() {
    initializeParams();
    Agent* a1 = new ContactTracer();
    Agent* v1 = new Virus(1);
    Session* mainSess = new Session("../../jsons/examples/config1.json");
    mainSess->addAgent(*a1);
    mainSess->addAgent(*v1);
    vector<Agent*> agentsList = mainSess->getAgents();
    if (agentsList.size() != 2){
        isPass = false;
        errors.push_back("Expected agents size: 2, actual: " + to_string(agentsList.size()));
    }
    for (int i = 0; i < agentsList.size(); ++i) {
        Agent* agent = agentsList[i];
        //std::is_base_of<Agent, ContactTracer>::value
        if (dynamic_cast<ContactTracer*>(agent)){
            if (agent == a1){
                isPass = false;
                errors.push_back("Contact tracer a1 added to list by ref and not by val");
            }
        } else if (dynamic_cast<Virus*>(agent)){
            if (agent == v1){
                isPass = false;
                errors.push_back("Virus s1 added to list by ref and not by val");
            }
            if (((Virus*)agent)->getNodeInd() != ((Virus*)v1)->getNodeInd()){
                isPass = false;
                errors.push_back("virus node not as expected. actual: " + to_string(((Virus*)agent)->getNodeInd()) + " expected: " + to_string(((Virus*)v1)->getNodeInd()));
            }
        } else{
            isPass = false;
            errors.push_back("agent added id different from contact trace id and virus id");
        }
    }
    TestMain::assert1(isPass, __FUNCTION__ , errors);
}
