#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include "Board.hpp"

class Stack : public std::stack<Board> {
  public:
    Board Pop() {
      Board node = top(); pop();
      return node;
    }
    Board Top() { return top(); }
};

class Queue : public std::queue<Board> {
  public:
    Board Pop() {
      Board node = front(); pop();
      return node;
    }
    Board Top() { return front(); }
};

struct comp { 
  bool operator()( Board lhs, Board rhs) {
    return ( lhs.hCost() < rhs.hCost() );
  }
};

class PriorityQueue : public std::priority_queue< Board, std::vector< Board >, comp > {
  public:
    Board Pop() {
      Board node = top(); pop();
      return node;
    }
    Board Top() { return top(); }
};

  // performs a depth first search on the board
void dfs(const Board& currentState, const Board& goalBoard);
  // performs a breadth first search on the board
void bfs(const Board& currentState, const Board& goalBoard);
  // performs a hueristic serach on the board
void heuristic(const Board& currentState, const Board& goalBoard);

  // One search algorithm to rule them all!
template <class T>
void genericSearch(const Board& currentState, const Board& goalBoard )
{
  T open;
  open.push(currentState);
  std::stack<Board> closed;

  u_int32 expanded = 0;

  while ( !open.empty() )
  {
    Board currentBoard = open.Pop();
    closed.push(currentBoard);

    if (currentBoard == goalBoard)
      break;

    std::vector<Board> states;
    currentBoard.possibleStates(states);

    u_int32 states_size = states.size();
    for ( u_int32 i = 0; i < states_size; i++ ) {
      expanded++;
      // this doesn't make any sense. the fCost should print a reasonable value
      //std::cout << "YO: " << states[i].getfCost() << "\n";
      open.push(states[i]);
    }
  }

  u_int32 count = 0;
  Board node = closed.top();

  while( node.parent_ != NULL )
  {
    count++;
    std::cout << node << std::endl;
    node = *node.parent_;
  }

  std::cout << std::setw(3) << ""
    << "Total nodes expanded: " << expanded
    << std::endl << std::setw(3) << ""
    << "Total nodes: " << count
    << std::endl;
}

/*
* @method
*   void Board::dfs(Board currentState, Board goalBoard)
*     - performs a depth first search on the board
*   Author: Mark Sands
*   Date modified: 2-4-11
*/
void dfs(const Board& currentState, const Board& goalBoard)
{
  genericSearch<Stack>( currentState, goalBoard );
}

/*
* @method
*   void Board::bfs(Board currentState, Board goalBoard)
*     - performs a breadth first search on the board
*   Author: Mark Sands
*   Date modified: 2-4-11
*/
void bfs(const Board& currentState, const Board& goalBoard)
{
  genericSearch<Queue>( currentState, goalBoard );
}

/*
* @method
*   void Board::heuristic(Board currentState, Board goalBoard)
*     - performs a heuristic search on the board
*   Author: Mark Sands
*   Date modified: 2-7-11
*/
void heuristic(const Board& currentState, const Board& goalBoard)
{
  genericSearch<PriorityQueue>( currentState, goalBoard );
}


