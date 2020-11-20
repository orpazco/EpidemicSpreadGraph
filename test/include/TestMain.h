//
// Created by Orpaz on 07/11/2020.
//

#ifndef EPIDEMICSPREADGRAPH_TESTMAIN_H
#define EPIDEMICSPREADGRAPH_TESTMAIN_H

#include <string>
#include <vector>

class TestMain {
public:
    static int errCounter;
    
    static void assert1(bool isPass, const std::string& testName, const std::vector<std::string>& errors);
    static void  finish();
};


#endif //EPIDEMICSPREADGRAPH_TESTMAIN_H
