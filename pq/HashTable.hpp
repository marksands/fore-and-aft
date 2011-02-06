#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <string>

template <class T>
class HashTable {
  private:
      //The current size of the hash table
    int size;
      //The number of entries in the hash table
    int numEntires;

      //The size of the table originally
    static const int ORIG_SIZE = 101;

      // enum holds the info type
    enum EntryType { ACTIVE, DELETED, EMPTY };
    
      //The HashTable is composed of HashNodes
    class HashNode {
      public:
        T* element;
        EntryType info;

          // HashNode constructor, element=null, EMPTY
        HashNode() : element( NULL ), info( EMPTY ) { }
    };

    HashNode** table;

      //Resizes the hash table when it exceeds it's load factor
    HashNode** resize(HashNode**& mainTable);
      //Returns false when the hash table is not beyond it's load factor
    bool isOverLoad();
      //Deletes the entire table
    void deleteTable(int size);
      //Adds a new entry into the hash table
    void addEntry(T value, HashNode**& Table);
      //Resets all the pointers in a hash table to NULL and sets the deletion values to false
    void clearNodes();
      //Returns a new hash table of default values with size of size
    HashNode** createTable( const int size );
      //First hash function
    unsigned int hash( std::string element );
      //Second hash function is used if a collison would of occured on the first
    unsigned int hash2( unsigned int index, std::string value, int i ); 
      // Copies a table directly
    void copyTable( HashNode**& newTable );
      // Rehashes the old table with the values of the new table
    void rehashTable( int oldSize, HashNode**& newTable );
      // Retrieve a node from the hash table
    HashNode*& retrieveEntry( std::string value );

  public:

      // Destructor for hash table, calls deleteTable
    ~HashTable();
      // Default constructor for hash table
    HashTable();
      // Clears all the entries within a table and resets its size
    void clear();
      // empties or deletes the table
    void empty();
      // Inserts an entry into the hash table
    void insertEntry(T value);
      // Deletes an entry form the hash table
    std::string deleteEntry(T value);
      // Determines if a certain entry is in the hash table
    bool isThere(std::string value);
      // Retrieves an item in the hash table
    T& retrieve(std::string value);
      // Returns the number of entries within the hash table
    int numEntries();
      //Returns the current size of the table
    int tableSize();
};

#include "HashTable.cpp"

#endif