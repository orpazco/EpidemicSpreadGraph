//
// Created by Orpaz on 07/11/2020.
//

#include "../include/TreeTests.h"
#include <string>
#include <vector>
#include "../include/TestMain.h"
#include "../include/CreateTree.h"

TreeTests::TreeTests(): RT_1(1), RT_2(2), RT_3(3) {
    //T_copyCtor_single();
    T_moveCtor();
}

void TreeTests::T_copyCtor_single() {
    bool isPass=true;
    std::string testName = "T_copyCtor_single";
    std::vector<std::string> errors;
    RootTree a(RT_1);
    int expected = a.getNode();
    int result = RT_1.getNode();
    if(expected!=result){
        isPass=false;
        errors.push_back("Expected node is:" + std::to_string(expected) + "received node:" + std::to_string(result));
    }
    std::vector<std::string> childrenDiff = childrenEqual(&RT_1, &a);
    if (!childrenDiff.empty())
        isPass= false;
    for (int i = 0; i < childrenDiff.size(); ++i) {
        errors.push_back(childrenDiff[i]);
    }
    TestMain::assert(isPass, testName, errors);
}

void TreeTests::T_moveCtor() {
    bool isPass=true;
    std::vector<std::string> errors;
    Tree* expected = CreateTree::createTreeNoChild(TreeType::Root, 0);
    Tree* actual = new RootTree(RootTree(0));
    if (expected->getNode() != actual->getNode()){
        isPass=false;
        errors.push_back("Expected node is:" + std::to_string(expected->getNode()) + "actual node is :" + std::to_string(actual->getNode()));
    }
    if (!actual->getChildren().empty()){
        isPass=false;
        errors.push_back("Expected children list: 0, actual children list size is: " + std::to_string(actual->getChildren().size()));
    }
    TestMain::assert(isPass, __FUNCTION__ , errors);
}