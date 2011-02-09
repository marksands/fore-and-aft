#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include "Board.hpp"

class BaseADT {
  public:
    virtual Board Pop() = 0;
    virtual Board Top() = 0;
};

class Stack : public BaseADT, public std::stack<Board> {
  public:
    Board Pop() {
      Board node = top(); pop();
      return node;
    }

    Board Top() {
      return top();
    }
};

class Queue : public BaseADT, public std::queue<Board> {
  public:
    Board Pop() {
      Board node = front(); pop();
      return node;
    }

    Board Top() {
      return front();
    }
};

struct comp { 
  bool operator()( Board lhs, Board rhs) {
    return (lhs.getfCost()+lhs.getgCost()) < (rhs.getfCost()+rhs.getgCost());
  }
};

class PriorityQueue : public BaseADT, public std::priority_queue< Board, std::vector< Board >, comp > {
  public:
    Board Pop() {
      Board node = top(); pop();
      return node;
    }

    Board Top() {
      return top();
    }
};

  // performs a depth first search on the board
void dfs(const Board& currentState, const Board& goalBoard);
  // performs a breadth first search on the board
void bfs(const Board& currentState, const Board& goalBoard);
  // performs a hueristic serach on the board
void heuristic(const Board& currentState, const Board& goalBoard);

  // One search algorithm to rule them all!
template <class T>
void genericSearch(const Board& currentState, const Board& goalBoard, T open )
{
  open->push(currentState);

  u_int32 expanded = 0;

  while ( !open->empty() )
  {
    Board currentBoard = open->Pop();

    if (currentBoard == goalBoard)
      break;

    std::vector<Board>* states = new std::vector<Board>;
    currentBoard.possibleStates(*states);

    u_int32 states_size = states->size();
    for ( u_int32 i = 0; i < states_size; i++ ) {
      expanded++;
      open->push(states->operator[](i));
    }
    delete states;
  }

  u_int32 count = 0;
  Board node = open->Top();

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
  Stack* s = new Stack;
  genericSearch( currentState, goalBoard, s );
  delete s;
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
  Queue* q = new Queue;
  genericSearch( currentState, goalBoard, q );
  delete q;
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
  PriorityQueue* pq = new PriorityQueue;
  genericSearch( currentState, goalBoard, pq );
  delete pq;
}


