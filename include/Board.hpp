#pragma once
#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

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

    Board swap(const Position& slot, const Position& token) const;

    void possibleStates(std::vector<Board>& states);
    void play(const Board& currentState, GameTree& parent) const;

    friend ostream& operator<<(ostream& os, const Board& b);

    std::string chargrid;
    std::vector<std::vector<char> > board;

  private:
    char tokenForPosition(const Position& pos);

    int size_;

    Position emptySlotIndex;
};

#endif