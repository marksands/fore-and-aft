#include "Position.hpp"
#include "TestHelper.hpp"

TEST_GROUP(Position)
{
  Position *p;
  Position *badP;

  void setup()
  {
    BoardSize::board_size = 5;
    p = new Position(2, 2);
    badP = new Position(0, 0);
  }

  void teardown()
  {
    delete p;
    delete badP;
  }

};

  TEST(Position, PositionIsValid)
  {
    CHECK_EQUAL( p->valid(), true );
    CHECK_EQUAL( p->valid(), true );
  }

  TEST(Position, PositionCanMove)
  {
    for ( int i = 0; i < 8; i++ )
      CHECK_EQUAL( p->canMoveTo(MOVES[i]), true );
  }

  TEST(Position, PositionCantMove)
  {
    for ( int i = 0, j = -1; i < 8; i++, j-- )
      CHECK_EQUAL( badP->canMoveTo(Position(i,j)), false );
  }