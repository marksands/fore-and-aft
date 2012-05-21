/*--------------------------------------------------------------------------------\
*   File: main.cpp
*   Name: Mark Sands
*   Date: 2/04/11
* Course: CS 438 - AI
*   Desc: An implementation of various search algorithms that solve a fore-and-aft puzzle.
*  Tests: Build CppUTest, and define the CPPUTEST_HOME env in the Makefile, `make && ./test` to run
*    Run: `make production` and `./graph`
*
* Post Mortem: Below is a chart of information displaying the results I received on
*   testing my application. All results were tested on my MacBook Pro 2.4Ghz with 2GB of RAM,
*   my 9x9 was tested on a linode VPS server with unknown CPU/RAM.
*
*   Depth-First-Search:
*     5x5: Total nodes: 48
*            Total time: 0.00405 seconds
*     7x7: Total nodes: 131
*            Total time: 0.02966 seconds
*     9x9: Total nodes: 262
*            Total Time: 2.7889 seconds
*
*   Breadth-First-Search:
*     5x5: Total nodes: 46
*            Total time: 1.86468 seconds
*     7x7: ??
*     9x9: ??
*
*   In order for my 9x9 dfs to run, since it expands to over 2million nodes, I had to drastically increase
*   my stack and heap. It only ran about once on my local machine and ran a few times on my linode server.
*   My 5x5 bfs runs in about 1.8 seconds, but my 7x7 and 9x9 would not finish. If I had more time to refactor
*   my code, I believe I could have taken some measures to improve efficiency in both areas. One thing I wanted to
*   try but didn't have the time to, was using bitset instead as an alternative to my array and chargrid to see
*   dramatic improvements. I tried converting my character grid to a char* isntead of a std::string but the
*   improvements weren't anything special so I switched back to std::string. I also tried a recursive dfs solution
*   instead, but it was actually slower for me, so I retained my stack implementation.
*   Improvements that did work: A single dimensional array instead of a multi dimensional vector array, using
*   bitshift operations instead of dividing by 2, unrolling for loops, using a hashtable for O(1) lookup.
*
*
*   Heuristic Search:
*     7x7: Total nodes: 130
*            Total time: 0.047694 seconds
*     9x9: Total nodes: 262
*            Total Time: 0.1062621 seconds
*     11x11: Total nodes: 489
*              Total time: 0.546488 seconds
*
*
/--------------------------------------------------------------------------------/
*
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <stack>
#include <list>

#include "Hash.hpp"
Hash<std::string> hash;

#include "../include/ForeAft.hpp"

using std::vector;
using std::cin;

enum MenuOptions { DEPTH = 1, BREADTH = 2, HEURISTIC = 3, QUIT = 4 };
enum SizeOptoins { FIVE = 1, SEVEN =  2, NINE = 3, ELEV = 4, THIRT = 5 };

int SizeMenu();
int Menu();

void InitBoard( Board*& board );

void DepthFirstSearch( Board*& board );
void BreadthFirstSearch( Board*& board );
void HeuristicSearch( Board*& board );
void QuitProgram( Board*& board );


int main(int argc, char* argv[])
{
  int choice = 0;
  Board *board;

  void (*menuTable[5])( Board*& board ) = {
    0, &DepthFirstSearch, &BreadthFirstSearch, &HeuristicSearch, &QuitProgram
  };

  try {
    do {
      InitBoard( board );
      menuTable[ choice = Menu() ]( board );
      hash.clear();
    } while(choice != 4);
  }
  catch(std::exception &e) {
    std::cerr << "Error! " << e.what() << "\n";
    return EXIT_FAILURE;
  }
  catch(...) {
    std::cerr << "Error! Something REALLY BAD happend!\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/*
* @method
*   int SizeMenu()
*     - queries the user for the size of the board
*   Author: Mark Sands
*   Date modified: 2-4-11
*/
int SizeMenu()
{
  int choice;

  cout << endl
    << setw(3) << FIVE  << ". 5x5 Grid"
    << endl
    << setw(3) << SEVEN << ". 7x7 Grid"
    << endl
    << setw(3) << NINE  << ". 9x9 Grid"
    << endl
    << setw(3) << ELEV  << ". 11x11 Grid"
    << endl
    << setw(3) << THIRT  << ". 13x13 Grid"
    << endl
    << endl
    << setw(3) << " " << "Enter choice: ";
  cin >> choice;

  return (choice);
}

/*
* @method
*   int Menu()
*     - queries the user for search method or quit
*   Author: Mark Sands
*   Date modified: 2-4-11
*/
int Menu()
{
  int choice;

  cout << endl
    << setw(3) << DEPTH     << ". Depth-First Search"
    << endl
    << setw(3) << BREADTH   << ". Breadth-First Search"
    << endl
    << setw(3) << HEURISTIC << ". Heuristic Search"
    << endl
    << setw(3) << QUIT      << ". Quit"
    << endl
    << endl
    << setw(3) << " " << "Enter choice: ";
  cin >> choice;
  cout << endl;

  return (choice);
}

/*
* @method
*   int InitBoard()
*     - Initializes the board based on the size
*   Author: Mark Sands
*   Date modified: 2-4-11
*/
void InitBoard( Board*& board )
{
  int choice = 0;

  do {
    switch ( choice = SizeMenu() ) {
      case FIVE:
        board = new Board(5);
        break;
      case SEVEN:
        board = new Board(7);
        break;
      case NINE:
        board = new Board(9);
        break;
      case ELEV:
        board = new Board(11);
        break;
      case THIRT:
        board = new Board(13);
        break;
      default:
        board = new Board(5);
    }
  } while( choice == 0);
}

/*
* @method
*   void DepthFirstSearch()
*     - performs a depth first search on the board
*   Author: Mark Sands
*   Date modified: 2-4-11
*/
void DepthFirstSearch( Board*& board )
{
  Timer t;
  Board goalBoard(board->getSize()); goalBoard.reverse();
  dfs( *board, goalBoard );
  delete board;
}

/*
* @method
*   void DepthFirstSearch()
*     - performs a breadth first search on the board
*   Author: Mark Sands
*   Date modified: 2-4-11
*/
void BreadthFirstSearch( Board*& board )
{
  Timer t;
  Board goalBoard(board->getSize()); goalBoard.reverse();
  bfs( *board, goalBoard );
  delete board;
}

/*
* @method
*   void HeuristicSearch()
*     - performs an A* search on the board (not yet implemented)
*   Author: Mark Sands
*   Date modified: 2-4-11
*/
void HeuristicSearch( Board*& board )
{
  Timer t;
  Board goalBoard(board->getSize()); goalBoard.reverse();
  heuristic( *board, goalBoard );
  delete board;
}

/*
* @method
*   void QuitProgram() - deletes the board
*   Author: Mark Sands
*   Date modified: 2-4-11
*/
void QuitProgram( Board*& board )
{
  delete board;
}

