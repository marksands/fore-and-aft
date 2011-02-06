#ifndef HASH_TABLE_CPP
#define HASH_TABLE_CPP

#include "HashTable.hpp"
#include <string>
#include <iostream>

#define BASE 0

//Resizes the hash table when it exceeds it's load factor
template<class T>
typename HashTable<T>::HashNode** HashTable<T>::resize( HashNode**& mainTable )
{
  int newSize, oldSize;
  HashNode** newTable;

  newSize = (size * 2) + 1;
  oldSize = size;
  size = newSize;

  newTable = createTable(newSize);

  rehashTable(oldSize,newTable);
  deleteTable(oldSize);

  return newTable;
}

//Returns false when the hash table is not beyond it's load factor
template<class T>
bool HashTable<T>::isOverLoad()
{
    // load variable is the current load of the table.
  double load = 0;
    // load factor is the maximum load amount the table can have
  double LOAD_FACTOR = 0.6;
    // Calculate the current load
  load = (double)numEntries()/tableSize();

    // Return true if the current load exceeds the max false otherwise  
  if(load >= LOAD_FACTOR)
    return true;
  return false;
}

  // Deletes the entire table
template<class T>
void HashTable<T>::deleteTable( int size )
{
  if( table != NULL )
  {
    for(int i = 0; i < size; i++)
    {
      delete table[i]->element; 
      delete [] table[i];
    }
      // delete the array of struct pointers
    delete [] table;
  }
}

  // Rehashes the old table with the values of the new table
template<class T>
void HashTable<T>::rehashTable( int oldSize, HashNode**& newTable )
{
  for(int i = 0; i < oldSize; i++)
  {
    if( table[i]->info == ACTIVE )  
     addEntry(*(table[i]->element), newTable);  
  }
}

template<class T>
void HashTable<T>::copyTable( HashNode**& newTable )
{ 
    // perform the copy
  newTable = table;
  for(int i = 0; i < tableSize(); i++)
  {
    newTable[i] = table[i];
    newTable[i]->element = table[i]->element;
    newTable[i]->info = table[i]->info;
  }   
}

  // Adds a new entry into the hash table
template<class T>
void HashTable<T>::addEntry( T value, HashNode**& Table )
{ 
  unsigned int index;
  int i;
  i = 1;
  
  T* element;
  element = new T;
  *element = value;

  index = hash(value->key);

  while (Table[index]->info == ACTIVE)  
    index = hash2( index, value->key, i++ );  

   Table[index]->element = element;
   Table[index]->info = ACTIVE;
}

  // Resets all the nodes in the array to default values
template<class T>
void HashTable<T>::clearNodes()
{
  for(int i = 0; i < tableSize(); i++)
  {
      table[i]->info = EMPTY;
      table[i]->element = NULL;
  }
}

  // Returns a new hash table of default values with size of size
template<class T>
typename HashTable<T>::HashNode** HashTable<T>::createTable( const int size )
{
  HashNode** newTable;
  newTable = new HashNode*[size];

  for(int i = 0; i < size; i++)     
  {
    newTable[i] = new HashNode;   
    newTable[i]->element = new T;
  }

  return newTable;
}

  // First hash function DJB hash function, presently it is the most effective hash function
template<class T>
unsigned int HashTable<T>::hash( std::string element )
{
  unsigned int index = 5381;
  
  for(int i = 0; i < element.length(); i++)
    index = ((index << 5) + index) + element[i];

  return ( index % tableSize() );
}

  // Second hash function is used if a collison would of occured on the first
template <class T>
unsigned int HashTable<T>::hash2( unsigned int index, std::string value, int i ) { 
  return (((index + i) << 3) + 1) % tableSize(); 
}


  // Destructor for hash table, calls deleteTable
template <class T>
HashTable<T>::~HashTable() {
  deleteTable( tableSize() );
}
 
  // Default constructor for hash table
template <class T>
HashTable<T>::HashTable()
{
  size = ORIG_SIZE;
  numEntires = 0;
  table = createTable( ORIG_SIZE );
  clearNodes();
}

  // Clears all the entries within a table and resets its size
template <class T>
void HashTable<T>::clear()
{
   deleteTable( tableSize() );
   numEntires = 0;
   size = ORIG_SIZE;
   table = createTable(ORIG_SIZE);
   clearNodes();
}

  // empties or deletes the table - convenience method
template <class T>
void HashTable<T>::empty()
{
  deleteTable( tableSize() );
}

  // Inserts an entry into the hash table
template <class T>
void HashTable<T>::insertEntry( T value )
{
  numEntires++;

  if( isOverLoad() )  
    table = resize(table);

  addEntry(value,table);
}

  // Deletes an entry form the hash table
template <class T>
std::string HashTable<T>::deleteEntry( T value )
{
  if(numEntries() > 0)
    numEntires--;

  retrieveEntry(value->key)->info = EMPTY;

  return value->key;
}

  // returns an item in the hash table if it is there.
template <class T>
T& HashTable<T>::retrieve( std::string value )
{
    // Make a pointer to retrieve entries return
  HashNode* foundNode;
    // retrieve the entry
  foundNode = retrieveEntry(value); 

  try {
      // if the node is deleted or not equal to the original value return the element 
    if(foundNode->info == EMPTY || (foundNode->element[BASE]->key) != value)
      throw "Entry does not exist!";
      
    return foundNode->element[BASE];   
  }
  catch ( const char* str ) {
    std::cerr << str << std::endl;
    exit(1);
  }
}

  // Notifies the user if an item is in the hash table
template <class T>
bool HashTable<T>::isThere( std::string value )
{
    // Make a pointer to retrieve entries return
  HashNode* foundNode;  
    // retrieve the entry
  foundNode = retrieveEntry(value); 

    // if the node is not deleted and equal to the original value return the element 
  if(foundNode->info == ACTIVE && (foundNode->element[BASE]->key) == value)
    return true;  
  return false;
}

//Retrieve a node from the hash table
template <class T>
typename HashTable<T>::HashNode*& HashTable<T>::retrieveEntry( std::string value )
{
  int index, i = 1;

    // hash the value
  index = hash(value);

    // if the value is not deleted and not equal to value keep looping quit looping if we've exceeded the number of entries in the table
  while ( table[index]->info == ACTIVE && i < numEntries() && (table[index]->element[BASE]->key) != value )
    index = hash2(index,value,i++); 

  return table[index];
}

  // Returns the number of entries within the hash table
template <class T>
inline int HashTable<T>::numEntries() {
  return numEntires;
}

  // Returns the current size of the table
template<class T>
inline int HashTable<T>::tableSize() {
  return size;
}

#endif