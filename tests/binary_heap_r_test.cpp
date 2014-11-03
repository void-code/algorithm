#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <utility>

#include "../binary_heap_r.hpp"

int main()
{
  time_t t = std::time(0);
  //time_t t = 1414676676;
  //std::cerr << t << "\n";
  srand(t);
  std::multiset<int> s;
  binary_heap_r<int> h;
  std::vector<std::pair<decltype(h)::iterator, decltype(s)::iterator>> vd;

  for ( unsigned i = 0; i < 999; ++i )
  {
    std::size_t size = (rand() % 10000) + 1;
    for ( unsigned j = 0; j < size; ++j )
       s.insert( rand() % unsigned(1<<29) );
    h.reserve(size);
    for ( auto it = s.begin(); it != s.end(); ++it )
    {
      auto del = h.add(*it);
      vd.push_back(std::make_pair(del, it));
    }
    if ( h.top() != *s.begin() )
    {
      std::cerr << "first iteration: top() failed\n";
      std::cerr << "step " << i
                << "; ERR: " << h.top() << " != " << *s.begin()
                << ", empty: " << h.empty()
                << ", size: " << h.size() << "\n";
      return 1;
    }
    std::size_t sssize = s.size();
    for ( unsigned j = 0; j < sssize; ++j )
    {
      std::size_t indx = std::rand() % vd.size();
      std::swap( vd[indx], vd.back() );
      s.erase(vd.back().second);
      h.remove( vd.back().first );
      vd.pop_back();
      if ( !h.empty() && !s.empty() && h.top() != *s.begin() )
      {
        std::cerr << "second iteration: top() failed\n";
        std::cerr << "step " << i
                  << "; ERR: " << h.top() << " != " << *s.begin()
                  << ", empty h: " << h.empty()
                  << ", size h: " << h.size()
                  << ", empty s: " << s.empty()
                  << ", size s: " << s.size() << "\n";
        return 1;
      }
    }
    s.clear();
    h.clear();
  } 
 
  std::cout << "OK\n";
  return 0;
}
