
#include "../binary_heap.hpp"
#include <iostream>
#include <limits>

int main()
{
  binary_heap<int> h;

  for ( unsigned i = 0; i < 1000000; ++i ) 
  {
    h.add( i );
  }

  for ( unsigned i = 0; i < 1000000; ++i ) 
  {
    h.extract_top();
  }

  return 0;
}
