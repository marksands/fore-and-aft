#pragma once
#ifndef GAME_TREE_HPP
#define GAME_TREE_HPP

#include <iostream>
#include <list>
#include "Board.hpp"

using std::cout;
using std::endl;

class GameTree {
  public:
    GameTree(const Board& state) : state_(state) { }

    void push(GameTree* tree) { children_.push_back(tree); }
    int numChildren() const { return children_.size(); }

    bool walk() { return GameTree::walk(*this); }

  private:
    static bool walk(GameTree& parent);

    Board state_;
    std::list<GameTree*> children_;
};

bool GameTree::walk(GameTree& parent)
{
  cout << parent.state_ << endl;

  std::list<GameTree*>::iterator firstChild = parent.children_.begin();
  if (firstChild == parent.children_.end())
  {
      cout << "========================" << endl;
      return true;
  }

  if (GameTree::walk(*(*firstChild)))
  {
      delete *firstChild;
      parent.children_.erase(firstChild);
  }

  return (parent.children_.begin() == parent.children_.end());
}

#endif