//
// Created by Orpaz on 07/11/2020.
//

#ifndef EPIDEMICSPREADGRAPH_TESTMAIN_H
#define EPIDEMICSPREADGRAPH_TESTMAIN_H

#include <string>
#include <vector>

static class TestMain {
public:
    static void assert(bool isPass, const std::string& testName);
    static void assert(bool isPass, const std::string& testName, std::vector<std::string> errors);
};


#endif //EPIDEMICSPREADGRAPH_TESTMAIN_H
