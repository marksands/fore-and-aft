#include <stack>
#include <queue>
#include <memory>
#include <algorithm>
#include <cstring>
#include "Board.hpp"

extern Hash<std::string> hash;

Board::Board(const int size) : parent_(NULL), solutionFound(false), size_(size)
{
  board.reserve(size*size);
  chargrid.resize(size*size);

  int sized2 = size >> 1;

  for (int i = 0; i < size; ++i) {
    for ( int j = 0; j < size; j++ )
    {
      int index = size*i+j;
      if      ((i <= sized2) && (j <= sized2)) { board[index] = RED;   chargrid[index] = RED;   }
      else if ((i >= sized2) && (j >= sized2)) { board[index] = BLUE;  chargrid[index] = BLUE;  }
      else                                     { board[index] = EMPTY; chargrid[index] = EMPTY; }
    }
  }

  board[(size*size) >> 1] = START;
  chargrid[(size*size) >> 1] = START;

  emptySlotIndex.setPosition(sized2, sized2);
}

Board::Board(const Board& copy)
{
  // *this = copy;

  if ( this != &copy) {
    parent_ = copy.parent_;
    size_ = copy.size_;
    chargrid = copy.chargrid;
    board = copy.board;
    emptySlotIndex = copy.emptySlotIndex;
  }
}

Board Board::swap(const Position& slot, const Position& token) const
{
  Board newBoard = *this;

  //std::cout << newBoard << std::endl;

  std::swap(newBoard.board[size_*slot.col + slot.row], newBoard.board[size_*token.col + token.row]);
  std::swap(newBoard.chargrid[size_*slot.col + slot.row], newBoard.chargrid[size_*token.col + token.row]);

    // update the emptySlotIndex, if that was a swapped tile
  if (newBoard.emptySlotIndex == slot)
    newBoard.emptySlotIndex = token;

  return newBoard;
}

void Board::reverse()
{
  std::reverse( board.begin(), board.end() );
  std::reverse( chargrid.begin(), chargrid.end() );
  //std::reverse( chargrid, &chargrid[ strlen( chargrid ) ] );
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
  return chargrid[size_*pos.col + pos.row];
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

void Board::dfs(Board& currentState, const Board& goalBoard)
{
  if ( !(currentState == goalBoard) )
  {
    if ( solutionFound ) return;

    std::vector<Board> states;
    currentState.possibleStates(states);

    for ( int i = 0; i < states.size(); i++ )
      dfs( states[i], goalBoard );
    return;
  }
  else {
    solutionFound = true;
    int count = 0;
    Board node = currentState;
    while( node.parent_ != NULL )
    {
      count++;
      std::cout << node << std::endl;
      node = *node.parent_;
    }

    std::cout << std::setw(3) << "";
    std::cout << "Total nodes: " << count << std::endl;
  }
}

/*
void Board::dfs(const Board& currentState, const Board& goalBoard)
{
  std::stack<Board> open;
  open.push(currentState);

  std::stack<Board> closed;

  while ( !open.empty() )
  {
    Board currentBoard = open.top(); open.pop();
    closed.push(currentBoard);

    std::cout << currentBoard.chargrid << "\n"
              << goalBoard.chargrid << "\n\n";
    //std::cout << currentBoard << std::endl << std::endl;

    if (currentBoard == goalBoard)
      break;

      // trying the heap instead, even though stack allocation is faster
    std::vector<Board>* states = new std::vector<Board>; // std::vector<Board> states;
    currentBoard.possibleStates(*states);

    u_int32 states_size = states->size();
    for ( u_int32 i = 0; i < states_size; i++ )
      open.push(states->operator[](i));

    delete states;
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
*/

void Board::bfs(const Board& currentState, const Board& goalBoard)
{
  std::queue<Board> open;
  open.push(currentState);

  while ( !open.empty() )
  {
    Board currentBoard( open.front() );

    std::cout << currentBoard << "\n\n";

    if (currentBoard == goalBoard)
      break;

     open.pop();

      // trying the heap instead, even though stack allocation is faster
    std::vector<Board>* states = new std::vector<Board>; // std::vector<Board> states;
    currentBoard.possibleStates(*states);

    u_int32 states_size = states->size();
    for ( u_int32 i = 0; i < states_size; i++ )
      open.push(states->operator[](i));

    delete states;
  }

  int count = 0;
  Board node( open.front() );
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
      os << "[" << b.board[b.size_*i+j] << "]";
    os << "\n";
  }
  return os;
}

bool operator==(const Board& lhs, const Board& rhs)
{
  return hash.equalHash(lhs.chargrid, rhs.chargrid);
  //return (bool)( 0 == strcmp(lhs.chargrid, rhs.chargrid) );
}

Board& Board::operator=(const Board& rhs)
{
  if ( this != &rhs) {
    parent_ = rhs.parent_;
    size_ = rhs.size_;
    //free(chargrid);
    //chargrid = (char*)malloc(size_*size_+1);
    //strcpy(chargrid, rhs.chargrid);
    chargrid = rhs.chargrid;
    board = rhs.board;
    emptySlotIndex = rhs.emptySlotIndex;
  }

  std::cout << board.size();
  std::cout << rhs.board.size();
  //std::cout << "Board " << *this << "\nrhsboard " << rhs << "\n";

  return *this;
}