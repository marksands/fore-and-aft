#ifndef PQUEUE_H
#define PQUEUE_H

#include <iostream>
#include <fstream>

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

      // common interface method
    void push( T key, int priority ) {
      InsertValue(key, priority);
    }
      // common interface method
    T pop() {
      return RemoveMin();
    }

private:

  MinHeap<Node<T>*>* heap;
  HashTable<Node<T>*>* hash;

  int size;
};


template <class T>
PQueue<T>::PQueue() : size(0)
{
  heap = new MinHeap<Node<T>*>();
  hash = new HashTable<Node<T>*>();
}

template <class T>
PQueue<T>::~PQueue() {
  delete hash;
  delete heap;
}

template <class T>
void PQueue<T>::InsertValue(T key, int priority)
{
  Node<T>* newNode = new Node<T>( key, priority );

  heap->insertValue( newNode );
  hash->insertEntry( newNode );
}

template <class T>
T PQueue<T>::RemoveMin()
{
  size--;
  return hash->deleteEntry( heap->removeMin() ); 
}

template <class T>
void PQueue<T>::Empty()
{
  heap->empty();
  hash->empty();
  
  size = 0;
}

template <class T>
void PQueue<T>::AdjustValue( T key, int adjustment )
{
  int oldPriority = 0;

  Node<T>*& oldNode = hash->retrieve( key );
  oldPriority = oldNode->priority;
  oldNode->priority = ComputePriority( oldPriority, adjustment );

  heap->adjustValue( oldNode, oldPriority );
}

template <class T>
int PQueue<T>::ComputePriority( int oldPriority, int adjustment)
{
  try {
    int newPriority = oldPriority + adjustment;
    if ( newPriority < 0 )
      throw "Negative Priority Error!";
    return newPriority; 
  }
  catch ( const char* str ) {
    std::cerr << str << std::endl;
    exit(1);
  }
}

template <class T>
bool PQueue<T>::isEmpty() { 
  return heap->isEmpty();
}

#endif