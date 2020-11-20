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
    T_findLeftChild();
//    T_copyCtor_single();
//    T_moveCtor();
//    CT_traceTree();
//    CT_traceLessThanChildrenAmount();
    MRT_traceSameDepth();
    MRT_traceLesserDepth();
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
    TestMain::assert1(isPass, testName, errors);
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
    TestMain::assert1(isPass, __FUNCTION__, errors);
}

// region orpaz tests
void TreeTests::T_moveCtorMultChild() {}
void TreeTests::T_moveAssignSame() {}
void TreeTests::T_moveAssignDiff() {}
void TreeTests::T_moveChildren() {}

void TreeTests::T_findLeftChild() {
    bool isPass= true;
    std::vector<std::string> errors;
    Tree* tree1 = CreateTree::createTreeMultiChild(Cycle, 6, 2, 10);
    std::vector<Tree *> children1 =  tree1->getChildren();
    for (int i = 0; i < tree1->getChildrenSize(); i++) {
        CreateTree::addChild(children1[i], TreeType::Cycle, 2, (i+1)*10, 10);
    }

    Tree* tree2 = CreateTree::createTreeMultiChild(Cycle, 1, 1, 10);
    std::vector<Tree *> children2 =  tree2->getChildren();
    Tree* curr = children2[0];
    for (int i = 0; i < 5; ++i) {
        CreateTree::addChild(curr, Cycle, 1, i+3, 10);
        children2 =  curr->getChildren();
        curr = children2[0];
    }

    int left1 = tree1->traceTree();
    int left2 = tree2->traceTree();

    if (left1 != 10){
        isPass=false;
        errors.push_back("Expected left: 30, actual left: " + std::to_string(left1));
    }
    if (left2 != 7){
        isPass=false;
        errors.push_back("Expected left: 7, actual left: " + std::to_string(left2));
    }
    TestMain::assert1(isPass, __FUNCTION__, errors);

}

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
    TestMain::assert1(isPass, __FUNCTION__, errors);
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
    TestMain::assert1(isPass, __FUNCTION__, errors);
}
// endregion

// region help methods
void TreeTests::MRT_traceTree(int shallowChildren, int deepChildren, int depth) {
    bool isPass=true;
    std::vector<std::string> errors;
    int root = 0;
    int& children = shallowChildren;
    int& dChildren = deepChildren;
    int expected;
    switch (depth) {
        case 0:{ expected = 0;
            break;}
        default:expected = root+children+1;
    }
    Tree* currTree = CreateTree::createTreeMultiChild(MaxRank, children, root);
    CreateTree::addChildInDepth(currTree, MaxRank, dChildren, root+children+1, depth);
    int trace = currTree->traceTree();
    if (trace != expected){
        isPass=false;
        errors.push_back("Expected trace:"+  std::to_string(expected)+ ", actual trace: " + std::to_string(trace));
    }
    TestMain::assert1(isPass, __FUNCTION__ , errors);
}

void TreeTests::MRT_traceLesserDepth() {
    bool isPass=true;
    std::vector<std::string> errors;
    int root = 0;
    int children = 2;
    int dChildren = 5;
    Tree* currTree = CreateTree::createTreeMultiChild(MaxRank, children, root);
    CreateTree::addChildInDepth(currTree, MaxRank, dChildren, root+children+1, 1);
    CreateTree::addChildInDepth(currTree, MaxRank, dChildren, root+children+1+dChildren, 2);
    int trace = currTree->traceTree();
    if (trace != root+children+1){
        isPass=false;
        errors.push_back("Expected trace:"+  std::to_string(root+children+1)+ ", actual trace: " + std::to_string(trace));
    }
    TestMain::assert1(isPass, __FUNCTION__ , errors);
}



void TreeTests::MRT_traceSameDepth() {
    TreeTests::MRT_traceTree(3,3,0);
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
// endregion