//
// Created by Orpaz on 05/11/2020.
//
using namespace std;

#include "../include/Tree.h"

//Tree
//ctor
Tree::Tree(int rootLabel): node(rootLabel) {}

//copy ctor
Tree::Tree(const Tree &other){
    node = other.node;
    for (int i = 0; i<other.children.size(); i++){
        Tree* treeOther = other.children[i]->clone();
        children.push_back(treeOther);
    };
}

//assignment
//TODO - Tomer
//destructor
//TODO - Tomer
//movecon
//TODO - Orpaz
//moveass
//TODO - Orpaz

void Tree::addChild(const Tree& child) {
    //TODO check
    children.push_back((Tree*)&child);
}

void Tree::addChild(Tree* child) {
    children.push_back(child);
}

//CreateTree
Tree* Tree::createTree(const Session &session, int rootLabel) {
}

//TODO - Orpaz



//CT
//TODO - Orpaz


//MRT
//TODO - Tomer


//RT
//TODO - Tomer
