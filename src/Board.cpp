#include <stack>
#include <queue>
#include <memory>
#include "Board.hpp"
#include "GameTree.hpp"

Board::Board(const int size) : parent_(NULL), size_(size)
{
  board.reserve(size_);
  chargrid = "";

  for (int i = 0; i < size; ++i)
  {
    std::vector<char> b;
    b.reserve(size_);
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

  char temp = newBoard.board[slot.col][slot.row];

  newBoard.board[slot.col][slot.row] = newBoard.board[token.col][token.row];
  newBoard.chargrid[size_*slot.col + slot.row] = newBoard.board[token.col][token.row];

  newBoard.board[token.col][token.row] = temp;
  newBoard.chargrid[size_*token.col + token.row] = temp;

    // update the emptySlotIndex, if that was a swapped tile
  if (newBoard.emptySlotIndex == slot)
    newBoard.emptySlotIndex = token;

  return newBoard;
}

void Board::reverse()
{
  char temp;

  for ( int i = 0; i <= size_/2; i++ ) {
    for ( int j = 0; j <= size_/2; j++ ) {
      temp = board[i][j];

      board[i][j] = board[size_-j-1][size_-i-1];
      board[size_-j-1][size_-i-1] = temp;

      chargrid[i*size_ + j] = chargrid[size_*size_ - (i*size_+j) - 1];
      chargrid[size_*size_ - (i*size_+j) - 1] = temp;
    }
  }
}

void Board::possibleStates(std::vector<Board>& states)
{
  states.clear();

  int maxJumps = 4;

    /** One Tile Moves **/

  if ( validMoveToPosition(MOVES[NORTH], NORTH) ) {
    maxJumps--;
    Board temp = swap(emptySlotIndex, emptySlotIndex.movePositionTo(MOVES[NORTH]));
    std::auto_ptr<Board> node(new Board(*this));
    temp.parent_ = node.release();    
    if ( !hash.isThere(temp.chargrid) ) {
      hash.insertEntry(temp.chargrid);
      states.push_back(temp);
    }
  }

  if ( maxJumps == 0 ) return;
  if ( validMoveToPosition(MOVES[EAST], EAST) ) {
    maxJumps--;
    Board temp = swap(emptySlotIndex, emptySlotIndex.movePositionTo(MOVES[EAST]));
    std::auto_ptr<Board> node(new Board(*this));
    temp.parent_ = node.release();    
    if ( !hash.isThere(temp.chargrid) ) {
      hash.insertEntry(temp.chargrid);
      states.push_back(temp);
    }
  }

  if ( maxJumps == 0 ) return;
  if ( validMoveToPosition(MOVES[SOUTH], SOUTH) ) {
    maxJumps--;
    Board temp = swap(emptySlotIndex, emptySlotIndex.movePositionTo(MOVES[SOUTH]));
    std::auto_ptr<Board> node(new Board(*this));
    temp.parent_ = node.release();    
    if ( !hash.isThere(temp.chargrid) ) {
      hash.insertEntry(temp.chargrid);
      states.push_back(temp);
    }
  }

  if ( maxJumps == 0 ) return;
  if ( validMoveToPosition(MOVES[WEST], WEST) ) {
    maxJumps--;
    Board temp = swap(emptySlotIndex, emptySlotIndex.movePositionTo(MOVES[WEST]));
    std::auto_ptr<Board> node(new Board(*this));
    temp.parent_ = node.release();    
    if ( !hash.isThere(temp.chargrid) ) {
      hash.insertEntry(temp.chargrid);
      states.push_back(temp);
    }
  }

    /** Two Tile Moves **/

  if ( maxJumps == 0 ) return;
  if ( validJumpToPosition(JUMPS[NORTH], NORTH) ) {
    maxJumps--;
    Board temp = swap(emptySlotIndex, emptySlotIndex.movePositionTo(JUMPS[NORTH]));
    std::auto_ptr<Board> node(new Board(*this));
    temp.parent_ = node.release();    
    if ( !hash.isThere(temp.chargrid) ) {
      hash.insertEntry(temp.chargrid);
      states.push_back(temp);
    }
  }

  if ( maxJumps == 0 ) return;
  if ( validJumpToPosition(JUMPS[EAST], EAST) ) {
    maxJumps--;
    Board temp = swap(emptySlotIndex, emptySlotIndex.movePositionTo(JUMPS[EAST]));
    std::auto_ptr<Board> node(new Board(*this));
    temp.parent_ = node.release();    
    if ( !hash.isThere(temp.chargrid) ) {
      hash.insertEntry(temp.chargrid);
      states.push_back(temp);
    }
  }

  if ( maxJumps == 0 ) return;
  if ( validJumpToPosition(JUMPS[SOUTH], SOUTH) ) {
    maxJumps--;
    Board temp = swap(emptySlotIndex, emptySlotIndex.movePositionTo(JUMPS[SOUTH]));
    std::auto_ptr<Board> node(new Board(*this));
    temp.parent_ = node.release();    
    if ( !hash.isThere(temp.chargrid) ) {
      hash.insertEntry(temp.chargrid);
      states.push_back(temp);
    }
  }

  if ( maxJumps == 0 ) return;
  if ( validJumpToPosition(JUMPS[WEST], WEST) ) {
    maxJumps--;
    Board temp = swap(emptySlotIndex, emptySlotIndex.movePositionTo(JUMPS[WEST]));
    std::auto_ptr<Board> node(new Board(*this));
    temp.parent_ = node.release();    
    if ( !hash.isThere(temp.chargrid) ) {
      hash.insertEntry(temp.chargrid);
      states.push_back(temp);
    }
  }

}

char Board::tokenForPosition(const Position& pos)
{
  return board[pos.col][pos.row];
}

bool Board::validMoveToPosition(const Position& pos, CARDINAL_DIRECTIONS direction)
{
  Position newPosition(emptySlotIndex);
  newPosition.setBoardSize(size_);

  newPosition += pos;

  if ( !newPosition.valid() )
    return false;

  if (direction == NORTH || direction == WEST) {
    if ( tokenForPosition(newPosition) != RED )
      return false;
  } else {
    if ( tokenForPosition(newPosition) != BLUE )
      return false;
  }

  return true;
}

bool Board::validJumpToPosition(const Position& pos, CARDINAL_DIRECTIONS direction)
{
  Position newPosition(emptySlotIndex);
  Position jumpPosition(emptySlotIndex);

  newPosition.setBoardSize(size_);
  jumpPosition.setBoardSize(size_);

  newPosition += pos;

  if ( !newPosition.valid() )
    return false;

  if (direction == NORTH) {
    jumpPosition += Position(0,-1);
    if ( tokenForPosition(newPosition) != RED || tokenForPosition(jumpPosition) != BLUE )
      return false;
  }
  else if (direction == EAST) {
    jumpPosition += Position(1,0);
    if ( tokenForPosition(newPosition) != BLUE || tokenForPosition(jumpPosition) != RED )
      return false;
  }
  else if (direction == SOUTH) {
    jumpPosition += Position(0,1);
    if ( tokenForPosition(newPosition) != BLUE || tokenForPosition(jumpPosition) != RED )
      return false;
  }
  else if (direction == WEST) {
    jumpPosition += Position(-1,0);
    if ( tokenForPosition(newPosition) != RED || tokenForPosition(jumpPosition) != BLUE )
      return false;
  }

  return true;
}

// this is still not finding the direct path HOW TO DO?! ;_;
void Board::dfs(const Board& currentState, const Board& goalBoard)
{
  std::stack<Board> open;
  open.push(currentState);

  std::stack<Board> closed;

  while ( !open.empty() )
  {
    Board currentBoard = open.top(); open.pop();
    closed.push(currentBoard);

    if (currentBoard == goalBoard)
      break;

    std::vector<Board> states;
    currentBoard.possibleStates(states);

    for ( u_int32 i = 0; i < states.size(); i++ )
      open.push(states[i]);
  }

  int count = 0;
  Board node = closed.top();
  while( node.parent_ != NULL )
  {
    count++;
    std::cout << node << std::endl;
    node = *node.parent_;
  }

  std::cout << std::setw(3) << "";
  std::cout << "Total nodes: " << count << std::endl;
}

ostream& operator<<(ostream& os, const Board& b)
{
  for ( int i = 0; i < b.size_; i++ ) {
    for ( int j = 0; j < b.size_; j++ )
      os << "[" << b.board[i][j] << "]";
    os << "\n";
  }
  return os;
}

bool operator==(const Board& lhs, const Board& rhs)
{
  return (bool)(lhs.chargrid == rhs.chargrid);;
}