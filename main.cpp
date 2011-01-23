#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>
#include <queue>

#include "Hash.hpp"
#include "Timer.hpp"

#pragma GCC diagnostic ignored "-Wwrite-strings"

typedef unsigned int u_int16;
typedef long int int16;
typedef unsigned long int u_int32;
typedef long int int32;

/*
* @prototypes
*/
int InitMenu();
void InitBoard(int32 size);
void InitGoal(int32 size);

void dfs();
void PrintGrid( std::string grid );

const char EMPTY = '0';
const char START = 'S';
const char RED   = 'R';
const char BLUE  = 'B';

class Node {
  public:
    std::vector<int32> state;
    std::string chargrid;
    int32 empty;
    bool visited;

  Node( int32 size ) { 
    state.resize(size*size);
    chargrid.resize(size*size,'0');
    visited = false;
  }

  Node( std::vector<int32> s, std::string c, int32 e, bool v )
    : state(s), chargrid(c), empty(e), visited(v) { }
};

std::vector<Node> nodes;
std::vector<int32> goalstate;
std::string goalstring;
int32 size;

int main(int argc, char* argv[])
{
  size = InitMenu();

  InitBoard(size);
  InitGoal(size);

  std::cout << std::endl
    << "init: " << nodes[0].chargrid
    << std::endl
    << "goal: " << goalstring
    << std::endl
    << std::endl;

  Timer t;
  dfs();

  #if defined(__WIN32__) || defined(_WIN32)
    system("pause");
  #endif

  return 0;
}

/*
* @methods
*   InitMenu() - query user for board size and return the size or 5
*/
int InitMenu()
{
  int choice;

  std::cout << std::endl
     << std::setw(3) << "" << "Initialize the board size"
     << std::endl
     << std::setw(3) << "" << "Enter size: ";
  std::cin >> choice;
  std::cout << std::endl;

  return ( choice < 5 ? 5 : choice );
}

/*
* @methods
*   InitMenu() - query user for board size and return the size or 5
*/
void InitBoard(int32 size)
{
  Node newNode(size);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      int index = i*size + j;
      if ((i == (size-1)/2) && (j == (size-1)/2) ) {
        newNode.state[index] = START;
        newNode.empty = index;
      } else if ((i <= (size-1)/2) && (j <= (size-1)/2) ) {
        newNode.state[index] = RED;
      } else if ((i >= (size-1)/2) && (j >= (size-1)/2) ) {
        newNode.state[index] = BLUE;
      }
      else {
        newNode.state[index] = EMPTY;
      }
      newNode.chargrid[index] = newNode.state[index];
    }
  }
  nodes.push_back(newNode);
}

/*
* @methods
*   InitMenu() - query user for board size and return the size or 5
*/
void InitGoal(int32 size)
{
  goalstate.resize(size*size);
  goalstring.resize(size*size, '0');

  for (int32 i = 0; i < size; i++) {
    for (int32 j = 0; j < size; j++) {
      int32 index = i*size + j;
      if ((i == (size-1)/2) && (j == (size-1)/2) ) {
        goalstate[index] = START;
      } else if ((i <= (size-1)/2) && (j <= (size-1)/2) ) {
        goalstate[index] = BLUE;
      } else if ((i >= (size-1)/2) && (j >= (size-1)/2) ) {
        goalstate[index] = RED;
      }
      else{
        goalstate[index] = EMPTY;
      }
      goalstring[index] = goalstate[index];
    }
  }
}

