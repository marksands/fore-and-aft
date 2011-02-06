#include <cstring>
#include <cstdlib>
#include <cassert>

typedef unsigned long int u_int32;

typedef struct
{
  void* elems;
  u_int32 loglength;
  u_int32 alloclength;
  int elemSize;
} stack;

static void stackGrow( stack* s )
{
  s->alloclength *= 2;
  s->elems = realloc(s->elems, s->alloclength * s->elemSize);
}

void stackNew(stack* s, int elemSize)
{
  assert( s->elemSize > 0 );
  s->elemSize = elemSize;
  s->loglength = 0;
  s->alloclength = 4;
  s->elems = malloc(4*elemSize);
  assert( s->elems != NULL );
}

void stackDispose( stack* s )
{
  free( s->elems );
}

void stackPush(stack* s, void* elemAddr)
{
  if ( s->loglength == s->alloclength )
    stackGrow( s );

  void* target = (char*)s->elems + s->loglength * s->elemSize;
  memcpy(target, elemAddr, s->elemSize);
  s->loglength++;
} 

void stackPop( stack* s, void* elemAddr )
{
  --s->loglength;
  void* source = (char*)s->elems + s->loglength * s->elemSize;
  memcpy(elemAddr, source, s->elemSize);
}
