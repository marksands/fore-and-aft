#pragma once
#ifndef MOVE_HPP
#define MOVE_HPP

#include <iostream>
#include "Position.hpp"

class Move {
  public:
    Move(const Position& from, const Position& to)
      : from_(from), to_(to) { }

    friend ostream& operator<<(ostream& os, const Move& m) {
      os << "(" << m.from_ << ":" << m.to_ << ")";
      return os;
    }

    Position from_;
    Position to_;
};

#endif