//
// Created by Orpaz on 09/11/2020.
//

#ifndef EPIDEMICSPREADGRAPH_SESSIONTESTS_H
#define EPIDEMICSPREADGRAPH_SESSIONTESTS_H
#include <string>
#include <vector>
#include "../include/TestMain.h"
using namespace std;

class SessionTests {
public:
    SessionTests();
    void startTests();
    void initializeParams();

    void addAgentClone();
    void addAgentByPointer();

    bool isPass;
    vector<string> errors;
};


#endif //EPIDEMICSPREADGRAPH_SESSIONTESTS_H
