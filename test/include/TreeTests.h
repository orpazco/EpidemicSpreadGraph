//
// Created by Orpaz on 07/11/2020.
//

#ifndef EPIDEMICSPREADGRAPH_TREETESTS_H
#define EPIDEMICSPREADGRAPH_TREETESTS_H
#include  "../../include/Tree.h"
#include <string>


class TreeTests {

public:
    TreeTests();
    // general Tree tests - using RT to initialize
    void T_copyCtor_single();
    void T_copyCtor_multi_1(RootTree a);
    void T_copyCtor_multi_2(RootTree a);
    void T_copyChildren(RootTree a); // check if children are copied from this to other, and other children are unreachable by this
    void T_assignmentOp(RootTree a); // check if other is cloned into this
    void T_moveCtor(); // check if other is moved (and deleted) to this
    void T_moveAssignSame(RootTree a); //  supposed to do nothing
    void T_moveAssignDiff(RootTree a); //  check if other is moved (and deleted) to this
    void T_clear(RootTree a); // check if this is  deleted
    void T_addChildConstRef(RootTree a);
    void T_addChildPointer(RootTree a);
    // RT tests
    void RT_clone(RootTree a);
    void RT_traceTree(RootTree a);

private:
    RootTree RT_1;
    RootTree RT_2;
    RootTree RT_3;
    static std::vector<std::string>  childrenEqual(Tree* a, Tree* b);
    static std::vector<std::string>  childrenSame(Tree* a, Tree* b);

};


#endif //EPIDEMICSPREADGRAPH_TREETESTS_H
