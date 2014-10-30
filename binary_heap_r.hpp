#include <vector>
#include <algorithm>
#include <cstddef>

template<typename T, typename R, typename C = std::less<T>>
class binary_heap_r
{
public:

  typedef T  type;
  typedef R  reset_type;
  typedef C  compare_type;

private:

  struct elem
  {
    type        value;
    std::size_t indx;
  };

public:

  struct deleter
  {
    friend class binary_heap_r<T, R, C>;
    deleter() : _elem(nullptr){}
    deleter (elem* e) : _elem(e){}
    deleter& operator= ( deleter const& ) = default;
    operator bool()
    {
      return _elem;
    }
    T const& get_value() const
    {
      return _elem->value;
    }
  private:
    elem* _elem;
  };

  binary_heap_r()
  {
  }

  ~binary_heap_r()
  {
    for ( auto p: _heap )
    {
      delete p;
    }
  }

  void reserve ( std::size_t const size )
  {
    _heap.reserve(size);
  }

  bool empty () const
  {
    return _heap.empty();
  }

  void clear()
  {
    _heap.clear();
  }

  void make ( std::vector<type>&& vec  )
  {
  }

  std::size_t size() const
  {
    return _heap.size();
  }

  deleter add ( type const& value )
  {
    _heap.push_back( new elem{value, _heap.size()});
    if ( _heap.size() < 2 )
    {
      return deleter(_heap[0]);
    }
    std::size_t const indx = this->sift_up (_heap.size() - 1);
    return deleter(_heap[indx]);
  }

  void remove ( deleter del )
  {
    _value_reset (del._elem->value);
    std::size_t indx = this->sift_down (del._elem->indx);
    std::swap( _heap[indx], _heap.back() );
    std::swap( _heap[indx]->indx, _heap.back()->indx );
    if ( indx > 0 )
    {
      this->sift_up(indx);
    }
    delete _heap.back();
    _heap.pop_back();
  }

  type& top()
  {
    return _heap[0]->value;
  }

  type const& top() const
  {
    return _heap[0].value;
  }
  
  void extract_top()
  {
    std::swap (_heap[0], _heap.back());
    delete _heap.back();
    _heap.pop_back();
    this->sift_down(0);
  }

private:

  std::size_t sift_up ( std::size_t indx )
  {
    std::size_t parent_indx = (indx - 1) / 2;
    while ( ! _cmp (_heap[parent_indx]->value, _heap[indx]->value) )
    {
      std::swap (_heap[parent_indx], _heap[indx]);
      std::swap (_heap[parent_indx]->indx, _heap[indx]->indx);
      indx = parent_indx;
      if ( parent_indx == 0 )
      {
        break;
      }
      parent_indx = (indx - 1) / 2;
    }
    return indx;
  }

  std::size_t sift_down ( std::size_t indx )
  {
    std::size_t child_indx = (indx * 2) + 1;
    std::size_t best = child_indx;
    while ( child_indx < _heap.size() )
    {
      if ( child_indx + 1 < _heap.size() && _cmp (_heap[child_indx+1]->value, _heap[child_indx]->value) )
      {
        best = child_indx + 1;
      }
      if ( _cmp (_heap[best]->value, _heap[indx]->value) )
      {
        std::swap (_heap[best], _heap[indx]);
        std::swap (_heap[best]->indx, _heap[indx]->indx);
        indx = best;
        child_indx = (best * 2) + 1;
        best = child_indx;
      }
      else
      {
        break;
      }
    }
    return indx;
  }

//members
  std::vector<elem*> _heap;
  reset_type         _value_reset;
  compare_type       _cmp;

};///binary_heap_r
