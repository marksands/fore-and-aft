#include <iostream>
#include <sstream>

#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>

#include "TestRunner.hpp"

#include "Board.hpp"
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


TEST_GROUP(Board)
{
  Board *boardFiv;
  Board *boardSev;
  Board *boardNin;

  void setup()
  {
    boardFiv = new Board(5);
    boardSev = new Board(7);
    boardNin = new Board(9);
  }

  void teardown()
  {
    delete boardFiv;
    delete boardSev;
    delete boardNin;
  }

};

  TEST(Board, TestGridPlacement)
  {
    char fxf[] = "RRR00RRR00RRSBB00BBB00BBB";
    STRCMP_EQUAL( boardFiv->chargrid.c_str(), fxf );
    char sxs[] = "RRRR000RRRR000RRRR000RRRSBBB000BBBB000BBBB000BBBB";
    STRCMP_EQUAL( boardSev->chargrid.c_str(), sxs );
    char nxn[] = "RRRRR0000RRRRR0000RRRRR0000RRRRR0000RRRRSBBBB0000BBBBB0000BBBBB0000BBBBB0000BBBBB";
    STRCMP_EQUAL( boardNin->chargrid.c_str(), nxn );
  }

  TEST(Board, TestSwapShouldSwapTiles)
  {
    char beforeGrid[] = "RRR00RRR00RRSBB00BBB00BBB";
    char afterGrid[]  = "RRR00RRS00RRRBB00BBB00BBB";

    int bRow = 5/2;
    int bCol = 5/2;

    int aRow = 1;
    int aCol = 2;

    Board afterSwap( boardFiv->swap( Position(bRow, bCol), Position(aRow, aCol) ) );

    STRCMP_EQUAL( boardFiv->chargrid.c_str(), beforeGrid );
    STRCMP_EQUAL( afterSwap.chargrid.c_str(), afterGrid );

    CHECK_EQUAL( boardFiv->board[bRow][bCol], 'S' );
    CHECK_EQUAL( boardFiv->board[aRow][aCol], 'R' );

    CHECK_EQUAL( afterSwap.board[bRow][bCol], 'R' );
    CHECK_EQUAL( afterSwap.board[aRow][aCol], 'S' );
  }

  TEST(Board, TestNonReverseBoard)
  {
    Board b(5);
    STRCMP_EQUAL( b.chargrid.c_str(), "RRR00RRR00RRSBB00BBB00BBB");

    char nonReversedGrid[5][5] = {
      {'R','R','R','0','0' },
      {'R','R','R','0','0' },
      {'R','R','S','B','B' },
      {'0','0','B','B','B' },
      {'0','0','B','B','B' }
    };

    for ( int i = 0; i < 5; i++ ) {
      for ( int j = 0; j < 5; j++ )
        CHECK_EQUAL( b.board[i][j], nonReversedGrid[i][j] );
    }
  }

  TEST(Board, TestReverseBoard)
  {
    Board b(5);

    b.reverse();
    STRCMP_EQUAL( b.chargrid.c_str(), "BBB00BBB00BBSRR00RRR00RRR");

    char reversedGrid[5][5] = {
      {'B','B','B','0','0' },
      {'B','B','B','0','0' },
      {'B','B','S','R','R' },
      {'0','0','R','R','R' },
      {'0','0','R','R','R' }
    };

    for ( int i = 0; i < 5; i++ ) {
      for ( int j = 0; j < 5; j++ )
        CHECK_EQUAL( b.board[i][j], reversedGrid[i][j] );
    }
  }

  TEST(Board, TestOverloadedComparisonOperator)
  {
    Board fivBoardA(5);
    Board fivBoardB(5);
    CHECK(fivBoardA == fivBoardB);

    Board sevBoardA(7);
    CHECK(!(fivBoardA == sevBoardA));
  }

  TEST(Board, TestOverloadedOutputOperator)
  {
    Board b(5);

    std::stringstream s;
    s << b;

    std::string output;
    output = "[R][R][R][0][0]\n";
    output+= "[R][R][R][0][0]\n";
    output+= "[R][R][S][B][B]\n";
    output+= "[0][0][B][B][B]\n";
    output+= "[0][0][B][B][B]\n";

    CHECK_EQUAL( s.str(), output );
  }
