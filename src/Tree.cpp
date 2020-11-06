#include "../include/Tree.h"
#include "../include/Session.h"

// C'tor
Tree::Tree(int rootLabel): node(rootLabel) {}

// copy C'tor
Tree::Tree(const Tree &other){
    node = other.node;
    for (int i = 0; i<other.children.size(); i++){
        Tree* treeOther = other.children[i]->clone();
        children.push_back(treeOther);
    };
}

// move C'tor
Tree::Tree(const Tree&& other) {
    node = other.node;
    for (int i = 0; i<other.children.size(); i++){
        children.push_back(other.children[i]);
    };
}

// move assignment
const Tree & Tree::operator=(Tree &&other) {
    if (&other != this){
        clear();
        node = other.node;
        for (int i=0; i < other.children.size(); i++){
            children.push_back(other.children[i]);
            other.children[i] = nullptr;
        }
    }
    return *this;
}

//assignment
//TODO - Tomer
//destructor
//TODO - Tomer


void Tree::addChild(const Tree& child) {
    //TODO check
    children.push_back((Tree*)&child);
}

void Tree::addChild(Tree* child) {
    children.push_back(child);
}

// Create new tree in heap according to tree type
Tree* Tree::createTree(const Session &session, int rootLabel) {
    switch (session.getTreeType()) {
        case Cycle:
            return new CycleTree(rootLabel, session.getCycle());
        case MaxRank:
            return new MaxRankTree(rootLabel);
        case Root:
            return new RootTree(rootLabel);
    };
}

// Cycle Tree
CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle){}

int CycleTree::traceTree() {
    return traceTree(0);
}

int CycleTree::traceTree(int counter) {
    // if there is no children return this
    if (getChildren().empty()) {
        return getNode();
    }
    else{
        // get the most left child
        std::vector<Tree*> children = getChildren();
        // init left node
        int leftNode = children[0]->getNode();
        CycleTree* leftChild;
        // go through all the children and find the node with the min root node value
        for (int i = 0; i < children.size(); ++i) {
            int node = children[i]->getNode();
            if (node < leftNode){
                leftChild = (CycleTree*)children[i];
            }
        }

        // if we get to the curr cycle return the current left node
        if (counter == getCurrCycle())
            return getNode();

        // return the most left child of the sub-tree
        counter++;
        return leftChild->traceTree(counter);
    }
}

int CycleTree::getCurrCycle() const {
    return currCycle;
}

Tree * CycleTree::clone() {
    // create new cycle tree with the same node and currCycle
    CycleTree *newTree = new CycleTree(getNode(), getCurrCycle());
    // copy the tree children to the new tree
    newTree->copyChildren(*this);
    return newTree;
}


//MRT
//TODO - Tomer


//RT
//TODO - Tomer
