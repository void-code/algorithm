
#include <queue>
#include <iostream>
#include <limits>

int main()
{
  unsigned const delta = 1000000;
  std::priority_queue<int> h;

  for ( unsigned i = 0; i < delta/2; ++i ) 
  {
    h.push( i );
  }

  for ( unsigned i = 0; i < delta/2; ++i ) 
  {
    h.pop();
  }

  return 0;
}

