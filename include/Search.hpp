#include <vector>
#include <stack>
#include <queue>
#include "Board.hpp"

  // performs a depth first search on the board
void dfs(const Board& currentState, const Board& goalBoard);
  // performs a breadth first search on the board
void bfs(const Board& currentState, const Board& goalBoard);


/*
* @method
*   void Board::dfs(Board currentState, Board goalBoard)
*     - performs a depth first search on the board
*   Author: Mark Sands
*   Date modified: 2-4-11
*/
void dfs(const Board& currentState, const Board& goalBoard)
{
  std::stack<Board> open;
  open.push(currentState);

  std::stack<Board> closed;

  u_int32 expanded = 0;

  while ( !open.empty() )
  {
    Board currentBoard = open.top(); open.pop();
    closed.push(currentBoard);

    if (currentBoard == goalBoard)
      break;

      // trying the heap instead, even though stack allocation is faster
    std::vector<Board>* states = new std::vector<Board>; // std::vector<Board> states;
    currentBoard.possibleStates(*states);

    u_int32 states_size = states->size();
    for ( u_int32 i = 0; i < states_size; i++ ) {
      expanded++;
      open.push(states->operator[](i));
    }

    delete states;
  }

  /**********************/
  /* Print the solution */
  /**********************/

  u_int32 count = 0;
  Board node = closed.top();

  while( node.parent_ != NULL )
  {
    count++;
    std::cout << node << std::endl;
    node = *node.parent_;
  }

  std::cout << std::setw(3) << "";
  std::cout << "Total nodes expanded: " << expanded << std::endl;
  std::cout << std::setw(3) << "";
  std::cout << "Total nodes: " << count << std::endl;
  
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
  std::queue<Board> open;
  open.push(currentState);

  u_int32 expanded = 0;

  while ( !open.empty() )
  {
    Board currentBoard( open.front() );

    if (currentBoard == goalBoard)
      break;

     open.pop();

      // trying the heap instead, even though stack allocation is faster
    std::vector<Board>* states = new std::vector<Board>; // std::vector<Board> states;
    currentBoard.possibleStates(*states);

    u_int32 states_size = states->size();
    for ( u_int32 i = 0; i < states_size; i++ ) {
      expanded++;
      open.push(states->operator[](i));
    }

    delete states;
  }

  /**********************/
  /* Print the solution */
  /**********************/

  u_int32 count = 0;
  Board node( open.front() );
  while( node.parent_ != NULL )
  {
    count++;
    std::cout << node << std::endl;
    node = *node.parent_;
  }

  std::cout << std::setw(3) << "";
  std::cout << "Total nodes expanded: " << expanded << std::endl;
  std::cout << std::setw(3) << "";
  std::cout << "Total nodes: " << count << std::endl;
}
