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

const char* GRID[3] = {
  "RRR00RRR00RRSBB00BBB00BBB",
  "RRRR000RRRR000RRRR000RRRSBBB000BBBB000BBBB000BBBB",
  "RRRRR0000RRRRR0000RRRRR0000RRRRR0000RRRRSBBBB0000BBBBB0000BBBBB0000BBBBB0000BBBBB"
};
static int test_grid_size = 5;

TEST_GROUP(Board)
{

  Board *board;

  void setup()
  {
    board = new Board(test_grid_size);
  }

  void teardown()
  {
    delete board;
  }

    // Helper Method
  void nextBoard()
  {
    test_grid_size += 2;
    delete board;
    board = new Board(test_grid_size);
  }

};

  TEST(Board, SetupAndTestGridPlacement)
  {
    for ( int i = 0; i < 3; i++ ) {
      STRCMP_EQUAL( board->chargrid.c_str(), GRID[i] );
      nextBoard();
    }
  }


