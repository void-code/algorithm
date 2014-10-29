#include <vector>
#include <algorithm>
#include <cstddef>

template<typename T, typename C = std::less<T>>
class binary_heap
{
public:
  typedef T type;
  typedef C compare_type;

  binary_heap()
  {
  }

  binary_heap( std::vector<type>&& vec )
    : _heap( std::move(vec) )
  {
  }

  ~binary_heap()
  {
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

  std::vector<type> const& get_heap() const
  {
    return _heap;
  }

  void add ( type const& elem )
  {
    _heap.push_back(elem);
    if ( _heap.size() < 2 )
    {
      return;
    }
    this->sift_up (_heap.size() - 1);
  }

  type& get_root()
  {
    return _heap[0];
  }

  type const& get_root() const
  {
    return _heap[0];
  }
  
  void extract_root()
  {
    std::swap (_heap[0], _heap.back());
    _heap.pop_back();
    this->sift_down(0);
  }

private:

  void sift_up ( std::size_t indx )
  {
    std::size_t parent_indx = (indx - 1) / 2;
    while ( ! _cmp (_heap[parent_indx], _heap[indx]) )
    {
      std::swap (_heap[parent_indx], _heap[indx]);
      if ( parent_indx == 0 )
      {
        break;
      }
      indx = parent_indx;
      parent_indx = (indx - 1) / 2;
    }
  }

  void sift_down ( std::size_t indx )
  {
    std::size_t child_indx = (indx * 2) + 1;
    std::size_t best = child_indx;
    while ( child_indx < _heap.size() )
    {
      if ( child_indx + 1 < _heap.size() && _cmp (_heap[child_indx+1], _heap[child_indx]) )
      {
        best = child_indx + 1;
      }
      if ( _cmp (_heap[best], _heap[indx]) )
      {
        std::swap (_heap[best], _heap[indx]);
        indx = best;
        child_indx = (best * 2) + 1;
        best = child_indx;
      }
      else
      {
        break;
      }
    }
  }

//members
  std::vector<type> _heap;
  compare_type      _cmp;

};///binary_heap
