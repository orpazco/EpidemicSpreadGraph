#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    //ctor
    Tree(int rootLabel);
    //copy ctor
    virtual Tree* clone() const=0;
    Tree(const Tree &tree);
    //adders
    void addChild(const Tree &child);
    void addChild(Tree* child);
    static Tree* createTree(const Session& session, int rootLabel);
    static  Tree* findLeftChild(const vector<Tree*> &children);
    //dstrctr
    virtual ~Tree();
    //assign op
    Tree& operator=(const Tree& other);
    //getters
    const int& getNode() const ;
    const std::vector<Tree*>& getChildren() const;
    //trace
    virtual int traceTree()=0;



private:
    int node;
    std::vector<Tree*> children;

protected:
    void copyChildren(const Tree &other);
    void clear();
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
    virtual Tree* clone() const;

private:
    void findMaxRank(int currMax, int currMaxDepth, int depth, std::vector<Tree*> nodes) ;
};

class RootTree: public Tree{
public:
    //ctr
    RootTree(int rootLabel);
    //copy ctr
    virtual Tree* clone() const;
    //trace
    virtual int traceTree();
};

#endif
