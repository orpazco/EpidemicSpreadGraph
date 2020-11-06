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
const Tree& Tree::operator=(Tree &&other) {
    if (&other != this){
        
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

//CT
//TODO - Orpaz


//MRT
//TODO - Tomer


//RT
//TODO - Tomer
