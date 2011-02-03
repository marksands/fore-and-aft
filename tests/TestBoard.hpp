#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>

#include "Board.hpp"

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

  #pragma mark TestGridPlacement
  TEST(Board, TestGridPlacement)
  {
    char fxf[] = "RRR00RRR00RRSBB00BBB00BBB";
    STRCMP_EQUAL( boardFiv->chargrid, fxf );
    char sxs[] = "RRRR000RRRR000RRRR000RRRSBBB000BBBB000BBBB000BBBB";
    STRCMP_EQUAL( boardSev->chargrid, sxs );
    char nxn[] = "RRRRR0000RRRRR0000RRRRR0000RRRRR0000RRRRSBBBB0000BBBBB0000BBBBB0000BBBBB0000BBBBB";
    STRCMP_EQUAL( boardNin->chargrid, nxn );
  }

  #pragma mark TestSwapShouldSwapTiles
  TEST(Board, TestSwapShouldSwapTiles)
  {
    char beforeGrid[] = "RRR00RRR00RRSBB00BBB00BBB";
    char afterGrid[]  = "RRR00RRS00RRRBB00BBB00BBB";

    int bRow = 5/2;
    int bCol = 5/2;

    int aCol = 1;
    int aRow = 2;

    Board afterSwap( boardFiv->swap( Position(bCol, bRow), Position(aCol, aRow) ) );

    STRCMP_EQUAL( boardFiv->chargrid, beforeGrid );
    STRCMP_EQUAL( afterSwap.chargrid, afterGrid );

    CHECK_EQUAL( boardFiv->board[bCol][bRow], 'S' );
    CHECK_EQUAL( boardFiv->board[aCol][aRow], 'R' );

    CHECK_EQUAL( afterSwap.board[bCol][bRow], 'R' );
    CHECK_EQUAL( afterSwap.board[aCol][aRow], 'S' );
  }

  #pragma mark TestNonReverseBoard
  TEST(Board, TestNonReverseBoard)
  {
    Board b(5);
    STRCMP_EQUAL( b.chargrid, "RRR00RRR00RRSBB00BBB00BBB");

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

  #pragma mark TestReverseBoard
  TEST(Board, TestReverseBoard)
  {
    Board b(5);

    b.reverse();
    STRCMP_EQUAL( b.chargrid, "BBB00BBB00BBSRR00RRR00RRR");

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

  #pragma mark TestOverloadedComparisonOperator
  TEST(Board, TestOverloadedComparisonOperator)
  {
    Board fivBoardA(5);
    Board fivBoardB(5);
    CHECK( fivBoardA == fivBoardB );
    //STRCMP_EQUAL( fivBoardA.chargrid, fivBoardB.chargrid)

    Board sevBoardA(7);
    CHECK( !(fivBoardA == sevBoardA) );
  }

  #pragma mark TestOverloadedOutputOperator
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

  #pragma mark TestPossibleStatesAreValid
  TEST(Board, TestPossibleStatesAreValid)
  {
      // a 4-state valid case
    Board a(5);

    CHECK( a.validMoveToPosition(MOVES[NORTH], NORTH) );
    CHECK( a.validMoveToPosition(MOVES[EAST], EAST) );
    CHECK( a.validMoveToPosition(MOVES[SOUTH], SOUTH) );
    CHECK( a.validMoveToPosition(MOVES[WEST], WEST) );

    CHECK(! a.validJumpToPosition(JUMPS[NORTH], NORTH) );
    CHECK(! a.validJumpToPosition(JUMPS[EAST], EAST) );
    CHECK(! a.validJumpToPosition(JUMPS[SOUTH], SOUTH) );
    CHECK(! a.validJumpToPosition(JUMPS[WEST], WEST) );

      // a 3-state valid case
    Board b = a.swap( Position(2,2), Position(3,2) );

    /*   0  1  2  3  4
      0 [R][R][R][0][0]
      1 [R][R][R][0][0]
      2 [R][R][B][S][B]
      3 [0][0][B][B][B]
      4 [0][0][B][B][B] */

    CHECK( !b.validMoveToPosition(MOVES[NORTH], NORTH) );
    CHECK(  b.validMoveToPosition(MOVES[EAST], EAST) );
    CHECK(  b.validMoveToPosition(MOVES[SOUTH], SOUTH) );
    CHECK( !b.validMoveToPosition(MOVES[WEST], WEST) );

    CHECK( !b.validJumpToPosition(JUMPS[NORTH], NORTH) );
    CHECK( !b.validJumpToPosition(JUMPS[EAST], EAST) );
    CHECK( !b.validJumpToPosition(JUMPS[SOUTH], SOUTH) );
    CHECK(  b.validJumpToPosition(JUMPS[WEST], WEST) );

      // a 3-state valid case
    Board c = a.swap( Position(2,2), Position(1,2) );

    /*   0  1  2  3  4
      0 [R][R][R][0][0]
      1 [R][R][R][0][0]
      2 [R][S][R][B][B]
      3 [0][0][B][B][B]
      4 [0][0][B][B][B] */

    CHECK(  c.validMoveToPosition(MOVES[NORTH], NORTH) );
    CHECK( !c.validMoveToPosition(MOVES[EAST], EAST) );
    CHECK( !c.validMoveToPosition(MOVES[SOUTH], SOUTH) );
    CHECK(  c.validMoveToPosition(MOVES[WEST], WEST) );

    CHECK( !c.validJumpToPosition(JUMPS[NORTH], NORTH) );
    CHECK(  c.validJumpToPosition(JUMPS[EAST], EAST) );
    CHECK( !c.validJumpToPosition(JUMPS[SOUTH], SOUTH) );
    CHECK( !c.validJumpToPosition(JUMPS[WEST], WEST) );

      // a 0-state valid case
    Board d = a.swap( Position(2,2), Position(0,0) );

    /*   0  1  2  3  4
      0 [S][R][R][0][0]
      1 [R][R][R][0][0]
      2 [R][R][R][B][B]
      3 [0][0][B][B][B]
      4 [0][0][B][B][B] */

    CHECK( !d.validMoveToPosition(MOVES[NORTH], NORTH) );
    CHECK( !d.validMoveToPosition(MOVES[EAST], EAST) );
    CHECK( !d.validMoveToPosition(MOVES[SOUTH], SOUTH) );
    CHECK( !d.validMoveToPosition(MOVES[WEST], WEST) );

    CHECK( !d.validJumpToPosition(JUMPS[NORTH], NORTH) );
    CHECK( !d.validJumpToPosition(JUMPS[EAST], EAST) );
    CHECK( !d.validJumpToPosition(JUMPS[SOUTH], SOUTH) );
    CHECK( !d.validJumpToPosition(JUMPS[WEST], WEST) );

      // a 2-state valid case
    Board e = a.swap( Position(2,2), Position(3,3) );

    /*   0  1  2  3  4
      0 [R][R][R][0][0]
      1 [R][R][R][0][0]
      2 [R][R][B][B][B]
      3 [0][0][B][S][B]
      4 [0][0][B][B][B] */

    CHECK( !e.validMoveToPosition(MOVES[NORTH], NORTH) );
    CHECK(  e.validMoveToPosition(MOVES[EAST], EAST) );
    CHECK(  e.validMoveToPosition(MOVES[SOUTH], SOUTH) );
    CHECK( !e.validMoveToPosition(MOVES[WEST], WEST) );

    CHECK( !e.validJumpToPosition(JUMPS[NORTH], NORTH) );
    CHECK( !e.validJumpToPosition(JUMPS[EAST], EAST) );
    CHECK( !e.validJumpToPosition(JUMPS[SOUTH], SOUTH) );
    CHECK( !e.validJumpToPosition(JUMPS[WEST], WEST) );
  }