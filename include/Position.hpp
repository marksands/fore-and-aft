#pragma once
#ifndef POSITION_HPP
#define POSITION_HPP

#include <iostream>

using std::ostream;

  //------------------------------------------------------------------------------------
  // Class: Position
  // Stores the row and column of a position on the board
  //------------------------------------------------------------------------------------
class Position {
  public:
    Position() : row(0), col(0), size_(5) {}
    Position(int c, int r) : row(r), col(c) {}

    Position(const Position& copy) {
      row = copy.row;
      col = copy.col;
    }

      // set the row and column of the position
    void setPosition(int c, int r) { row = r; col = c; }
      // set the size of board 
    void setBoardSize(int size) { size_ = size; }

      // moves a position to the Position pos
    bool move(const Position& pos);
      // returns true if a position can move to Postion pos
    bool canMoveTo(const Position& pos);
      // validates the position
    bool valid();

      // overloaded plus-equals operater that increments a position to Position pos
    Position& operator+=(const Position& pos);

      // overloaded output operator that prints the Position
    friend ostream& operator<<(ostream& os, const Position& pos) {
      os << pos.col << ',' << pos.row;
      return os;
    }

      // overloaded comparison operator that returns true if Position lhs is equal to Position rhs
    friend bool operator==(const Position& lhs, const Position& rhs) {
      if ( lhs.row == rhs.row && lhs.col == rhs.col )
        return true;
      return false;
    }

      // returns a new position moved to Position pos
    Position movePositionTo(const Position& pos) const
    {
      Position p(*this);
      p += pos;
      return p;
    }

    int row;
    int col;

  private:
    int size_;
};

#endif