void dfs()
{
  Hash<std::string> lookup;
  lookup.insertEntry(goalstring);

  std::stack<Node> s;
  s.push(nodes[0]);
  
  while( !s.empty() )
  {
    Node n = s.top(); s.pop();

    if (!n.visited){
      n.visited = true;

      // multiplication is expensive
      int32 size2 = size*size;

      if ((n.empty - 1 >= 0) && (n.state[n.empty-1] == RED)) {
      // make a new state left
        Node newState(n.state, n.chargrid, n.empty-1, false );
        newState.state[n.empty-1] = newState.chargrid[n.empty-1] = START;
        newState.state[n.empty] = newState.chargrid[n.empty] = RED;

          // found it!
        if( newState.chargrid == goalstring ) {
          PrintGrid( newState.chargrid );
          break;
        }
        if( !lookup.isThere(newState.chargrid) ) {
          lookup.insertEntry(newState.chargrid);
          PrintGrid( newState.chargrid );
          s.push(newState);
        }
      }
        else if ((n.empty - 2 >= 0) && (n.state[n.empty-2] == RED)) {
        // make a new state left
          Node newState(n.state, n.chargrid, n.empty-2, false );
          newState.state[n.empty-2] = newState.chargrid[n.empty-2] = START;
          newState.state[n.empty] = newState.chargrid[n.empty] = RED;
            // found it!
          if( newState.chargrid == goalstring ) {
            PrintGrid( newState.chargrid );
            break;
          }
          if( !lookup.isThere(newState.chargrid) ) {
            lookup.insertEntry(newState.chargrid);
            PrintGrid( newState.chargrid );
            s.push(newState);
          }
        }

      if ((n.empty + 1 < size2) && (n.state[n.empty+1] == BLUE)) {
        // make a new state right
        Node newState(n.state, n.chargrid, n.empty+1, false );
        newState.state[n.empty+1] = newState.chargrid[n.empty+1] = START;
        newState.state[n.empty] = newState.chargrid[n.empty] = BLUE;
            // found it!
        if( newState.chargrid == goalstring ) {
          PrintGrid( newState.chargrid );
          break;
        }
        if( !lookup.isThere(newState.chargrid) ) {
          lookup.insertEntry(newState.chargrid);
          PrintGrid( newState.chargrid );
          s.push(newState);
        }
      }
        else if ((n.empty + 2 < size2) && (n.state[n.empty+2] == BLUE)) {
        // make a new state right
          Node newState(n.state, n.chargrid, n.empty+2, false );
          newState.state[n.empty+2] = newState.chargrid[n.empty+2] = START;
          newState.state[n.empty] = newState.chargrid[n.empty] = BLUE;
            // found it!
          if( newState.chargrid == goalstring ) {
            PrintGrid( newState.chargrid );
            break;
          }
          if( !lookup.isThere(newState.chargrid) ) {
            lookup.insertEntry(newState.chargrid);
            PrintGrid( newState.chargrid );
            s.push(newState);
          }
        }
      
      if ((n.empty - size >= 0) && (n.state[n.empty-size] == RED)) {
        // make a new state up
        Node newState(n.state, n.chargrid, n.empty-size, false );
        newState.state[n.empty-size] = newState.chargrid[n.empty-size] = START;
        newState.state[n.empty] = newState.chargrid[n.empty] = RED;
            // found it!
        if( newState.chargrid == goalstring ) {
          PrintGrid( newState.chargrid );
          break;
        }
        if( !lookup.isThere(newState.chargrid) ) {
          lookup.insertEntry(newState.chargrid);
          PrintGrid( newState.chargrid );
          s.push(newState);
        }
      }
        else if ((n.empty - size*2 >= 0) && (n.state[n.empty-size*2] == RED)) {
        // make a new state up
          Node newState(n.state, n.chargrid, n.empty-size*2, false );
          newState.state[n.empty-size*2] = newState.chargrid[n.empty-size*2] = START;
          newState.state[n.empty] = newState.chargrid[n.empty] = RED;
            // found it!
          if( newState.chargrid == goalstring ) {
            PrintGrid( newState.chargrid );
            break;
          }
          if( !lookup.isThere(newState.chargrid) ) {
            lookup.insertEntry(newState.chargrid);
            PrintGrid( newState.chargrid );
            s.push(newState);
          }
        }

      if ((n.empty + size < size2) && (n.state[n.empty+size] == BLUE)) {
        // make a new state down
        Node newState(n.state, n.chargrid, n.empty+size, false );
        newState.state[n.empty+size] = newState.chargrid[n.empty+size] = START;
        newState.state[n.empty] = newState.chargrid[n.empty] = BLUE;
            // found it!
        if( newState.chargrid == goalstring ) {
          PrintGrid( newState.chargrid );
          break;
        }
        if( !lookup.isThere(newState.chargrid) ) {
          lookup.insertEntry(newState.chargrid);
          PrintGrid( newState.chargrid );
          s.push(newState);
        }
      }
        else if ((n.empty + size*2 < size2) && (n.state[n.empty+size*2] == BLUE)) {
        // make a new state down
        Node newState(n.state, n.chargrid, n.empty+size*2, false );
        newState.state[n.empty+size*2] = newState.chargrid[n.empty+size*2] = START;
        newState.state[n.empty] = newState.chargrid[n.empty] = BLUE;
            // found it!
          if( newState.chargrid == goalstring ) {
            PrintGrid( newState.chargrid );
            break;
          }
          if( !lookup.isThere(newState.chargrid) ) {
            lookup.insertEntry(newState.chargrid);
            PrintGrid( newState.chargrid );
            s.push(newState);
          }
        }
    }
  }
}

void PrintGrid( std::string grid )
{
  for ( int i = 0; i < size; i++ ) {
    for ( int j = 0; j < size; j++ ) {
      int index = i*size + j;
      if (grid[index] == EMPTY)
        std::cout << "[ ] ";
      else
        std::cout << "[" << grid[index] << "] ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl << std::endl;
}