#include "Position.hpp"

/*
* @method
*   Position::valid() - validations the position of the token
*   Author: Mark Sands
*   Date modified: 1-25-11
*/
bool Position::valid()
{
  int sized2 = size_ >> 1;
  if (row <  0)       return false;
  if (col <  0)       return false;
  if (row >= size_)   return false;
  if (col >= size_)   return false;
  if (row <  sized2
   && col >  sized2)  return false;
  if (row >  sized2
   && col <  sized2)  return false;

  return true;
}

/*
* @method
*   Position::move() - move the token to the given postition
*   Author: Mark Sands
*   Date modified: 1-25-11
*/
bool Position::move(const Position& pos)
{
  Position newPosition(*this);

  newPosition += pos;

  if ( !newPosition.valid() )
    return false;

  *this = newPosition;

  return true;
}

/*
* @method
*   Position::canMoveTo() - return true if the token can move to the new position
*   Author: Mark Sands
*   Date modified: 1-26-11
*/
bool Position::canMoveTo(const Position& pos)
{
  Position newPosition(*this);

  newPosition += pos;

  if ( !newPosition.valid() )
    return false;

  return true;
}

/*
* @method
*   Position::operator+=() - Increments the position by addition, returns the position
*   Author: Mark Sands
*   Date modified: 1-25-11
*/
Position& Position::operator+=(const Position& pos)
{
  row += pos.row;
  col += pos.col;

  return *this;
}
