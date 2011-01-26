#pragma once
#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "Global.hpp"
#include "Move.hpp"
#include "Position.hpp"

using std::ostream;
using std::setfill;
using std::setw;
using std::cout;
using std::endl;

class GameTree;

class Board {
  public:
    Board(const int size = 5);

    void possibleStates(std::vector<Move>& moves) const;
    void play(const Move& currentMove, GameTree& parent) const;
    void move(const Move& move);

    friend ostream& operator<<(ostream& os, const Board& b);

    std::string chargrid;

  private:
    char tokenForPosition(const Position& pos);

    Position emptySlotIndex;
    std::vector<std::vector<char> > board;
};

  // this is here to avoid circular references
#include "GameTree.hpp"

Board::Board(const int size)
{
  chargrid = "";
  for (int i = 0; i < size; ++i)
  {
    std::vector<char> b;
    for ( int j = 0; j < size; j++ )
    {
      if      ((i <= size/2) && (j <= size/2)) { b.push_back(RED);   chargrid += RED; }
      else if ((i >= size/2) && (j >= size/2)) { b.push_back(BLUE);  chargrid += BLUE; }
      else                                     { b.push_back(EMPTY); chargrid += EMPTY; }
    }
    board.push_back(b);
  }
  board[size/2][size/2] = START;
  chargrid[(size*size)/2] = START;
  emptySlotIndex.setPosition(size/2, size/2);
}

void Board::possibleStates(std::vector<Move>& moves) const
{
  moves.clear();

  Position currentPosition(emptySlotIndex);
  /*
  for ( int i = 0 ; i < NUMBER_OF_MOVES/2; i++ ) {
    if ( currentPosition.canMoveTo(MOVES[i]) && tokenForPosition(currentPosition) == RED )
      moves.push_back(Move(emptySlotIndex, MOVES[i]));
  }

  for ( int i = 2 ; i < NUMBER_OF_MOVES; i++ ) {
    if ( currentPosition.canMoveTo(MOVES[i]) && tokenForPosition(currentPosition) == RED )
      moves.push_back(Move(emptySlotIndex, MOVES[i]));
  }

  Position currentPosition(emptySlotIndex);
  if ( currentPosition.canMoveTo(MOVES[0]) ) {
    currentPosition.move(MOVES[0]);
    if ( tokenForPosition(MOVES[NORTH]) == RED )
      // PASS
  }

  Position currentPosition(emptySlotIndex);
  if ( currentPosition.canMoveTo(JumpNorth) )

  JumpEast(+2,+0);
  JumpSouth(+0,+2);
  JumpWest(-2,+0);

      for(int m = 0; m < 4; m++)
      {
        Position move(empty);
        if (move.move(MOVES[m]) && occupied(move) &&
            move.move(MOVES[m]) && occupied(move))
        {
          Position direction(MOVES[m]);
          moves.push_back(Move(move, direction));
        }
      }
    }
  }
  */
}

char Board::tokenForPosition(const Position& pos)
{
  return board[pos.row][pos.col];
}

void Board::move(const Move& move)
{
  Position t(move.from_);

  t += move.to_;
  t += move.to_;
}

  // recursive!!
void Board::play(const Move& currentMove, GameTree& parent) const
{
  Board nextBoard(*this);
  nextBoard.move(currentMove); // this advances the current state to the given move, do this #marksands

  std::auto_ptr<GameTree> node(new GameTree(nextBoard));

  //if ( nextBoard.state == goalstate ) {
  if (0) { //nextBoard.numPegs() == 1) {
    parent.pushTree(node.release());
    return;
  }

    // populate "states" (moves) with the possible moves avaialbe for this state
  std::vector<Move> moves;
  nextBoard.possibleStates(moves);

    // for each new possible state, play the move with the current board! (is this BFS?)
  for (u_int32 i = 0; i < moves.size(); ++i) {
    nextBoard.play(moves[i], *node);
  }

    // still not really sure what this does -_-
  if (node->numChildren() > 0) {
    parent.pushTree(node.release());
  }
}

ostream& operator<<(ostream& os, const Board& p)
{
  int boardCode = 0;
  for (int i = 0; i < BoardSize::size(); ++i)
  {
    os << setfill(' ') << setw(BoardSize::size()-i) << " ";
    for (int j = 0; j <= i; ++j)
    {
      os << p.board[i][j] << ' ';

      boardCode <<= 1;
      if (p.board[i][j]) boardCode |= 1;
    }
    os << endl;
  }
  return os;
}

#endif