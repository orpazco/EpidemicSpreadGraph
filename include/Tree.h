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
    Tree(Tree&& other);

    //adders
    void addChild(const Tree &child);
    static Tree* findLeftChild(const std::vector<Tree*> &children);

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
    void moveChildren(Tree& other);
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    CycleTree(const CycleTree &other);
    CycleTree& operator=(const CycleTree& other);
    const CycleTree& operator=(CycleTree&& other);

    int getCurrCycle() const;
    virtual int traceTree();
    virtual Tree* clone();

private:
    int currCycle;
    int traceTree(int counter);
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