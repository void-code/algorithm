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
    this->sift_up (_heap.size() - 1);
  }

  type& top()
  {
    return _heap[0];
  }

  type const& top() const
  {
    return _heap[0];
  }
  
  void extract_top()
  {
    std::swap (_heap[0], _heap.back());
    _heap.pop_back();
    this->sift_down(0);
  }

private:

  void sift_up ( std::size_t indx )
  {
    std::size_t parent_indx = (indx - 1) / 2;
    while ( indx > 0 && !compare_type()(_heap[parent_indx], _heap[indx]) )
    {
      std::swap (_heap[parent_indx], _heap[indx]);
      indx = parent_indx;
      if ( indx > 0 )
      {
        parent_indx = (indx - 1) / 2;
      }
    }
  }

  void sift_down ( std::size_t indx )
  {
    std::size_t child_indx = (indx * 2) + 1;
    while ( child_indx < _heap.size() )
    {
      if ( child_indx + 1 < _heap.size() &&
            compare_type()(_heap[child_indx+1], _heap[child_indx]) )
      {
        child_indx += 1;
      }
      if ( compare_type()(_heap[child_indx], _heap[indx]) )
      {
        std::swap (_heap[child_indx], _heap[indx]);
        indx = child_indx;
        child_indx = (child_indx * 2) + 1;
      }
      else
      {
        break;
      }
    }
  }

//members
  std::vector<type> _heap;

};///binary_heap
