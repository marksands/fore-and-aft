#include <stack>
#include <queue>
#include <memory>
#include <algorithm>
#include <cstring>
#include "Board.hpp"

extern Hash<std::string> hash;

/*
* @method
*   Board::Board() - Constructor initializes the board
*   Author: Mark Sands
*   Date modified: 2-3-11
*/
Board::Board(const u_int32 size) : parent_(NULL), solutionFound(false), size_(size)
{
  board.reserve(size*size);
  chargrid = "";

  u_int32 sized2 = size >> 1;

  for (u_int32 i = 0; i < size; ++i) {
    for ( u_int32 j = 0; j < size; j++ )
    {
      if      ((i <= sized2) && (j <= sized2)) { board.push_back(RED);   chargrid += RED;   }
      else if ((i >= sized2) && (j >= sized2)) { board.push_back(BLUE);  chargrid += BLUE;  }
      else                                     { board.push_back(EMPTY); chargrid += EMPTY; }
    }
  }

  board[(size*size) >> 1] = START;
  chargrid[(size*size) >> 1] = START;

  emptySlotIndex.setPosition(sized2, sized2);
}

/*
* @method
*   Board::Board() - Copy Constructor copies the board
*   Author: Mark Sands
*   Date modified: 2-3-11
*/
Board::Board(const Board& copy)
{
  if ( this != &copy) {
    parent_ = copy.parent_;
    size_ = copy.size_;
    chargrid = copy.chargrid;
    board = copy.board;
    emptySlotIndex = copy.emptySlotIndex;
  }
}


/*
* @method
*   Board Board::swap(Position slot, Position token)
*     - returns a new board with slot and token positions switched
*   Author: Mark Sands
*   Date modified: 2-3-11
*/
Board Board::swap(const Position& slot, const Position& token) const
{
  Board newBoard = *this;

  std::swap(newBoard.board[size_*slot.col + slot.row], newBoard.board[size_*token.col + token.row]);
  std::swap(newBoard.chargrid[size_*slot.col + slot.row], newBoard.chargrid[size_*token.col + token.row]);

    // update the emptySlotIndex, if that was a swapped tile
  if (newBoard.emptySlotIndex == slot)
    newBoard.emptySlotIndex = token;

  return newBoard;
}

/*
* @method
*   void Board::reverse() - reverses the board
*   Author: Mark Sands
*   Date modified: 2-2-11
*/
void Board::reverse()
{
  std::reverse( board.begin(), board.end() );
  std::reverse( chargrid.begin(), chargrid.end() );
}

/*
* @method
*   void Board::possibleStates(vector<Board> states)
*     - populates a vector<Board> with all possible neighbors of the board's current state
*   Author: Mark Sands
*   Date modified: 2-1-11
*/
void Board::possibleStates(std::vector<Board>& states)
{
  states.clear();

  u_int32 maxJumps = 4;

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

/*
* @method
*   char Board::tokenForPosition(Position pos)
*     - returns the character at the position on the board
*   Author: Mark Sands
*   Date modified: 1-25-11
*/
char Board::tokenForPosition(const Position& pos)
{
  return chargrid[size_*pos.col + pos.row];
}

/*
* @method
*   bool Board::validMoveToPosition(Position pos, CARDINAL_DIRECTIONS direction)
*     - validates the move from Position pos to a given Cardinal Direction
*   Author: Mark Sands
*   Date modified: 1-25-11
*/
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

/*
* @method
*   bool Board::validJumpToPosition(Position pos, CARDINAL_DIRECTIONS direction)
*     - validates the jump from Position pos to a given Cardinal Direction
*   Author: Mark Sands
*   Date modified: 1-25-11
*/
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

#if 0
/*
* @method
*   void Board::dfs(Board currentState, Board goalBoard)
*     - performs a recursive depth first search on the board
*   Author: Mark Sands
*   Date modified: 2-4-11
*/
void Board::dfs(Board& currentState, const Board& goalBoard)
{
  if ( !(currentState == goalBoard) )
  {
    if ( solutionFound ) return;

    std::vector<Board> states;
    currentState.possibleStates(states);

    for ( u_int32 i = 0; i < states.size(); i++ )
      dfs( states[i], goalBoard );
    return;
  }
  else {
 
   /**********************/
   /* Print the solution */
   /**********************/

    solutionFound = true;
    u_int32 count = 0;
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
#endif

/*
* @method
*   void Board::dfs(Board currentState, Board goalBoard)
*     - performs a depth first search on the board
*   Author: Mark Sands
*   Date modified: 2-4-11
*/
void Board::dfs(const Board& currentState, const Board& goalBoard)
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
void Board::bfs(const Board& currentState, const Board& goalBoard)
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

/*
* @method
*   ostream& operator<<(ostream& os, const Board& b)
*     - overloaded output operator pru_int32s the board
*   Author: Mark Sands
*   Date modified: 1-25-11
*/
ostream& operator<<(ostream& os, const Board& b)
{
  for ( u_int32 i = 0; i < b.size_; i++ ) {
    for ( u_int32 j = 0; j < b.size_; j++ )
      os << "" << b.board[b.size_*i+j] << " ";
    os << "\n";
  }
  return os;
}

/*
* @method
*   bool operator==(const Board& lhs, const Board& rhs)
*     - overloaded comparison operator returns if Board lhs is equal to Board rhs
*   Author: Mark Sands
*   Date modified: 1-29-11
*/
bool operator==(const Board& lhs, const Board& rhs)
{
  return hash.equalHash(lhs.chargrid, rhs.chargrid);
}

/*
* @method
*   Board& Board::operator=(const Board& rhs)
*     - overloaded assignment operator copies one board to another
*   Author: Mark Sands
*   Date modified: 1-25-11
*/
Board& Board::operator=(const Board& rhs)
{
  if ( this != &rhs) {
    parent_ = rhs.parent_;
    size_ = rhs.size_;
    chargrid = rhs.chargrid;
    board = rhs.board;
    emptySlotIndex = rhs.emptySlotIndex;
  }

  return *this;
}