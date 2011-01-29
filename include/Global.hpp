#pragma once
#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "Position.hpp"

typedef unsigned long int u_int32;
typedef long int int32;

const char EMPTY = '0';
const char START = 'S';
const char RED   = 'R';
const char BLUE  = 'B';

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

#endif