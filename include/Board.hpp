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

class Board {
  public:
    Board(const int size = 5);
    Board(const Board& copy);

    virtual ~Board() {
      free(chargrid);
    }

    Board swap(const Position& slot, const Position& token) const;
    void reverse();

    void possibleStates(std::vector<Board>& states);

    void dfs(const Board& currentState, const Board& goalBoard);

    bool validMoveToPosition(const Position& pos, CARDINAL_DIRECTIONS direction);
    bool validJumpToPosition(const Position& pos, CARDINAL_DIRECTIONS direction);

    friend ostream& operator<<(ostream& os, const Board& b);
    friend bool operator==(const Board& lhs, const Board& rhs);

    char* chargrid;
    std::vector<std::vector<char> > board;

  private:
    char tokenForPosition(const Position& pos);

    Board *parent_;

    int size_;
    Position emptySlotIndex;
    Hash<char*> hash;
};

#endif