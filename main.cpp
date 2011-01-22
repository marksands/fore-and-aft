#include <iostream>
#include <iomanip>
#include "AdjacencyList.hpp"

/*
* @prototypes
*/
int InitMenu();


int main(int argc, char* argv[])
{  
  /* - menu choice, board size, and the graph */
  int choice = 0;
  u_int size = 5;
  Graph<int>* board;

  /* - query the user for the board size & initialize the graph with size */
  size = InitMenu();
  board = new Graph<int>(size);

  /* - query the user for the board size & initialize the graph with size */
  board->addNode( 0, 1 );
  board->addNode( 1, 1 );
  board->addNode( 2, 1 );
  board->addNode( 3, 1 );
  board->addNode( 4, 1 );

  delete board;

  return 0;
}

/*
* @methods
*   - query the user for the board size
*   - return the size, ensuring a size of 5
*/
int InitMenu()
{
  int choice;

  std::cout << std::endl
     << std::setw(3) << "" << "Initialize the board size"
     << std::endl
     << std::setw(3) << " " << "Enter: ";
  std::cin >> choice;

  return ( choice < 5 ? 5 : choice );
}