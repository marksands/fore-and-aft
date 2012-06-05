#pragma once
#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>

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
    explicit Board(const int32 size = 5);
    Board(const Board& copy);

    virtual ~Board() { }

      // returns a new board with slot and token positions switched
    Board swap(const Position& slot, const Position& token);
      // reveresed the board
    void reverse();

      // returns the size of the board
    const int32 getSize() const;
      // distance a tile is from the closest corner
    void distance( const Position& pos );
      //  the heuristic cost, g(n) + f(n)
    void numberOfWrongTokens();

      //  a heuristic cost attribute, f(n)
    inline int32 getfCost() const;
      //  a heuristic cost attribute, g(n)
    inline int32 getgCost() const;
      //  the heuristic cost, g(n) + f(n)
    inline int32 gethCost() const;

      // populates a vector<Board> with all possible neighbors of the board's current state
    void possibleStates(std::vector<Board>& states);
      // validates the move from Position pos to a given Cardinal Direction
    bool validMoveToPosition(const Position& pos, CARDINAL_DIRECTIONS direction);
      // validates the jump from Position pos to a given Cardinal Direction
    bool validJumpToPosition(const Position& pos, CARDINAL_DIRECTIONS direction);

      // overloaded output operator pru_int32s the board
    friend ostream& operator<<(ostream& os, const Board& b);
      // overloaded comparison operator returns if Board lhs is equal to Board rhs
    bool operator==(const Board& rhs);
      // overloaded less than comparison operator returns if rhs is less than lhs
    inline bool operator<(const Board& rhs) const;
      // overloaded less than comparison operator returns if rhs is greater than lhs
    bool operator>(const Board& rhs) const;
      // overloaded assignment operator copies one board to another
    Board& operator=(Board rhs);

    std::vector<char> board;

    std::shared_ptr<Board> parent_;

  private:
    void somethingBad();
      // helper swap function
    void swap(Board &copy);
      // returns the character at the position on the board
    char tokenForPosition(const Position& pos) const;

    int32 fCost;
    int32 gCost;
    int32 size_;
    bool solutionFound;
    Position emptySlotIndex;
};

#endif