#include "md5.hpp"

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
    int Hash<T>::hash( T value ) const
    {
      unsigned int hash = 5381;

      //for( size_t i = 0; value[i] != '\0'; i++ )
        //hash = ((hash << 5) + hash) + value[i];

      MD5 md5;
      hash = md5.digestString(value);
      //std::cout << hash << std::endl;

      return hash;
    }


      // finds the hashvalue of the item  : 2nd hash
    template <class T>
    int Hash<T>::hash2( T value ) const
    {
      unsigned int hash = 773;

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
    bool Hash<T>::IsActive(int pos) const
    {
      return ( array[pos].info == ACTIVE );
    }


      // inserts value into the hash table
    template <class T>
    bool Hash<T>::Insert( const T& value )
    {
      if ( numberOfItems != 0 ) 
        if ( (double)numberOfItems/(double)size > 0.6 )
          rehash();

      HashNode newNode(value, ACTIVE);
        
      bool flag = false;
      bool endfor = true;

      int h1 = hash(value);
      int h2 = hash2(value);

      for ( int i = 1; endfor; i++)
      {
        int pos = abs((h1 + i*h2) % size);

        if ( !IsActive( pos ) )
        {
          array[ pos ] = newNode;
          numberOfItems++;
          endfor = false;
          flag = true;
        } else if ( array[ pos ].element == newNode.element ) {
          endfor = false;
          flag = true;
        }
      }
            
      return ( flag );
    }

      // removes a value from the hash table
    template <class T>
    bool Hash<T>::Remove( const T& value )
    {
      bool flag = true;
      int pos = hash( value );

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
  Hash<T>::Hash( int size ) : size(size)
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
    else std::cerr << "Failed to insert!" << std::endl;
  }

    // boolean is there?
  template <class T>
  bool Hash<T>::isThere(T value)
  {
    if ( numberOfItems == 0 ) return false;

    int h1 = hash(value);
    int h2 = hash2(value);

    for ( int i = 1; ; i++) {
      int pos = abs( (h1 + (i*h2)) % size );

      if ( !IsActive( pos ) )
        return false;
      else if ( array[ pos ].element == value && array[ pos ].info == ACTIVE )
        return true;
    }
  }
  
    // checks if v1 and v2 have the same hash
  template <class T>
  bool Hash<T>::equalHash(T check, T goal)
  {
    if ( numberOfItems == 0 ) return false;

    int h1 = hash(check);
    int h2 = hash2(check);

    int h3 = hash(goal);
    int h4 = hash(goal);

    for ( int i = 1; ; i++) {
      int posChek = abs( (h1 + (i*h2)) % size );
      int posGoal = abs( (h3 + (i*h4)) % size );

      if ( !IsActive( posGoal ) ) {
        return false;
      }
      else if ( array[ posGoal ].element == goal && array[ posGoal ].info == ACTIVE ) {
        if ( posGoal == posChek ) {
          return true;
        }
        else {
          return false;
        }
      }
    }
    return false;
  }

    // number of entries
  template <class T>
  int Hash<T>::numEntries(void)
  {
    return ( numberOfItems );
  }