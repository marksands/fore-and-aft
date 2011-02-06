#ifndef NODE_HPP_XLBAR4E1
#define NODE_HPP_XLBAR4E1

#include <string>

  //---------------------------------------------------------------------------------------------------
  // Class: Node
  //---------------------------------------------------------------------------------------------------

template <class T>
class Node {
  public:

      // Node contains a key to store a string type along with its priority and location in the queue
    T key;
    int priority;
    int loc;

      // Default constructor
    Node( const T& key = T(), int priority = 0 ) : key(key), priority(priority) { }
};

#endif /* end of include guard: NODE_HPP_XLBAR4E1 */
