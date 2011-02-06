#include <iostream>
#include <fstream>

#include "PQueue.hpp"
#include "Heap.hpp"
#include "Hash.hpp"
#include "Node.hpp"

#ifndef PQUEUE_CPP
#define PQUEUE_CPP

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