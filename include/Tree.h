#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    // ctor
    Tree(int rootLabel);

    // copy ctor
    virtual Tree* clone()=0;
    Tree(const Tree &tree);
    void copyChildren(const Tree &other);
    // move copy
    Tree(const Tree&& other);

    //adders
    void addChild(const Tree &child);

    void addChild(Tree* child);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;

    // dstrctr
    virtual ~Tree();
    void clear();
    void deleteChild(Tree* child);

    // assign op
    Tree& operator=(const Tree& other);
    const Tree& operator=(Tree&& other);

    // getters
    const std::vector<Tree*>& getChildren() const;
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
    int getCurrCycle() const;
    int traceTree(int counter);
    virtual int traceTree();
    virtual Tree* clone();
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone();
};

class RootTree: public Tree{
public:
    //ctr
    RootTree(int rootLabel);
    //copy ctr
    virtual int traceTree();
    virtual Tree* clone();
};

#endif