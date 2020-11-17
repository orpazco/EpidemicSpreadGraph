#include <iostream>
#include "../include/Session.h"
#include "../include/Tree.h"

using namespace std;

int main(int argc, char** argv){
//    if(argc != 2){
//        cout << "usage cTrace <config_path>" << endl;
//        return 0;
//    }
    Session s("../jsons/examples/config1.json");
    s.simulate();
    return 0;

}
