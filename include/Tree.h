#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    //ctor
    Tree(int rootLabel);
    //copy ctor
    virtual Tree* clone()=0;
    Tree(const Tree &tree);
    void copyChildren(const Tree &other);
    //adders
    void addChild(const Tree &child);
    void addChild(Tree* child);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    //dstrctr
    virtual ~Tree();
    void clear();
    void deleteChild(Tree* child);
    //assign op
    Tree& operator=(const Tree& other);
    //getters
    const int& getNode() const{
        return this->node;
    }

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
    //ctr
    RootTree(int rootLabel);
    //copy ctr
    Tree* clone();
    virtual int traceTree();
};

#endif