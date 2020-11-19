#include <iostream>
#include <fstream>
#include "Tree.h"
#include "json.hpp"

#define JSON_PATH "output.json"

using namespace std;

int tree_exp1(){
    MaxRankTree t(1);
    MaxRankTree t2(2);
    t2.addChild(MaxRankTree(3));
    t2.addChild(MaxRankTree(4));
    t2.addChild(MaxRankTree(5));
    t.addChild(t2);
    t.addChild(MaxRankTree(6));
    return t.traceTree();
}


int main(int argc, char** argv){
    nlohmann::json j;
    j["tree1"] = tree_exp1();
    std::ofstream o(JSON_PATH);
    o << j << endl;
    return 0;
}
