//
// Created by Orpaz on 05/11/2020.
//
using namespace std;

#include "../include/Tree.h"

//Tree
//ctor
Tree::Tree(int rootLabel): node(rootLabel){}

//copy ctor
void Tree::copyChildren(const Tree &other){
    for (int i = 0; i<other.children.size(); i++){
        Tree* treeOther = other.getChildren()[i]->clone();
        children.push_back(treeOther);
    }
}

Tree::Tree(const Tree &other){
    node = other.node;//copies node and children
    copyChildren(other);
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

//destructor
void Tree::clear(){
    for(int i=0;i<children.size(); i++)
        delete(children[i]);//deep child deletion
}

Tree::~Tree(){
    clear();
}


// getters
const int& Tree::getNode() const{
    return node;
}

const vector<Tree*>& Tree::getChildren() const {
    return children;

}

//movecon
//TODO - Orpaz
//moveass
//TODO - Orpaz

void Tree::addChild(const Tree& child) {
    Tree* newTree = child.clone();
    children.push_back(newTree);
}

void Tree::addChild(Tree* child) {
    children.push_back(child);
}

//CreateTree
Tree* Tree::createTree(const Session &session, int rootLabel) {
    return 0;
}

//TODO - Orpaz



//CT
//TODO - Orpaz


//MRT
//ctor
MaxRankTree::MaxRankTree(int rootLabel): Tree(rootLabel) {}

//trace
int MaxRankTree::traceTree() {
    std::vector<Tree*> nodes;
    (findMaxRank(0,0,0, nodes));
    return findLeftChild(nodes)->getNode();
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
        findMaxRank(currMax, currMaxDepth, depth+1, nodes);
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

