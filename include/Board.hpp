#pragma once
#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "Position.hpp"
#include "Global.hpp"
#include "Hash.hpp"

using std::ostream;
using std::setfill;
using std::setw;
using std::cout;
using std::endl;

  //------------------------------------------------------------------------------------
  // Class: Board
  // Board stores the grid of the playing field
  //------------------------------------------------------------------------------------
class Board {
  public:
    Board(const u_int32 size = 5);
    Board(const Board& copy);

    virtual ~Board() { }

      // returns a new board with slot and token positions switched
    Board swap(const Position& slot, const Position& token) const;
      // reveresed the board
    void reverse();
      // returns the size of the board
    u_int32 getSize() { return size_; }

    void distance( const Position& pos ) {
      if ( tokenForPosition(pos) == RED ) {
        int a = (size_*pos.col + pos.row);
        int b = (size_*((size_/2)+1) + (size_/2));
        fCost = ( a - b ) < 0 ? 0 : (a - b);
      }
      else {
        int a = (size_*pos.col + pos.row);
        int b = (size_*((size_/2)-1) + (size_/2));
        fCost = ( a - b ) < 0 ? 0 : (a - b);
      }
    }

    void numberOfWrongTokens()
    {
      int shouldHave = ( ((int)(size_/2)+1) * ((int)(size_/2)+1) ) - 1;
      int doesHave = 0;

        // search only half the board
      for ( u_int32 i = 0; i < size_/2; i++ ){
        for (u_int32 j = 0; j < size_/2; j++ ) {
           if ( board[size_*i+j] == RED )
             doesHave++;
        }
      }
      gCost = shouldHave - doesHave;
    }

    int getfCost() {
      return fCost;
    }

      // one of my hueristic functions, number of wrong tokens
    int getgCost() {
      return gCost;
    }

      // populates a vector<Board> with all possible neighbors of the board's current state
    void possibleStates(std::vector<Board>& states);

      // validates the move from Position pos to a given Cardinal Direction
    bool validMoveToPosition(const Position& pos, CARDINAL_DIRECTIONS direction);
      // validates the jump from Position pos to a given Cardinal Direction
    bool validJumpToPosition(const Position& pos, CARDINAL_DIRECTIONS direction);

      // overloaded output operator pru_int32s the board
    friend ostream& operator<<(ostream& os, const Board& b);
      // overloaded comparison operator returns if Board lhs is equal to Board rhs
    friend bool operator==(const Board& lhs, const Board& rhs);

      // overloaded assignment operator copies one board to another
    Board& operator=(const Board& rhs);

    std::string chargrid;
    std::vector<char> board;

    Board *parent_;
  private:
      // returns the character at the position on the board
    char tokenForPosition(const Position& pos);

      // A*
    int fCost, gCost;

    bool solutionFound;
    u_int32 size_;
    Position emptySlotIndex;
};

#endif