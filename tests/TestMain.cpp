// g++ tests.cpp  -I/Users/mark/Downloads/CppUTest-v2.3/include /Users/mark/Downloads/CppUTest-v2.3/lib/libCppUTest.a
#include <iostream>
#include <sstream>

#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>

#include "TestPosition.hpp"
#include "TestBoard.hpp"
#include "TestHash.hpp"

int main(int argc, char **argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}