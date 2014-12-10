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

  struct elem
  {
    value_type  value;
    std::size_t indx;
  };

  struct iterator
  {
    friend class binary_heap_r<value_type, compare_type>;
    iterator() : _elem(nullptr)
    {
    }
    explicit iterator (elem* e) : _elem(e)
    {
    }
    iterator& operator= (iterator const&) = default;
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
      return this->operator*();
    }
  private:
    elem const* _elem;
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

  void reserve (std::size_t const size)
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

  void make (std::vector<value_type>&& vec)
  {
    // TODO
  }

  std::size_t size() const
  {
    return _heap.size();
  }

  iterator add (value_type const& value)
  {
    _heap.push_back( new elem{value, _heap.size()});
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

  void remove (iterator del)
  {
    std::size_t const indx = del._elem->indx;
    delete _heap[indx];
    if ( indx == (_heap.size()-1) )
    {
      _heap.pop_back();
      return;
    }
    _heap[indx] = _heap.back();
    _heap[indx]->indx = del._elem->indx;
    _heap.pop_back();
    if ( del._elem->indx == 0 )
    {
      this->sift_down(0);
      return;
    }
    if ( indx == this->sift_up(indx) )
    {
      this->sift_down(indx);
    }
  }

private:
  std::size_t sift_up (std::size_t indx)
  {
    for ( std::size_t parent_indx = (indx - 1) / 2;
            indx > 0 && !compare_type() (_heap[parent_indx]->value, _heap[indx]->value); )
    {
      std::swap (_heap[parent_indx], _heap[indx]);
      _heap[parent_indx]->indx = parent_indx;
      _heap[indx]->indx = indx;
      indx = parent_indx;
      if ( indx != 0 )
      {
        parent_indx = (indx - 1) / 2;
      }
    }
    return indx;
  }

  std::size_t sift_down (std::size_t indx)
  {
    for ( std::size_t child_indx = (indx * 2) + 1; child_indx < _heap.size(); )
    {
      if ( child_indx + 1 < _heap.size() &&
              compare_type() (_heap[child_indx+1]->value, _heap[child_indx]->value) )
      {
        child_indx += 1;
      }
      if ( compare_type() (_heap[child_indx]->value, _heap[indx]->value) )
      {
        std::swap (_heap[child_indx], _heap[indx]);
        _heap[child_indx]->indx = child_indx;
        _heap[indx]->indx = indx;
        indx = child_indx;
        child_indx = (child_indx * 2) + 1;
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
};///binary_heap_r
