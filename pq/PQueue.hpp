#ifndef PQUEUE_H
#define PQUEUE_H

#include "Heap.hpp"
#include "HashTable.hpp"
#include "Node.hpp"

template <class T>
class PQueue {
public:
      // Constructor for the priority queue
    PQueue();
      // Destructor for the priority queue
    ~PQueue();
      // inserts a value into the queue
    void InsertValue( T key, int priority );
      // adjusts the priority to a new value
    void AdjustValue( T key, int priorityAdjustment );
      // Removes the minimum item from the priority queue
    T RemoveMin();
      // Empties the priority queue
    void Empty();
      // Returns true if the priority queue is empty
    bool isEmpty();
      // Computes the new priority
    int ComputePriority( int oldPriority, int priorityAdjustment );

private:

  MinHeap<Node<T>*>* heap;
  HashTable<Node<T>*>* hash;

  int size;
};

#endif