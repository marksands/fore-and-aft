#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>
#include <queue>

#include "Hash.hpp"

#pragma GCC diagnostic ignored "-Wwrite-strings"

typedef unsigned int u_int;

/*
* @prototypes
*/
int InitMenu();
void InitBoard(int size);
void InitGoal(int size);

void dfs();
void PrintGrid( std::string grid );

const char EMPTY = '0';
const char START = 'S';
const char RED   = 'R';
const char BLUE  = 'B';

class Node {
  public:
    std::vector<int> state;
    std::string chargrid;
    int empty;
    bool visited;

  Node( int size ) { 
    state.resize(size*size);
    chargrid.resize(size*size,'0');
    visited = false;
  }

  Node( std::vector<int> s, std::string c, int e, bool v )
    : state(s), chargrid(c), empty(e), visited(v) { }
};

std::vector<Node> nodes;
std::vector<int> goalstate;
std::string goalstring;
int size;

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

  dfs();

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
void InitBoard(int size)
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
void InitGoal(int size)
{
  goalstate.resize(size*size);
  goalstring.resize(size*size, '0');

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      int index = i*size + j;
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

      // for each state push node/state onto stack

      // multiplication is expensive
      int size2 = size*size;
  
      std::cout << "trying 1 and 2" << std::endl;    
      if ((n.empty - 1 >= 0) && (n.state[n.empty-1] == RED)) {
      // make a new state left
        Node newState(n.state, n.chargrid, n.empty-1, false );
        newState.state[n.empty-1] = newState.chargrid[n.empty-1] = START;
        newState.state[n.empty] = newState.chargrid[n.empty] = RED;

          // found it!
        if( newState.chargrid == goalstring )
          break;
        if( !lookup.isThere(newState.chargrid) ) {
          std::cout << "1st" << std::endl;
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
          if( newState.chargrid == goalstring )
            break;
          if( !lookup.isThere(newState.chargrid) ) {
            std::cout << "2nd" << std::endl;
            lookup.insertEntry(newState.chargrid);
            PrintGrid( newState.chargrid );
            s.push(newState);
          }
        }

      std::cout << "trying 3 and 4" << std::endl;
      if ((n.empty + 1 < size2) && (n.state[n.empty+1] == BLUE)) {
        // make a new state right
        Node newState(n.state, n.chargrid, n.empty+1, false );
        newState.state[n.empty+1] = newState.chargrid[n.empty+1] = START;
        newState.state[n.empty] = newState.chargrid[n.empty] = BLUE;
            // found it!
        if( newState.chargrid == goalstring )
          break;
        if( !lookup.isThere(newState.chargrid) ) {
          std::cout << "3rd" << std::endl;
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
          if( newState.chargrid == goalstring )
            break;
          if( !lookup.isThere(newState.chargrid) ) {
            std::cout << "4th" << std::endl;
            lookup.insertEntry(newState.chargrid);
            PrintGrid( newState.chargrid );
            s.push(newState);
          }
        }
      
      std::cout << "trying 5 and 6" << std::endl;
      std::cout << "empty: " << n.empty << " size: " << size << std::endl;
      std::cout << "n.empty - size: " << (n.empty - size) << std::endl;
      if (( n.empty - size ) >= 0 ) { std::cout << "5-1 passes" << std::endl;}
      if (( n.state[n.empty-size] == RED)) { std::cout << "5-2 passes" << std::endl;}
      if ((n.empty - size >= 0) && (n.state[n.empty-size] == RED)) {
        // make a new state up
        Node newState(n.state, n.chargrid, n.empty-size, false );
        newState.state[n.empty-size] = newState.chargrid[n.empty-size] = START;
        newState.state[n.empty] = newState.chargrid[n.empty] = RED;
            // found it!
        if( newState.chargrid == goalstring )
          break;
        if( !lookup.isThere(newState.chargrid) ) {
          std::cout << "5th" << std::endl;
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
          if( newState.chargrid == goalstring )
            break;
          if( !lookup.isThere(newState.chargrid) ) {
            std::cout << "6th" << std::endl;
            lookup.insertEntry(newState.chargrid);
            PrintGrid( newState.chargrid );
            s.push(newState);
          }
        }

      std::cout << "trying 7 and 8" << std::endl;
      if ((n.empty + size < size2) && (n.state[n.empty+size] == BLUE)) {
        // make a new state down
        Node newState(n.state, n.chargrid, n.empty+size, false );
        newState.state[n.empty+size] = newState.chargrid[n.empty+size] = START;
        newState.state[n.empty] = newState.chargrid[n.empty] = BLUE;
            // found it!
        if( newState.chargrid == goalstring )
          break;
        if( !lookup.isThere(newState.chargrid) ) {
          std::cout << "7th" << std::endl;
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
          if( newState.chargrid == goalstring )
            break;
          if( !lookup.isThere(newState.chargrid) ) {
            std::cout << "8th" << std::endl;
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


