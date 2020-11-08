//
// Created by Orpaz on 07/11/2020.
//

#include "../include/TreeTests.h"
#include <string>
#include <vector>
#include "../include/TestMain.h"

TreeTests::TreeTests(): RT_1(1), RT_2(2), RT_3(3) {}

void TreeTests::T_copyCtor_single() {
    bool isPass=true;
    std::string testName = "T_copyCtor_single";
    std::vector<std::string> errors;
    RootTree a(RT_1);
    int expected = a.getNode();
    int result = RT_1.getNode();
    if(expected!=result){
        isPass=false;
        errors.push_back("Expected node is:" +std::to_string(expected) + "received node:" + std::to_string(result));
    }
    std::vector<std::string> childrenDiff = childrenEqual(&RT_1, &a);
    if (childrenDiff.size()!= 0 )
        isPass= false;
    for (int i = 0; i < childrenDiff.size(); ++i) {
        errors.push_back(childrenDiff[i]);
    }
    TestMain::assert(isPass, testName, errors);

}