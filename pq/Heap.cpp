#include <iostream>
#include <string>
#include <vector>
#include "Heap.hpp"

#ifndef HEAP_CPP
#define HEAP_CPP

const int ROOT = 1;

template <class T>
MinHeap<T>::MinHeap() : size( 0 )
{
  heap.resize(1);
}

template <class T>
inline bool MinHeap<T>::isEmpty() const
{
  return ( size <= 0 );
}

  // insert item into heap
template <class T>
void MinHeap<T>::Insert( const T& item )
{
  if ( size == heap.size() - 1 )
    heap.resize( heap.size() * 2 );
  
  int hole = ++size;
  heap[hole] = item;

    // insert item into appropriate position
  PercolateUp( hole );
}

  // clear the heap
template <class T>
void MinHeap<T>::Clear()
{
  heap.clear();
  size = 0;
}

  // delete the min
template <class T>
void MinHeap<T>::DeleteMin()
{
  try {
    if ( isEmpty() ) 
      throw "Underflow Exception!";     
    heap[ROOT] = heap[ size-- ];
    PercolateDown( ROOT );
  }
  catch ( char* str ) {
    std::cerr << str << std::endl;
    exit(1);
  }
}
  
  // return the min and remove the node
template <class T>
T MinHeap<T>::removeMin()
{
  try {
    if ( isEmpty() )
      throw "Queue is empty";
      
    T temp = heap[ROOT];
    DeleteMin();
    
    return temp;
  }
  catch ( const char* str ) {
    std::cerr << str << std::endl;
    exit(1);
  }
}

  // empty the heap
template <class T>
void MinHeap<T>::empty()
{
  Clear();
}

  // insert a value into the heap
template <class T>
void MinHeap<T>::insertValue(T value)
{
  Insert( value );
}

  // Adjusts an item downward in the heap according to it's priority
template <class T>
void MinHeap<T>::PercolateDown( int hole )
{
  int child;
  T temp = heap[hole];
  
  for(; hole * 2 <= size; hole = child) {
    child = hole * 2;
    
    if ( child != size && heap[child+1]->priority < heap[child]->priority )
      child++;
    
    if ( heap[child]->priority < temp->priority ) {
      heap[hole] = heap[child];
      heap[hole]->loc = hole;
    }
    else
      break;
  }
  heap[hole] = temp;
  heap[hole]->loc = hole;
}

  // Adjusts an item upward in the heap according to it's priority
template <class T>
void MinHeap<T>::PercolateUp( int hole )
{
  T temp = heap[hole];

  for(; hole > 1 && temp->priority < heap[hole/2]->priority; hole/= 2)
  {
    heap[hole] = heap[hole/2];
    heap[hole]->loc = hole;
  }

  heap[hole] = temp;
  heap[hole]->loc = hole;
}

  // Adjust a value according to it's priority
template <class T>
void MinHeap<T>::adjustValue( T& value, int priority )
{
  if (priority > value->priority)
    PercolateUp(value->loc); 
  else
    PercolateDown(value->loc);
}

#endif