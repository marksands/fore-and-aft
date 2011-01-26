#pragma once
#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <iomanip>
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

  private:
    // ????
    void flip(const Position& token) {
      //board[token.row][token.col] = EMPTY;
      //board[token.row][token.col].flip();
    }

    bool occupied(const Position& pos) const {
      return board[pos.row][pos.col];
    }

    std::vector<std::vector<char> > board;
};

  // this is here to avoid circular references
#include "GameTree.hpp"

Board::Board(const int size)
{
  for (int i = 0; i < size; ++i)
  {
    std::vector<char> b;
    for ( int j = 0; j < size; j++ )
    {
      if      ((i <= size/2) && (j <= size/2)) b.push_back(RED);
      else if ((i >= size/2) && (j >= size/2)) b.push_back(BLUE);
      else                                     b.push_back(EMPTY);
    }
    board.push_back(b);
  }
  board[size/2][size/2] = START;
}

void Board::possibleStates(std::vector<Move>& moves) const
{
  moves.clear();

  for(int i = 0; i < BoardSize::size(); i++) {
    for(int j = 0; j <= BoardSize::size(); j++)
    {
      Position empty(i,j);

      if (occupied(empty))
          continue;

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
}

void Board::move(const Move& move)
{
  Position t(move.from_);

  flip(t);
  t += move.to_;
  flip(t);
  t += move.to_;
  flip(t);
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