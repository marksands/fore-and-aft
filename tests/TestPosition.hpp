#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>

#include "Global.hpp"
#include "Position.hpp"

TEST_GROUP(Position)
{
  Position *p;

  void setup()
  {
    p = new Position(2, 2);
    p->setBoardSize(5);
  }

  void teardown()
  {
    delete p;
  }

};

  TEST(Position, TestPositionIsValid)
  {
    CHECK( p->valid() );
  }

  TEST(Position, TestPositionCanMove)
  {
    for ( int i = 0; i < 8; i++ )
      CHECK( p->canMoveTo(MOVES[i]) );
  }

  TEST(Position, TestPositionCantMove)
  {
    p->setPosition(0,0);

    for ( int i = 0, j = -1; i < 8; i++, j-- )
      CHECK( !p->canMoveTo(Position(i,j)) );
  }

  TEST(Position, TestPlusEqualsOperatorFunctionsAsExpected)
  {
    p->operator+=(Position(1,1));

    LONGS_EQUAL( p->row, 2+1 )
    LONGS_EQUAL( p->col, 2+1 )
  }