#pragma once
#ifndef GAME_TREE_HPP
#define GAME_TREE_HPP

#include <iostream>
#include <list>

class Board;

class GameTree {
  public:
    GameTree(const Board& state) : state_(state) { }

    void pushTree(GameTree* tree) { children.push_back(tree); }
    int numChildren() const { return children.size(); }

  private:
    Board state_;
    std::list<GameTree*> children;
};

#endif