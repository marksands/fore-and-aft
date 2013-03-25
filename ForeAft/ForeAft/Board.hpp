#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include <unordered_map>
#include "Position.hpp"

// Tokens
const char EMPTY = '#';
const char START = ' ';
const char RED   = 'R';
const char BLUE  = 'B';

// Directions NORTH, EASH, SOUTH, and WEST
enum CARDINAL_DIRECTIONS {
    NORTH = 0, EAST, SOUTH, WEST
};

// clockwise NORTH -> EAST -> SOUTH -> WEST
static const Position MOVES[] = {
    Position(+0,-1),
    Position(+1,+0),
    Position(+0,+1),
    Position(-1,+0)
};

// clockwise NORTH -> EAST -> SOUTH -> WEST
static const Position JUMPS[] = {
    Position(+0,-2),
    Position(+2,+0),
    Position(+0,+2),
    Position(-2,+0)
};

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
    explicit Board(const int size = 5);
    Board(const Board& copy);
    
    std::unordered_map<size_t, std::string> hash;
    std::hash<std::string> hash_function;

    virtual ~Board() { }

      // returns a new board with slot and token positions switched
    Board swap(const Position& slot, const Position& token);
      // reveresed the board
    void reverse();

      // returns the size of the board
    const int getSize() const;
      // distance a tile is from the closest corner
    void distance( const Position& pos );
      //  the heuristic cost, g(n) + f(n)
    void numberOfWrongTokens();

      //  a heuristic cost attribute, f(n)
    inline int getfCost() const;
      //  a heuristic cost attribute, g(n)
    inline int getgCost() const;
      //  the heuristic cost, g(n) + f(n)
    inline int gethCost() const;

      // helper function that adds a valid state to vector<Board> given the move and direction
    bool addState(std::vector<Board>& states, const Position& move, CARDINAL_DIRECTIONS direction);
      // populates a vector<Board> with all possible neighbors of the board's current state
    void possibleStates(std::vector<Board>& states);
      // validates the move from Position pos to a given Cardinal Direction
    bool validMoveToPosition(const Position& pos, CARDINAL_DIRECTIONS direction);
      // validates the jump from Position pos to a given Cardinal Direction
    bool validJumpToPosition(const Position& pos, CARDINAL_DIRECTIONS direction);

      // overloaded output operator pru_size_ts the board
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

    int fCost;
    int gCost;
    int size_;
    bool solutionFound;
    Position emptySlotIndex;
};
