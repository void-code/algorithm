
#include <cstddef>

template<typename T>
class list
{
public:
  typedef T value_type;

  struct node
  {
    value_type value;
    node* prev;
    node* next;
  };

  list()
    : _size(0)
    , _beg (new node {value_type(), nullptr, nullptr})
    , _end (_beg)
  {
  }

  node* end()
  {
    return _end;
  }

  node* begin()
  {
    return _beg;
  }

  /*
  void push_back (value_type const& val)
  {
    this->insert (_end, val);
  }
  */

  node* insert (node* pos, value_type const& val)
  {
    node* new_node = new node ({val, pos->prev, pos});
    if ( pos->prev )
    {
      pos->prev->next = new_node;
    }
    else
    {
      _beg = new_node;
    }
    pos->prev = new_node;
    ++_size;
    return new_node;
  }

  void erase (node* beg, node* end)
  {
    if ( beg == end )
    {
      return;
    }
    if ( beg->prev )
    {
      beg->prev->next = end;
    }
    else
    {
      _beg = end;
    }
    end->prev = beg->prev;
    for ( node* remove; beg != end; --_size )
    {
      remove = beg;
      beg = beg->next;
      delete remove;
    }
  }

  void erase (node* rm_node)
  {
    if ( rm_node->prev )
    {
      rm_node->prev->next = rm_node->next;
    }
    else
    {
      _beg = rm_node->next;
    }
    rm_node->next->prev = rm_node->prev;
    delete rm_node;
    --_size;
  }

  std::size_t size() const
  {
    return _size;
  }

  node* next (node* pos, std::size_t step = 1)
  {
    for ( ; step && pos != _end; --step )
    {
      pos = pos->next;
    }
    return pos;
  }

  node* prev (node* pos, std::size_t step = 1)
  {
    for ( ; step && pos != nullptr; --step )
    {
      pos = pos->prev;
    }
    return pos;
  }

private:
  std::size_t _size;
  node* _beg;
  node* _end;

};//list
