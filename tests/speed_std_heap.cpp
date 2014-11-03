
#include <queue>
#include <iostream>
#include <limits>

int main()
{
  std::priority_queue<int> h;

  for ( unsigned i = 0; i < 1000000; ++i ) 
  {
    h.push( i );
  }

  for ( unsigned i = 0; i < 1000000; ++i ) 
  {
    h.pop();
  }

  return 0;
}

