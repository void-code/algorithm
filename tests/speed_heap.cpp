
#include <iostream>
#include <limits>
#include "../binary_heap.hpp"
#include <cstdlib>

int main()
{
  unsigned const delta = 100000;
  binary_heap<int> h;
  h.reserve(delta/2);
  srand(111);

  for ( unsigned i = 0; i < delta/2; ++i ) 
  {
    h.add( rand() % 100000 );
    //h.add( i );
  }
  for ( unsigned i = 0; i < delta/2; ++i ) 
  {
    h.extract_top();
  }

  return 0;
}
