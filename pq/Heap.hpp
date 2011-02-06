#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

template <class T>
class Heap {
public:
  virtual ~Heap() { }
  
    // inserts a value into the heap
  virtual void insertValue(T value) = 0;
    // returns the min and deletes the node
  virtual T removeMin() = 0;
    // empties the list
  virtual void empty() = 0;
    // returns true if the list is empty
  virtual bool isEmpty() const = 0;
};

template <class T>
class MinHeap : public Heap<T> {
public:
  explicit MinHeap();

    // returns true if the heap is empty
  bool isEmpty() const;
    // return number of items inserted
  int loadFromFile( std::string fileName );
    // returns the min and deletes the node
  T removeMin();
    // empties the list
  void empty();
    // inserts a value into the heap
  void insertValue( T value );
    //Adjusts a value in the heap to it's new priority
  virtual void adjustValue( T& value, int priority ); 
  
private:
  int size;
  std::vector<T> heap;
  
    // insert an item into the heap
  void Insert( const T& item );
    // clears the items in the heap
  void Clear();
    // delets the min node in the heap
  void DeleteMin();
    // percolates down the heap adjusting values
  void PercolateDown( int hole );
    // percolates up the heap adjusting values
  void PercolateUp( int hole );
};

#include "Heap.cpp"

#endif