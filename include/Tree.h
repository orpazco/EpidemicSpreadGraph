#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    Tree(const Tree &tree);
    void addChild(const Tree& child);
    void addChild(Tree* child);

    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    virtual Tree* clone()=0;

private:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
};

#endif