#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>

#include "Board.hpp"
#include "Hash.hpp"

TEST_GROUP(Hash)
{

  void setup()
  {

  }

  void teardown()
  {

  }

};

  TEST(Hash, TestHashFunctionality)
  {
    Board board(5);

    Hash<char*> hash;
    hash.insertEntry(const_cast<char*>("RRR00RRR00RSB00BBB00BBB"));

    CHECK( hash.isThere(const_cast<char*>("RRR00RRR00RSB00BBB00BBB")) );
  }
