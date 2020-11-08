//
// Created by Orpaz on 07/11/2020.
//

#include <iostream>
#include "../include/TestMain.h"

void TestMain::start() {
    errCounter = 0;
}

void TestMain::assert(bool isPass, const std::string& testName) {
    assert(isPass, testName, {});
}

void TestMain::assert(bool isPass, const std::string &testName, const std::vector<std::string>& errors) {
    if (isPass)
        std::cout << "Test " << testName << " Pass" << std::endl;
    else {
        std::cout << "Test " << testName << " Fail" << std::endl;
        std::cout << "errors: " << std::endl;
        for (auto & error : errors) {
            errCounter++;
            std::cout << "--> " << error << std::endl;
        }
    }
}

void TestMain::finish() {
    std::cout << "finish all tests. \ntotal numbers of errors: " << errCounter;
}