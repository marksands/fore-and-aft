#pragma once

#include <vector>
#include <stack>
#include <queue>
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

class PriorityQueue : public std::priority_queue<Board, std::vector<Board>, std::greater<Board>> {
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

  // helper method prints statistics about search
void printSearchStatistics(std::stack<Board> closed, size_t expandedNodes);


/*
 * @method
 *   void genericSearch(const Board& currentState, const Board& goalBoard )
 *     - performs a search on the board dependent on the data structure used
 *       accepting a Stack, Queue, or PriorityQueue for dfs, bfs, or A*
 *   Author: Mark Sands
 *   Date modified: 2-4-11
 */
template <class T>
void genericSearch(const Board& currentState, const Board& goalBoard )
{
    T open;
    open.push(currentState);
    std::stack<Board> closed;

    size_t expanded = 0;

    while ( !open.empty() )
    {
        Board currentBoard = open.Pop();
        closed.push(currentBoard);

        if (currentBoard == goalBoard)
            break;

        std::vector<Board> states;
        currentBoard.possibleStates(states);

        for (auto i : states) {
            expanded++;
            open.push(i);
        }
    }
    
    printSearchStatistics(closed, expanded);
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

/*
 * @method
 *   void printSearchStatistics(std::stack<Board> closed, size_t expandedNodes)
 *     - Prints the nodes and stats referring to the search
 *   Author: Mark Sands
 *   Date modified: 3-23-13
 */
void printSearchStatistics(std::stack<Board> closed, size_t expandedNodes)
{
    size_t count = 0;
    Board node = closed.top();
    
    while (node.parent_ != nullptr)
    {
        ++count;
        std::cout << node << std::endl;
        node = *node.parent_;
    }
    
    std::cout << std::setw(3) << ""
              << "Total nodes expanded: " << expandedNodes
              << std::endl << std::setw(3) << ""
              << "Total nodes: " << count
              << std::endl;
}