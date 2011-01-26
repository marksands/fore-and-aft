#pragma once
#ifndef POSITION_HPP
#define POSITION_HPP

#include <iostream>

#include "Boardsize.hpp"

using std::ostream;

class Position {
  public:
    Position() : row(0), col(0) {}
    Position(int r, int c) : row(r), col(c) {}

    bool move(const Position& pos);
    bool valid(const Position& pos);

    Position& operator+=(const Position& pos);

    friend ostream& operator<<(ostream& os, const Position& pos) {
      os << pos.row << ',' << pos.col;
      return os;
    }

    int row;
    int col;
};

/*
* @method
*   Position::valid() - validations the position of the token
* Author: Mark Sands
* Date modified: 1-25-11
*/
bool Position::valid(const Position& pos)
{
  if (pos.row <  0)                   return false;
  if (pos.col <  0)                   return false;
  if (pos.row >= BoardSize::size())   return false;
  if (pos.col >= BoardSize::size())   return false;
  if (pos.row <  BoardSize::size()/2
   && pos.col >  BoardSize::size()/2) return false;
  if (pos.row >  BoardSize::size()/2
   && pos.col <  BoardSize::size()/2) return false;

  return true;
}

/*
* @method
*   Position::move() - move the token to the given postition
* Author: Mark Sands
* Date modified: 1-25-11
*/
bool Position::move(const Position& pos)
{
  Position newPosition(*this);

  newPosition += pos;
  if ( !valid(newPosition) )
    return false;

  *this = newPosition;

  return true;
}

/*
* @method
*   Position::operator+=() - Increments the position by addition, returns the position
* Author: Mark Sands
* Date modified: 1-25-11
*/
Position& Position::operator+=(const Position& pos)
{
  row += pos.row;
  col += pos.col;

  return *this;
}

#endif