#pragma once
#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>

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
    Board(const int32 size = 5);
    Board(const Board& copy);

    virtual ~Board() { }

      // returns a new board with slot and token positions switched
    Board swap(const Position& slot, const Position& token) const;

      // reveresed the board
    void reverse();

      // returns the size of the board
    inline const int32 getSize() const {
      return size_;
    }

      // distance a tile is from the closest corner
    void distance( const Position& pos ) {

      // bottom-right corner
      //size_ * ((size_+1)/2) + (size_/2);

      // top-left cornerm blue
      //size_ * ((size_-1)/2) + (size_/2);

      if ( tokenForPosition(pos) == RED ) {
        //int a = (size_*pos.col + pos.row);
        int a = (size_*pos.row + pos.col);
        int b = (size_*((size_+1)/2) + (size_/2));
          if ( (a - b) <= 0 ) fCost = 0;
          else fCost = (a-b);
      }
      else if ( tokenForPosition(pos) == BLUE ) {
        //int a = (size_*pos.col + pos.row);
        int a = (size_*pos.row + pos.col);
        int b = (size_*((size_-1)/2) + (size_/2));
          if ( (a - b) <= 0 ) fCost = 0;
          else fCost = (a-b);
      }
      else {
        fCost = 0;
      }

      if (fCost < 0)
        throw std::runtime_error("F Cost is negative!");
    }

    void numberOfWrongTokens()
    {
      int32 shouldHave = ( ((size_+1)/2) * ((size_+1)/2) ) - 1;
      int32 doesHave = 0;

        // search only half the board
      for ( int32 i = 0; i < size_/2; i++ ){
        for (int32 j = 0; j < size_/2; j++ ) {
           if ( board[size_*i+j] == BLUE )
             doesHave++;
        }
      }

      gCost = shouldHave - doesHave;

      if (gCost < 0)
        throw std::runtime_error("G Cost is negative!");
    }

    inline const int32 getfCost() const {
      return fCost;
    }

    inline const int32 getgCost() const {
      return gCost;
    }

      //  the heuristic cost, g(n) + f(n)
    inline const int32 hCost() const {
      int32 hCost = getfCost() + getgCost();
      if (hCost < 0)
        throw std::runtime_error("H Cost is negative!");
      return hCost;
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
    char tokenForPosition(const Position& pos) const;

      // A*
    int32 fCost, gCost;

    bool solutionFound;
    int32 size_;
    Position emptySlotIndex;
};

#endif