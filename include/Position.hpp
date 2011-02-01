#pragma once
#ifndef POSITION_HPP
#define POSITION_HPP

#include <iostream>

using std::ostream;

class Position {
  public:
    Position() : row(0), col(0), size_(5) {}
    Position(int c, int r) : row(r), col(c) {}

    void setPosition(int c, int r) { row = r; col = c; }
    void setBoardSize(int size) { size_ = size; }

    bool move(const Position& pos);
    bool canMoveTo(const Position& pos);
    bool valid();

    Position& operator+=(const Position& pos);

    friend ostream& operator<<(ostream& os, const Position& pos) {
      os << pos.col << ',' << pos.row;
      return os;
    }

    friend bool operator==(const Position& lhs, const Position& rhs) {
      if ( lhs.row == rhs.row && lhs.col == rhs.col )
        return true;
      return false;
    }

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