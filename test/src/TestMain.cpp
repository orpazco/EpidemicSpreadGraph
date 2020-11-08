//
// Created by Orpaz on 07/11/2020.
//

#include <iostream>
#include "../include/TestMain.h"
void TestMain::assert(bool isPass, const std::string& testName) {
    if (isPass)
        std::cout << "Test " << testName << " Pass" << std::endl;
    else
        std::cout << "Test " << testName << " Fail" << std::endl;
}

void TestMain::assert(bool isPass, const std::string &testName, std::vector<std::string> errors) {
    if (isPass)
        std::cout << "Test " << testName << " Pass" << std::endl;
    else
        std::cout << "Test " << testName << " Fail" << std::endl;
}