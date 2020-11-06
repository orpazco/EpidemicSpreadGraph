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
Tree::Tree(Tree&& other) {
    node = other.node;
    moveChildren(other);
}

// move assignment
const Tree & Tree::operator=(Tree &&other) {
    if (&other != this){
        clear();
        children.clear();
        node = other.node;
        moveChildren(other);
    }
    return *this;
}

// copy the pointers of the children from other to this children vector
// used in move constructor and move assign
void Tree::moveChildren(Tree &other) {
    for (int i=0; i < other.children.size(); i++){
        children.push_back(other.children[i]);
        other.children[i] = nullptr;
    }
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

// get the most left child
Tree * Tree::findLeftChild(const std::vector<Tree*> &children) {
    // init left node
    int leftNode = children[0]->getNode();
    Tree* leftChild = children[0];
    // go through all the children and find the node with the min root node value
    for (int i = 1; i < children.size(); i++) {
        int node = children[i]->getNode();
        if (node < leftNode){
            leftChild = children[i];
        }
    }
    return leftChild;
}

// Cycle Tree
CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle){}

CycleTree::CycleTree(const CycleTree &other): Tree(other) {
    currCycle = other.getCurrCycle();
}

CycleTree & CycleTree::operator=(const CycleTree &other) {
    currCycle = other.getCurrCycle();
    Tree::operator=(other);
    return *this;
}

const CycleTree & CycleTree::operator=(CycleTree &&other) {
    currCycle = other.getCurrCycle();
    Tree::operator=(other);
    return *this;
}

int CycleTree::traceTree() {
    return traceTree(0);
}

int CycleTree::traceTree(int counter) {
    // if there is no children return this
    if (getChildren().empty()) {
        return getNode();
    }
    // if we get to the curr cycle return the current left node
    if (counter == getCurrCycle())
        return getNode();
    else {
        CycleTree* leftChild = (CycleTree*)findLeftChild(getChildren());

        // return the most left child of the sub-tree
        counter++;
        return leftChild->traceTree(counter);
    }
}

int CycleTree::getCurrCycle() const {
    return currCycle;
}

Tree * CycleTree::clone() {
    // create new cycle tree with the same node and currCycle (go to copy ctor)
    return new CycleTree(*this);
}


//MRT
//TODO - Tomer


//RT
//TODO - Tomer
