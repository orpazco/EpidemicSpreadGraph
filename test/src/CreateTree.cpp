//
// Created by Orpaz on 08/11/2020.
//

#include "../include/CreateTree.h"
#include "../../include/Tree.h"

Tree * CreateTree::createTreeNoChild(TreeType type, int root) {
    return createTree(type, root);
}

Tree * CreateTree::createTreeOneChild(TreeType type, int root) {
    Tree* tree = createTree(type, root);
    Tree* tree1 = createTree(type, root+1);
    tree->addChild(tree1);
    return tree;
}

Tree * CreateTree::createTreeMultiChild(TreeType type, int numChild) {
    Tree* tree = createTree(type, 0);
    for (int i = 1; i <= numChild; i++) {
        Tree* child = createTree(type, i);
        tree->addChild(child);
    }
    return tree;
}

Tree * CreateTree::createTree(TreeType type, int depth, int numNodesLayer) {
    Tree* tree = createTree(type, 0);
    addLayer(tree, type, numNodesLayer, depth-1);
    return tree;
}

void CreateTree::addLayer(Tree *tree, TreeType type, int numChild, int depth) {
    for (int i = 1; i < numChild; ++i) {
        Tree* child = createTree(type, i);
        CreateTree::addLayer(child, type, numChild, depth--);
        tree->addChild(child);
    }
}

void CreateTree::addChild(Tree *tree, TreeType type, int numChild, int startNode) {
    for (int i = startNode; i < startNode+numChild; i++) {
        Tree* child = createTree(type, i);
        tree->addChild(child);
    }
}

Tree * CreateTree::createTree(TreeType type, int root) {
    switch (type) {
        case Cycle:
            return new CycleTree(root, 0);
        case MaxRank:
            return new MaxRankTree(root);
        case Root:
            return new RootTree(root);
    }
}

Tree * CreateTree::createTree(int root, int cycle) {
    return new CycleTree(root, cycle);
}