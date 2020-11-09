//
// Created by Orpaz on 07/11/2020.
//

#include "../include/TreeTests.h"
#include <string>
#include <vector>
#include "../include/CreateTree.h"

TreeTests::TreeTests(): RT_1(1), RT_2(2), RT_3(3) {
    startTests();
}

void TreeTests::startTests() {
    T_copyCtor_single();
    T_moveCtor();
    CT_traceTree();
    CT_traceLessThanChildrenAmount();
}

// TODO: not finish (tomer)
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

// orpaz
void TreeTests::T_moveCtor() {
    bool isPass=true;
    std::vector<std::string> errors;
    Tree* expected = CreateTree::createTreeNoChild(TreeType::Root, 0,0);
    Tree* actual = new RootTree(RootTree(0));
    if (!actual->getChildren().empty()){
        isPass=false;
        errors.push_back("Expected children list: 0, actual children list size is: " + std::to_string(actual->getChildren().size()));
    }
    isPass = compare(actual, expected, errors);
    TestMain::assert(isPass, __FUNCTION__ , errors);
}

//TODO: orpaz
void TreeTests::T_moveCtorMultChild() {}
void TreeTests::T_moveAssignSame() {}
void TreeTests::T_moveAssignDiff() {}

void TreeTests::T_moveChildren() {}
void TreeTests::T_findLeftChild() {}

void TreeTests::CT_traceTree() {
    bool isPass= true;
    std::vector<std::string> errors;
    // create tree
    Tree* tree = CreateTree::createTreeMultiChild(TreeType::Cycle, 5,0, 2);

    std::vector<Tree *> children =  tree->getChildren();
    // add to each child another child
    for (int i = 0; i < tree->getChildrenSize(); i++) {
        CreateTree::addChild(children[i], TreeType::Cycle, 2, (i+1)*10, 2);
    }
    int trace = tree->traceTree();
    if (trace !=10){
        isPass=false;
        errors.push_back("Expected trace: 10, actual trace: " + std::to_string(trace));
    }
    TestMain::assert(isPass, __FUNCTION__ , errors);
}

void TreeTests::CT_traceLessThanChildrenAmount() {
    bool isPass= true;
    std::vector<std::string> errors;
    int left = 5;
    int cycle = 3;
    int i = 0;
    // create tree
    Tree* currTree = CreateTree::createTreeNoChild(TreeType::Cycle, i, cycle);
    Tree* root = currTree;
    while (left > 0){
        i++;
        CreateTree::addChild(currTree, Cycle, 1, i, cycle);
        currTree = currTree->getChildren()[0];
        left--;
    }
    int trace = root->traceTree();
    if (trace != 3){
        isPass=false;
        errors.push_back("Expected trace: 2, actual trace: " + std::to_string(trace));
    }
    TestMain::assert(isPass, __FUNCTION__ , errors);
}

bool TreeTests::compare(Tree *actual, Tree *expected, std::vector<std::string> &errors) {
    bool isPass=true;
    if (expected->getNode() != actual->getNode()){
        isPass=false;
        errors.push_back("Expected node is:" + std::to_string(expected->getNode()) + "actual node is :" + std::to_string(actual->getNode()));
    }
    if (actual->getChildren().size() != expected->getChildren().size()){
        isPass=false;
        errors.push_back("Expected children size is:" + std::to_string(expected->getChildren().size()) + "actual size is :" + std::to_string(actual->getChildren().size()));
    }
    return isPass;
}

std::vector<std::string> TreeTests::childrenEqual(Tree *a, Tree *b) {
    return {};
}