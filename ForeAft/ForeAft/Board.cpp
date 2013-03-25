#include <stack>
#include <queue>
#include <memory>
#include <cstring>
#include <memory>
#include "Board.hpp"
#include <algorithm>

/*
* @method
*   Board::Board() - Constructor initializes the board
*   Author: Mark Sands
*   Date modified: 2-3-11
*/
Board::Board(const int size) : parent_(nullptr), fCost(999), gCost(999), size_(size), solutionFound(false)
{
    int sized2 = size >> 1;

    board.reserve((size_t)(sized2));

    for (int i = 0; i < size; ++i) {
        for ( int j = 0; j < size; j++ )
        {
            if      ((i <= sized2) && (j <= sized2)) { board.push_back(RED);  }
            else if ((i >= sized2) && (j >= sized2)) { board.push_back(BLUE); }
            else                                     { board.push_back(EMPTY);}
        }
    }

    board[(size_t)((sized2) >> 1)] = START;
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
    board = copy.board;
    emptySlotIndex = copy.emptySlotIndex;
  }
  else {
    throw std::runtime_error("Tried to copy board of same board!");
  }
}


/*
* @method
*   Board Board::swap(Position slot, Position token)
*     - returns a new board with slot and token positions switched
*   Author: Mark Sands
*   Date modified: 2-3-11
*/
Board Board::swap(const Position& slot, const Position& token)
{
    Board newBoard(*this);

    std::swap(newBoard.board[(size_t)(size_*slot.col + slot.row)],
              newBoard.board[(size_t)(size_*token.col + token.row)]);

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
}

bool Board::addState(std::vector<Board>& states, const Position& move, CARDINAL_DIRECTIONS direction)
{
    if (validMoveToPosition(move, direction))
    {
        Board temp = swap(emptySlotIndex, emptySlotIndex.movePositionTo(move));
        if (hash.find(hash_function(&board[0])) == hash.end())
        {
            std::shared_ptr<Board> node(new Board(*this));
            temp.parent_ = node;
        
            // generate heuristic
            temp.distance(emptySlotIndex);
            temp.numberOfWrongTokens();
            hash.insert({hash_function(&board[0]), &board[0]});
            states.push_back(temp);
        
            return true;
        }
    }
    return false;
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
    size_t maxJumps = 4;

    if ( addState(states, MOVES[NORTH], NORTH) ) {
        maxJumps--;
    }
    
    if (maxJumps > 0 && addState(states, MOVES[EAST], EAST)) {
        maxJumps--;
    }
    
    if (maxJumps > 0 && addState(states, MOVES[SOUTH], SOUTH)) {
        maxJumps--;
    }
    
    if (maxJumps > 0 && addState(states, MOVES[WEST], WEST)) {
        maxJumps--;
    }
    
    if (maxJumps > 0 && addState(states, JUMPS[NORTH], NORTH)) {
        maxJumps--;
    }
    
    if (maxJumps > 0 && addState(states, JUMPS[EAST], EAST)) {
        maxJumps--;
    }
    
    if (maxJumps > 0 && addState(states, JUMPS[SOUTH], SOUTH)) {
        maxJumps--;
    }
    
    if (maxJumps > 0 && addState(states, JUMPS[WEST], WEST)) {
        maxJumps--;
    }
}

/*
* @method
*   char Board::tokenForPosition(Position pos)
*     - returns the character at the position on the board
*   Author: Mark Sands
*   Date modified: 1-25-11
*/
char Board::tokenForPosition(const Position& pos) const
{
    return board[(size_t)(size_*pos.col + pos.row)];
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

/*
* @method
*   ostream& operator<<(ostream& os, const Board& b)
*     - overloaded output operator prints the board
*   Author: Mark Sands
*   Date modified: 1-25-11
*/
ostream& operator<<(ostream& os, const Board& b)
{
    for ( int i = 0; i < b.size_; i++ ) {
        for ( int j = 0; j < b.size_; j++ )
            os << "" << b.board[(size_t)(b.size_*i+j)] << " ";
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
bool Board::operator==(const Board& rhs)
{
  // This doesn't work. I might need to rethink if hashing is working..
  //return (boardToString(board) == boardToString(rhs.board));
    
    return hash_function(&rhs.board[0]) == hash_function(&board[0]);
}

  // returns the size of the board
const int Board::getSize() const
{
    return size_;
}

  // distance a tile is from the closest corner
void Board::distance( const Position& pos )
{
    if ( tokenForPosition(pos) == RED ) {
        int a = (size_*pos.row + pos.col);
        int b = (size_*((size_+1)/2) + (size_/2));
        if ( (a - b) <= 0 ) fCost = 0;
        else fCost = (a-b);
    }
    else if ( tokenForPosition(pos) == BLUE ) {
        int a = (size_*pos.row + pos.col);
        int b = (size_*((size_-1)/2) + (size_/2));
        if ( (a - b) <= 0 ) fCost = 0;
        else fCost = (a-b);
    }
    else {
        fCost = 0;
    }

    if (fCost < 0)
        throw std::runtime_error("F Cost is negative!");
}

void Board::numberOfWrongTokens()
{
    int shouldHave = ( ((size_+1)/2) * ((size_+1)/2) ) - 1;
    int doesHave = 0;

    // search only half the board
    for ( int i = 0; i < size_/2; i++ ){
        for (int j = 0; j < size_/2; j++ ) {
            if ( board[(size_t)(size_*i+j)] == BLUE )
                doesHave++;
        }
    }

    gCost = shouldHave - doesHave;

    if (gCost < 0)
        throw std::runtime_error("G Cost is negative!");
}

int Board::getfCost() const
{
    return fCost;
}

int Board::getgCost() const
{
    return gCost;
}

  //  the heuristic cost, g(n) + f(n)
int Board::gethCost() const
{
    int hCost = getfCost() + getgCost();
    
    if (!hCost || hCost < 0)
        throw std::runtime_error("H Cost is negative!");
    
    return hCost;
}

  // less than
bool Board::operator<(const Board& rhs) const
{
    return gethCost() < rhs.gethCost();
}

  // greater than
bool Board::operator>(const Board& rhs) const
{
    return gethCost() > rhs.gethCost();
}

  // overloaded assignment operator copies one board to another
Board& Board::operator=(Board rhs)
{
  rhs.swap(*this);
  return *this;
}

  // helper swap function
void Board::swap(Board &copy)
{
  if (this != &copy ) {
    parent_.swap(copy.parent_); // shared_ptr::swap()
    std::swap(copy.size_, size_);
    std::swap(copy.board, board);
    std::swap(copy.emptySlotIndex, emptySlotIndex);
  }
  else {
    throw std::runtime_error("Tried to copy board of same board!");
  }
}
