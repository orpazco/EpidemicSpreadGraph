//
// Created by Orpaz on 08/11/2020.
//

#ifndef EPIDEMICSPREADGRAPH_CREATETREE_H
#define EPIDEMICSPREADGRAPH_CREATETREE_H


#include "../../include/Tree.h"
enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class CreateTree {
public:
    static Tree* createTreeNoChild(TreeType type, int root);
    static Tree* createTreeOneChild(TreeType type, int root);
    static Tree* createTreeMultiChild(TreeType type, int numChild);
    static Tree* createTree(TreeType type, int depth, int numNodesLayer);
    static void addLayer(Tree* tree, TreeType type, int numChild, int depth);
    static void addChild(Tree* tree, TreeType type, int numChild, int startNode);

private:
    static Tree* createTree(TreeType type, int root);
    static Tree* createTree(int root, int cycle);
};


#endif //EPIDEMICSPREADGRAPH_CREATETREE_H
