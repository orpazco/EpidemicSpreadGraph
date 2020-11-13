#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    // ctor
    Tree(int rootLabel);
    //copy ctor
    virtual Tree* clone() const=0;
    Tree(const Tree &tree);
    // move copy
    Tree(Tree&& other);

    //adders
    void addChild(const Tree &child);
    static Tree* findLeftChild(const std::vector<Tree*> &children);
    void addChild(Tree* child);
    static Tree* createTree(const Session& session, int rootLabel);

    //dstrctr
    virtual ~Tree();
  
    //getters
    const int& getNode() const ;
    const std::vector<Tree*>& getChildren() const;
    int getChildrenSize() const;
  
    //trace
    virtual int traceTree()=0;

    // assign op
    Tree& operator=(const Tree& other);
    // move assign op
    const Tree& operator=(Tree&& other);


private:
    int node;
    std::vector<Tree*> children;
    void moveChildren(Tree& other);

protected:
    void copyChildren(const Tree &other);
    void clear();
    
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    CycleTree(const CycleTree &other);
    CycleTree& operator=(const CycleTree& other);
    const CycleTree& operator=(CycleTree&& other);

    int getCurrCycle() const;
    virtual int traceTree();
    virtual Tree* clone() const;

private:
    int currCycle;
    int traceTree(int &counter);
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;

private:
    void findMaxRank(int* currMax, int* currMaxDepth, int depth, std::vector<Tree*>* nodes) ;

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
