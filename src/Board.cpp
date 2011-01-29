#include "Board.hpp"
#include "GameTree.hpp"
#include "Global.hpp"

Board::Board(const int size) : size_(size)
{
  chargrid = "";
  for (int i = 0; i < size; ++i)
  {
    std::vector<char> b;
    for ( int j = 0; j < size; j++ )
    {
      if      ((i <= size/2) && (j <= size/2)) { b.push_back(RED);   chargrid += RED; }
      else if ((i >= size/2) && (j >= size/2)) { b.push_back(BLUE);  chargrid += BLUE; }
      else                                     { b.push_back(EMPTY); chargrid += EMPTY; }
    }
    board.push_back(b);
  }
  board[size/2][size/2] = START;
  chargrid[(size*size)/2] = START;
  emptySlotIndex.setPosition(size/2, size/2);
}

Board Board::swap(const Position& slot, const Position& token) const
{
  Board newBoard(*this);

  char temp = newBoard.board[slot.row][slot.col];

  newBoard.board[slot.row][slot.col] = newBoard.board[token.row][token.col];
  newBoard.chargrid[size_*slot.row + slot.col] = newBoard.board[token.row][token.col];

  newBoard.board[token.row][token.col] = temp;
  newBoard.chargrid[size_*token.row + token.col] = temp;

  return newBoard;
}

void Board::possibleStates(std::vector<Board>& states)
{
  states.clear();

  Position currentPosition(emptySlotIndex);
  currentPosition.setBoardSize(size_);

    // One Tile Moves
  if ( currentPosition.canMoveTo(MOVES[NORTH]) && tokenForPosition(currentPosition) == RED )
    states.push_back(swap(emptySlotIndex, MOVES[NORTH]));
  if ( currentPosition.canMoveTo(MOVES[EAST]) && tokenForPosition(currentPosition) == BLUE )
    states.push_back(swap(emptySlotIndex, MOVES[EAST]));
  if ( currentPosition.canMoveTo(MOVES[SOUTH]) && tokenForPosition(currentPosition) == BLUE )
    states.push_back(swap(emptySlotIndex, MOVES[SOUTH]));
  if ( currentPosition.canMoveTo(MOVES[WEST]) && tokenForPosition(currentPosition) == RED )
    states.push_back(swap(emptySlotIndex, MOVES[WEST]));

    // Two Tile Moves
  if ( currentPosition.canMoveTo(JUMPS[NORTH]) && tokenForPosition(currentPosition) == RED
      && tokenForPosition(Position(currentPosition.row+0, currentPosition.col-1)) == BLUE )
    states.push_back(swap(emptySlotIndex, JUMPS[NORTH]));
  if ( currentPosition.canMoveTo(JUMPS[EAST]) && tokenForPosition(currentPosition) == BLUE
      && tokenForPosition(Position(currentPosition.row+1, currentPosition.col+0)) == RED )
    states.push_back(swap(emptySlotIndex, JUMPS[EAST]));
  if ( currentPosition.canMoveTo(JUMPS[SOUTH]) && tokenForPosition(currentPosition) == BLUE
      && tokenForPosition(Position(currentPosition.row+0, currentPosition.col+1)) == RED )  
    states.push_back(swap(emptySlotIndex, JUMPS[SOUTH]));
  if ( currentPosition.canMoveTo(JUMPS[WEST]) && tokenForPosition(currentPosition) == RED
      && tokenForPosition(Position(currentPosition.row-1, currentPosition.col+0)) == BLUE )
    states.push_back(swap(emptySlotIndex, JUMPS[WEST]));
}

char Board::tokenForPosition(const Position& pos)
{
  return board[pos.row][pos.col];
}

  // recursive!!
void Board::play(const Board& currentState, GameTree& parent) const
{
  Board nextBoard(*this);
  //nextBoard.move(currentMove); // this advances the current state to the given move, do this #marksands

  std::auto_ptr<GameTree> node(new GameTree(nextBoard));

  //if ( nextBoard.state == goalstate ) {
  if (0) { //nextBoard.numPegs() == 1) {
    parent.pushTree(node.release());
    return;
  }

    // populate "states" (moves) with the possible moves avaialbe for this state
  std::vector<Board> states;
  nextBoard.possibleStates(states);

    // for each new possible state, play the move with the current board! (is this BFS?)
  for (u_int32 i = 0; i < states.size(); ++i) {
    nextBoard.play(states[i], *node);
  }

    // still not really sure what this does -_-
  if (node->numChildren() > 0) {
    parent.pushTree(node.release());
  }
}

ostream& operator<<(ostream& os, const Board& b)
{
  int boardCode = 0;
  for (int i = 0; i < b.size_; ++i)
  {
    os << setfill(' ') << setw(b.size_-i) << " ";
    for (int j = 0; j <= i; ++j)
    {
      os << b.board[i][j] << ' ';

      boardCode <<= 1;
      if (b.board[i][j]) boardCode |= 1;
    }
    os << endl;
  }
  return os;
}
