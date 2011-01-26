#include "Board.hpp"
#include "Position.hpp"

TEST_GROUP(Position)
{
  Position *p;

  void setup()
  {
    BoardSize::board_size = 5;
    p = new Position(2, 2);
  }

  void teardown()
  {
    delete p;
  }

};

  TEST(Position, PositionIsValid)
  {
    CHECK( p->valid() );
  }

  TEST(Position, PositionCanMove)
  {
    for ( int i = 0; i < 8; i++ )
      CHECK( p->canMoveTo(MOVES[i]) );
  }

  TEST(Position, PositionCantMove)
  {
    p->setPosition(0,0);

    for ( int i = 0, j = -1; i < 8; i++, j-- )
      CHECK( !p->canMoveTo(Position(i,j)) );
  }

  TEST(Position, PlusEqualsOperatorFunctionsAsExpected)
  {
    p->operator+=(Position(1,1));

    LONGS_EQUAL( p->row, 2+1 )
    LONGS_EQUAL( p->col, 2+1 )
  }

TEST_GROUP(Board)
{
  
  Board *board5;
  Board *board7;
  Board *board9;

  void setup()
  {
    board5 = new Board(5);
    board7 = new Board(7);
    board9 = new Board(9);    
  }

  void teardown()
  {
    delete board5;
    delete board7;
    delete board9;
  }

};

  TEST(Board, 5x5GridCorrectPlacement)
  {
    STRCMP_EQUAL( board5->chargrid.c_str(),
      "RRR00RRR00RRSBB00BBB00BBB")
  }

  TEST(Board, 7x7GridCorrectPlacement)
  {
    STRCMP_EQUAL( board7->chargrid.c_str(),
      "RRRR000RRRR000RRRR000RRRSBBB000BBBB000BBBB000BBBB")
  }

  TEST(Board, 9x9GridCorrectPlacement)
  {
    STRCMP_EQUAL( board9->chargrid.c_str(),
      "RRRRR0000RRRRR0000RRRRR0000RRRRR0000RRRRSBBBB0000BBBBB0000BBBBB0000BBBBB0000BBBBB")
  }
