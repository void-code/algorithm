#include <vector>
#include <algorithm>
#include <cstddef>

// TODO: iterator::elem --> shared_ptr with flag 'deleted'

template<typename T, typename C = std::less<T>>
class binary_heap_r
{
public:

  typedef T  value_type;
  typedef C  compare_type;

private:

  struct elem
  {
    value_type  value;
    std::size_t indx;
  };

public:

  struct iterator
  {
    friend class binary_heap_r<value_type, compare_type>;
    iterator() : _elem(nullptr){}
    iterator (elem* e) : _elem(e){}
    iterator& operator= ( iterator const& ) = default;
    operator bool()
    {
      return _elem;
    }
    T const& operator*() const
    {
      return _elem->value;
    }
    T const& operator->() const
    {
      return *this;
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

  void make ( std::vector<value_type>&& vec  )
  {
    // TODO
  }

  std::size_t size() const
  {
    return _heap.size();
  }

  iterator add ( value_type const& value )
  {
    _heap.push_back( new elem{value, _heap.size()});
    if ( _heap.size() < 2 )
    {
      return iterator(_heap[0]);
    }
    std::size_t const indx = this->sift_up (_heap.size() - 1);
    return iterator(_heap[indx]);
  }

  value_type const& top() const
  {
    return _heap[0]->value;
  }
  
  void extract_top()
  {
    delete _heap[0];
    _heap[0] = _heap.back();
    _heap[0]->indx = 0;
    _heap.pop_back();
    this->sift_down(0);
  }

  void remove ( iterator del )
  {
    delete _heap[del._elem->indx];
    _heap[del._elem->indx] = _heap.back();
    _heap[del._elem->indx]->indx = del._elem->indx;
    _heap.pop_back();
    if ( del._elem->indx == 0 )
    {
      this->sift_down(0);
      return;
    }
    std::size_t new_indx = this->sift_up(del._elem->indx);
    if ( new_indx == del._elem->indx )
    {
      this->sift_down(new_indx);
    }
  }

private:

  std::size_t sift_up ( std::size_t indx )
  {
    std::size_t parent_indx = (indx - 1) / 2;
    while ( !_cmp (_heap[parent_indx]->value, _heap[indx]->value) )
    {
      std::swap (_heap[parent_indx], _heap[indx]);
      _heap[parent_indx]->indx = parent_indx;
      _heap[indx]->indx = indx;
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
        _heap[best]->indx = best;
        _heap[indx]->indx = indx;
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
  compare_type       _cmp;

};///binary_heap_r
