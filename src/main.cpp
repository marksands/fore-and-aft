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
#include <memory>

#include "../include/ForeAft.hpp"

using std::vector;
using std::cin;

int main(int argc, char* argv[])
{
  int size = 5;
  //cin >> size;

  do {
    Board board(size);

    vector<Board> states;
    board.possibleStates(states);

    GameTree root(board);
    for (u_int32 i = 0; i < states.size(); ++i) {
      board.play(states[i], root);
    }

    //while (!root.walk());

    cin >> size;
  } while ( size != 0 );

  return 0;
}