// objects are:
// PegBoard (the board itself with pins indicating position occupied)
// Position (a pair of row/col position on the board, or a relative position)
// Move (a pair of Positions, one absolute position, and other a direction
//       to move toward)
// GameTree (a tree starting from initial PegBoard that will contain all the
//           winning successive board positions as children, representing
//           the next logical board position from give one)
//

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <list>

#include "../include/ForeAft.hpp"

using std::vector;
using std::cin;

int main(int argc, char* argv[])
{
  int size = 5;
  cout << "boardsize: ";
  cin >> size;

  do {
    Board board(size);

    Board goalBoard(size);
    goalBoard.reverse();

    vector<Board> states;
    GameTree root(board);

    if (1) {
      Timer t;
      board.dfs(board, goalBoard);
    }

    cout << "boardsize or 0: ";
    cin >> size;
  } while ( size != 0 );

  return 0;
}