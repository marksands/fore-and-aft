// objects are:
// PegBoard (the board itself with pins indicating position occupied)
// Position (a pair of row/col position on the board, or a relative position)
// Move (a pair of Positions, one absolute position, and other a direction
//       to move toward)
// GameTree (a tree starting from initial PegBoard that will contain all the
//           winning successive board positions as children, representing
//           the next logical board position from give one)
//
//

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <list>
#include <memory>

#include "ForeAft.hpp"

using namespace std;

// something like this?
bool JumpsForToken(char token) {
  //if ( Position(+0,-1).token != token ) return true;
  //if ( Position(+0,+1).token != token ) return true;
  //if ( Position(+1,+0).token != token ) return true;
  //if ( Position(-1,+0).token != token ) return true;
  return true;
}

// I'm 12 and what is this
//static const int NUMMOVEMENTS = sizeof(MOVES)/sizeof(Position);
static const int NUMMOVEMENTS = 8;

int main(int argc, char* argv[])
{
  int size = 5;
  //cin >> size;

  do {
    BoardSize::board_size = size;
    Board board(size);

    vector<Move> moves;
    board.possibleStates(moves);

    GameTree root(board);
    for (u_int32 i = 0; i < moves.size(); ++i) {
      board.play(moves[i], root);
    }

    //while (!root.walk());

    cin >> size;
  } while ( size != 0 );

  return 0;
}