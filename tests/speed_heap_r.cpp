
#include "../binary_heap_r.hpp"
#include <iostream>
#include <limits>

int main()
{
  unsigned const delta = 1000000;
  binary_heap_r<int> h;
  h.reserve(delta/2);

  for ( unsigned i = 0; i < delta/2; ++i ) 
  {
    auto del = h.add( i );
  }

  for ( unsigned i = 0; i < delta/2; ++i ) 
  {
    h.extract_top();
  }

  return 0;
}
