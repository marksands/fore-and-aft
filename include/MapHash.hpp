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
 * size_tERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
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

  //---------------------------------------------------------------------------------------------------
  // Class: Hash
  //---------------------------------------------------------------------------------------------------
  template<class T>
  class Hash : public SearchableADT<T>
  {
  private:

    size_t size;
      // holds curent size;
    size_t numberOfItems;
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

    virtual size_t hash(T value) const;
      // finds the hashvalue of the item : 1st hash
    virtual size_t hash2(T value) const;
      // finds the hashvalue of the item : 2nd hash
    virtual bool IsActive(size_t pos) const;
      // returns true if the position is occupied

    virtual void rehash();
      // rehashes the hash table to double its size

    void Empty();
      // erases the hash table
    bool Insert( const T& value );
      // inserts value size_to the hash table
    bool Remove( const T& value );
      // removes a value from the hash table

  public:
    Hash( size_t size = 101 );
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
    virtual size_t numEntries(void);
      // number of entries

    virtual bool equalHash(T check, T goal);
      // checks if v1 and v2 have the same hash
  };

  #include "../src/Hash.cpp"

#endif