
#include "../binary_heap.hpp"
#include <iostream>
#include <limits>

int main()
{
  unsigned const delta = 1000000;
  binary_heap<int> h;
  h.reserve(delta/2);

  for ( unsigned i = 0; i < delta/2; ++i ) 
  {
    h.add( i );
  }

  for ( unsigned i = 0; i < delta/2; ++i ) 
  {
    h.extract_top();
  }

  return 0;
}
