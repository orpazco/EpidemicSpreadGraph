#include "../include/Tree.h"
#include "../include/Session.h"

//Tree

//ctor
Tree::Tree(int rootLabel): node(rootLabel){}

//copy ctor
Tree::Tree(const Tree &other){
    node = other.node;//copies node and children
    copyChildren(other);
}

// move C'tor
Tree::Tree(Tree&& other) {
    node = other.node;
    moveChildren(other);
}

//assignment
Tree& Tree::operator=(const Tree &other) {
    if(this == &other)// checks for same obj assignment
        return *this;
    clear();
    node=other.node;
    children.clear();
    copyChildren(other);
    return *this;
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

//destructor
void Tree::clear(){
    for(int i=0;i<children.size(); i++)
        delete(children[i]);//deep child deletion
}

void Tree::copyChildren(const Tree &other){
    for (int i = 0; i<other.children.size(); i++){
        Tree* treeOther = other.getChildren()[i]->clone();
        children.push_back(treeOther);
    }
}

// copy the pointers of the children from other to this children vector
// used in move constructor and move assign
void Tree::moveChildren(Tree &other) {
    for (int i=0; i < other.children.size(); i++){
        children.push_back(other.children[i]);
        other.children[i] = nullptr;
    }
}

Tree::~Tree(){
    clear();
}


// getters

const int& Tree::getNode() const{
    return node;
}

const std::vector<Tree*>& Tree::getChildren() const {
    return children;

}

int Tree::getChildrenSize() const {
    return children.size();
}

void Tree::addChild(const Tree& child) {
    Tree* newTree = child.clone();
    children.push_back(newTree);
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

Tree * CycleTree::clone() const{
    // create new cycle tree with the same node and currCycle (go to copy ctor)
    return new CycleTree(*this);
}


//MRT
//ctor
MaxRankTree::MaxRankTree(int rootLabel): Tree(rootLabel) {}

//trace
int MaxRankTree::traceTree() {
    std::vector<Tree*> nodes; // nodes vector for storing MR candidates
    findMaxRank(0,0,0, nodes);// gets candidates
    return findLeftChild(nodes)->getNode();// returns the leftmost child in case of a tie
}


void MaxRankTree::findMaxRank(int currMax, int currMaxDepth , int depth, std::vector<Tree*> nodes)  {
    int currRank = getChildren().size();
    if (currRank>=currMax){
        if(currRank>currMax || depth<currMaxDepth){
            currMax = currRank;
            currMaxDepth = depth;
            nodes={this}; //candidate is largest or shallowest depth
        }
        else if (depth==currMaxDepth) //rank and depth equal
            nodes.push_back(this);
    }
    for(int i=0; i<getChildren().size(); i++) {
        findMaxRank(currMax, currMaxDepth, depth+1, nodes); //check children for candidates
    }
}

//clone
Tree* MaxRankTree::clone() const {
    MaxRankTree* clone = new MaxRankTree(*this);
    return clone;
}


//RT

//ctor
RootTree::RootTree(int rootLabel): Tree(rootLabel) {
}

//copy ctor
Tree* RootTree::clone() const{
    RootTree* clone = new RootTree(*this);
    return clone;
}


//trace
int RootTree::traceTree() {
    return getNode();
}

