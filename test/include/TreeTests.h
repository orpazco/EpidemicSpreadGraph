//
// Created by Orpaz on 07/11/2020.
//

#ifndef EPIDEMICSPREADGRAPH_TREETESTS_H
#define EPIDEMICSPREADGRAPH_TREETESTS_H
#include  "../../include/Tree.h"
#include "../include/TestMain.h"
#include <string>
#include <memory>


class TreeTests {

public:
    TreeTests();
    void startTests();

    // general Tree tests - using RT to initialize
    void T_copyCtor_single();
    void T_copyCtor_multi_1(RootTree a);
    void T_copyCtor_multi_2(RootTree a);
    void T_copyChildren();// check if children are copied from this to other, and other children are unreachable by this
    void T_moveChildren();
    void T_assignmentOp(); // check if other is cloned into this
    void T_moveCtor(); // check if other is moved (and deleted) to this
    void T_moveCtorMultChild();
    void T_moveAssignSame(); //  supposed to do nothing
    void T_moveAssignDiff(); //  check if other is moved (and deleted) to this
    void T_clear(RootTree a); // check if this is  deleted
    void T_addChildConstRef(RootTree a);
    void T_addChildPointer(RootTree a);
    // RT tests
    void RT_clone(RootTree a);
    void RT_traceTree(RootTree a);

    void T_findLeftChild();
    void CT_traceTree();
    void CT_traceLessThanChildrenAmount();
    void MRT_traceTree(int shallowChildren, int deepChildren, int depth);
    void MRT_traceSameDepth();
    void MRT_traceLesserDepth();

private:
    RootTree RT_1;
    RootTree RT_2;
    RootTree RT_3;

    bool compare(Tree* actual, Tree* expected, std::vector<std::string> &errors);
    static std::vector<std::string>  childrenEqual(Tree* a, Tree* b);
    static std::vector<std::string>  childrenSame(Tree* a, Tree* b);

};


#endif //EPIDEMICSPREADGRAPH_TREETESTS_H
