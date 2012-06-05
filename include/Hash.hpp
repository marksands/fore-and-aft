/*
 * Copyright (c) 2010, Mark Sands marksands07@gmail.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * u_int32ERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef HASH_HPP
#define HASH_HPP

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>

typedef unsigned long int u_int32;

  //---------------------------------------------------------------------------------------------------
  // Abstract Class: SearchableADT
  //---------------------------------------------------------------------------------------------------
  template <class T>
  class SearchableADT {
    public:
    virtual ~SearchableADT() { }

    virtual void clear(void) = 0;
    virtual void insertEntry(T value) = 0;
    virtual void deleteEntry(T value) = 0;
    virtual bool isThere(T value) = 0;
    virtual u_int32 numEntries(void) = 0;
  };

  //---------------------------------------------------------------------------------------------------
  // Class: Hash
  //---------------------------------------------------------------------------------------------------
  template<class T>
  class Hash : public SearchableADT<T>
  {
  private:

    u_int32 size;
      // holds curent size;
    u_int32 numberOfItems;
      //holds mumber of items

    enum EntryType { ACTIVE, EMPTY, DELETED };

      // struct HashNode stores the item and lazy deletion information
    struct HashNode {
      T element;
      EntryType info;

      HashNode( const T& e = T(), EntryType i = EMPTY ) : element(e), info(i)
        { }
    };

      // vector array of HashNode
    std::vector<HashNode> array;

    virtual u_int32 hash(T value) const;
      // finds the hashvalue of the item : 1st hash
    virtual u_int32 hash2(T value) const;
      // finds the hashvalue of the item : 2nd hash
    virtual bool IsActive(u_int32 pos) const;
      // returns true if the position is occupied

    virtual void rehash();
      // rehashes the hash table to double its size

    void Empty();
      // erases the hash table
    bool Insert( const T& value );
      // inserts value u_int32o the hash table
    bool Remove( const T& value );
      // removes a value from the hash table

  public:
    Hash( u_int32 size = 101 );
      // Sets the root to NULL;
    virtual ~Hash();
      // Calls DestroyTree() to destroy the current tree.

    virtual void clear(void);
      // clears tree
    virtual void insertEntry(T value);
      // inserts entry 'value'
    virtual void deleteEntry(T value);
      // deletes entry 'value'
    virtual bool isThere(T value);
      // boolean is there?
    virtual u_int32 numEntries(void);
      // number of entries

    virtual bool equalHash(T check, T goal);
      // checks if v1 and v2 have the same hash
  };

#pragma mark -
#pragma mark Private

      //***********************************
      //
      //    Private Methods
      //
      //***********************************


      // erases the hash table
    template <class T>
    void Hash<T>::Empty()
    {
      size_t size_ = array.size();
      for ( size_t i = 0; i < size_; i++ )
        array[i].info = EMPTY;

      numberOfItems = 0;
    }

#pragma mark -
#pragma mark Hash Algorithms

      // finds the hashvalue of the item : 1st hash
    template <class T>
    u_int32 Hash<T>::hash( T value ) const
    {
      u_int32 hash = 5381;

      for( size_t i = 0; value[i] != '\0'; i++ )
        hash = ((hash << 5) + hash) + value[i];

      return hash;
    }


      // finds the hashvalue of the item  : 2nd hash
    template <class T>
    u_int32 Hash<T>::hash2( T value ) const
    {
      u_int32 hash = 773;

      for( size_t i = 0; value[i] != '\0'; i++ )
        hash = ((hash << 3) + hash) + 1 + value[i];

      return hash;
    }


      // rehashes the hash table to double its size
    template <class T>
    void Hash<T>::rehash()
    {
      std::vector<HashNode> oldArray = array;
      array.resize( 2 * oldArray.size() + 1 );

      size_t size_ = array.size();
      for ( size_t i = 0; i < size_; i++ ) {
        array[i].info = EMPTY;
      }

      size = ( size * 2 ) + 1;

      size_ = oldArray.size();
      for ( size_t i = 0; i < size_; i++ ) {
        if ( oldArray[i].info == ACTIVE ) {
          Insert( oldArray[i].element );
        }
      }

    }

#pragma mark -
#pragma mark Standard

      // returns true if the position is occupied
    template <class T>
    bool Hash<T>::IsActive(u_int32 pos) const
    {
      return ( array[pos].info == ACTIVE );
    }


      // inserts value u_int32o the hash table
    template <class T>
    bool Hash<T>::Insert( const T& value )
    {
      if ( numberOfItems != 0 )
        if ( (double)numberOfItems/(double)size > 0.6 )
          rehash();

      HashNode newNode(value, ACTIVE);

      u_int32 h1 = hash(value);
      u_int32 h2 = hash2(value);

      for ( u_int32 i = 1; ; i++)
      {
        u_int32 pos = abs((h1 + i*h2) % size);

        if ( !IsActive( pos ) )
        {
          array[ pos ] = newNode;
          numberOfItems++;
          return true;
        } else if ( array[ pos ].element == newNode.element ) {
          return false;
        }
      }

      return false;
    }

      // removes a value from the hash table
    template <class T>
    bool Hash<T>::Remove( const T& value )
    {
      bool flag = true;
      u_int32 pos = hash( value );

      if ( IsActive(pos) )
      {
        array[pos].info = DELETED;
        numberOfItems--;
      }
      else {
        flag = false;
      }

      return ( flag );
    }

#pragma mark -
#pragma mark Public


      //***********************************
      //
      //    Public Methods
      //
      //***********************************


  template <class T>
  Hash<T>::Hash( u_int32 size ) : size(size)
  {
    array.resize(size);
    Empty();
  }

  template <class T>
  Hash<T>::~Hash()
  {
    Empty();
  }


#pragma mark -
#pragma mark Inherited

      //***********************************
      //
      //    Inherited Methods
      //
      //***********************************

    // clears tree
  template <class T>
  void Hash<T>::clear(void)
  {
    Empty();
  }

    // inserts entry 'value'
  template <class T>
  void Hash<T>::insertEntry(T value)
  {
    if ( Insert( value ) );
    else std::cerr << "Failed to insert!" << std::endl;
  }

    // deletes entry 'value'
  template <class T>
  void Hash<T>::deleteEntry(T value)
  {
    if ( Remove( value ) );
    else std::cerr << "Failed to remove!" << std::endl;
  }

    // boolean is there?
  template <class T>
  bool Hash<T>::isThere(T value)
  {
    if ( numberOfItems == 0 )
      return false;

    u_int32 h1 = hash(value);
    u_int32 h2 = hash2(value);

    for ( u_int32 i = 1; ; i++) {
      u_int32 pos = abs( (h1 + (i*h2)) % size );

      if ( !IsActive( pos ) )
        return false;
      else if ( array[pos].element == value && array[pos].info == ACTIVE )
        return true;
      //else if ( array[ pos ].element == value && array[ pos ].info == ACTIVE )
    }
  }

    // checks if v1 and v2 have the same hash
  template <class T>
  bool Hash<T>::equalHash(T check, T goal)
  {
    if ( numberOfItems == 0 ) return false;

    u_int32 h1 = hash(check);
    u_int32 h2 = hash2(check);

    for ( u_int32 i = 1; ; i++) {
      u_int32 pos = abs( (h1 + (i*h2)) % size );

      if ( !IsActive( pos ) ) {
        return false;
      }
      else if ( array[pos].element == goal && array[pos].info == ACTIVE ) {
        return true;
      }
    }
    return false;
  }

    // number of entries
  template <class T>
  u_int32 Hash<T>::numEntries(void)
  {
    return ( numberOfItems );
  }
#endif