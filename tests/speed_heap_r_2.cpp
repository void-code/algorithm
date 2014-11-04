
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include "../binary_heap_r.hpp"

int main()
{
  srand(time(0));
  unsigned const delta = 100000;
  unsigned const div_delta = delta;
  binary_heap_r<int> h;
  h.reserve(delta/2);

  decltype(h)::iterator it ( new decltype(h)::elem );

  for ( unsigned i = 0; i < div_delta; ++i ) 
  {
    h.add( rand() % 1000000 );
    //auto del = h.add( i );
  }

  for ( unsigned i = 0; i < div_delta; ++i ) 
  {   
    it._elem->indx = std::rand() % (div_delta - i);
    h.remove(it);
    //h.extract_top();
  }

  return 0;
}

