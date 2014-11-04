
#include <iostream>
//#include <list>

#include "../list.hpp"

int main()
{
  unsigned delta = 10;
  list<int> l;

  for ( unsigned i = 0; i < delta; ++i )
  {
    l.insert ( l.end(), i );
  }
  std::cerr << l.size() << "\n";

  list<int>::node* it = l.begin();

  //std::cerr << it->prev << ", " << it << ", " << it->next << ", " << l.end() << "\n";

  auto rm_it = l.next( it, 4 );

  l.erase ( it, rm_it );
  //l.erase ( it);

  for ( it = l.begin(); it != l.end(); )
  {
    std::cout << it->value << "\n";
    it = it->next;
  }

  l.insert ( l.begin(), 1000 );
  l.insert ( l.end(), 999 );

  it = l.next( l.begin(), 3 );

  l.erase( it, l.next(it, 3) );

  it = l.next( l.begin(), 1 );

  l.insert ( it, 777 );

  std::cerr << "\n "<< "\n";

  for ( unsigned i = 0; i < delta; ++i )
  {
    l.insert ( l.begin(), delta-i );
  }

  for ( it = l.begin(); it != l.end(); )
  {
    std::cout << it->value << "\n";
    it = it->next;
  }
  return 0;
}
