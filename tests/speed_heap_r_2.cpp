
#include "../binary_heap_r.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

int main()
{
  srand(time(0));
  unsigned const delta = 1000000;
  unsigned const div_delta = delta/2;
  binary_heap_r<int> h;
  h.reserve(delta/2);

  decltype(h)::iterator it ( new decltype(h)::elem );

  for ( unsigned i = 0; i < div_delta; ++i ) 
  {
    auto del = h.add( i );
  }

  for ( unsigned i = 0; i < div_delta; ++i ) 
  {   
    it._elem->indx = std::rand() % (div_delta - i);
    h.remove(it);
  }

  return 0;
}

