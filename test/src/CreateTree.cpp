//
// Created by Orpaz on 08/11/2020.
//

#include "../include/CreateTree.h"

Tree * CreateTree::createTreeNoChild(TreeType type, int root, int currCycle) {
    return createTree(type, root, currCycle);
}

Tree * CreateTree::createTreeOneChild(TreeType type, int root, int currCycle) {
    Tree* tree = createTree(type, root, currCycle);
    Tree* tree1 = createTree(type, root+1, currCycle);
    tree->addChild(tree1);
    return tree;
}

Tree * CreateTree::createTreeMultiChild(TreeType type, int numChild, int root) {
    return CreateTree::createTreeMultiChild(type, numChild, root, 0);
}

Tree * CreateTree::createTreeMultiChild(TreeType type, int numChild, int root, int currCycle) {
    Tree* tree = createTree(type, root, currCycle);
    for (int i = root+1; i <= root+numChild; i++) {
        Tree* child = createTree(type, i, currCycle);
        tree->addChild(child);
    }
    return tree;
}


void CreateTree::addChild(Tree *tree, TreeType type, int numChild, int startNode, int currCycle) {
    for (int i = startNode; i < startNode+numChild; i++) {
        Tree* child = createTree(type, i, currCycle);
        tree->addChild(child);
    }
}

Tree * CreateTree::createTree(TreeType type, int root, int currCycle) {
    switch (type) {
        case Cycle:
            return new CycleTree(root, currCycle);
        case MaxRank:
            return new MaxRankTree(root);
        case Root:
            return new RootTree(root);
    }
}