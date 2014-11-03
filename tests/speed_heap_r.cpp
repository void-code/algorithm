
#include "../binary_heap_r.hpp"
#include <iostream>
#include <limits>

int main()
{
  binary_heap_r<int> h;

  for ( unsigned i = 0; i < 1000000; ++i ) 
  {
    auto del = h.add( i );
  }

  for ( unsigned i = 0; i < 1000000; ++i ) 
  {
    h.extract_top();
  }

  return 0;
}
