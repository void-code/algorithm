#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "../binary_heap.hpp"

int main()
{
  srand(std::time(0));
  std::vector<int> v;
  binary_heap<int> h;

  for ( unsigned i = 0; i < 999; ++i )
  {
    v.resize( (rand() % 10000) + 1 );
    for ( unsigned j = 0; j < v.size(); ++j )
      v[j] = rand() % unsigned(1<<29);
    h.reserve(v.size());
    for ( auto x: v )
      h.add(x);
    std::sort( v.begin(), v.end() );
    if ( h.top() != v[0] )
    {
      std::cerr << "top() failed\n";
      std::cerr << "step " << i
                << "; ERR: " << h.top() << " != " << v[0]
                << ", empty: " << h.empty()
                << ", size: " << h.get_heap().size() << "\n";
      return 1;
    }
    for ( unsigned j = 0; j < v.size(); ++j )
    {
      if ( h.top() != v[j] )
      {
        std::cerr << "step " << i << ", iteration " << j
                  << "; ERR: " << h.top() << " != " << v[j] << "\n";
        return 1;
      }
      h.extract_top();
    }
    v.clear();
    h.clear();
  } 
 
  std::cout << "OK\n";
  return 0;
}
