#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include <stdexcept>

#include "../algorithm/equal.hpp"
#include "../algorithm/lexicographical_compare.hpp"
#include "../config.hpp"
#include "../iterator/iterator.hpp"
#include "../iterator/iterator_traits.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../type_traits/enable_if.hpp"
#include "../utility/nullptr_t.hpp"

#define _ITERATOR_CATEGORY random_access_iterator_tag

_BEGIN_NAMESPACE_FT
template <class T, class Allocator = std::allocator<T> >
class vector_base {
 public:
  typedef Allocator allocator_type;
  typedef std::allocator_traits<allocator_type> alloc_traits;
  typedef typename alloc_traits::size_type size_type;

 protected:
  typedef T value_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename alloc_traits::difference_type difference_type;
  typedef typename alloc_traits::pointer pointer;
  typedef typename alloc_traits::const_pointer const_pointer;
  typedef pointer iterator;
  typedef const_pointer const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  allocator_type _alloc;
  pointer _begin;
  pointer _end;
  pointer _end_capacity;
  // * Member Functions
  size_type _capacity(void) const { return _end_cap() - _begin; }
  void clear(void) { _destruct_at_end(_begin); }
  // * Default Constructor
  explicit vector_base(const Allocator &alloc = Allocator())
      : _alloc(alloc),
        _begin(ft_nullptr),
        _end(ft_nullptr),
        _end_capacity(ft_nullptr) {}

  ~vector_base(void) {
    if (_begin != ft_nullptr) {
      clear();
      alloc_traits::deallocate(_alloc, _begin, _capacity());
    }
  }

  // * utility
 protected:
  allocator_type &_allocator(void) { return this->_alloc; }
  const allocator_type &_allocator(void) const { return this->_alloc; }
  pointer &_end_cap(void) { return this->_end_capacity; }
  const pointer &_end_cap(void) const { return this->_end_capacity; }
  value_type *to_address(pointer p) { return p; }
  void _destruct_at_end(pointer new_end) {
    pointer origin_end = this->_end;
    while (new_end != origin_end)
      alloc_traits::destroy(_alloc, to_address(--origin_end));
    this->_end = new_end;
  }
};

template <class T, class Allocator = std::allocator<T> >
class vector : public vector_base<T, Allocator> {
 private:
  typedef vector_base<T, Allocator> _base;
  typedef Allocator _default_allocator;
  typedef vector self;
  typedef typename _base::alloc_traits alloc_traits;

 public:
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef typename _base::reference reference;
  typedef typename _base::const_reference const_reference;
  typedef typename _base::size_type size_type;
  typedef typename _base::difference_type difference_type;
  typedef typename _base::pointer pointer;
  typedef typename _base::const_pointer const_pointer;
  typedef wrap_iterator<pointer> iterator;
  typedef wrap_iterator<const_pointer> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  // * utility
 private:
  void __destruct_at_end(pointer new_end) { _base::_destruct_at_end(new_end); }
  void throw_length_error(void) const {
    throw(std::length_error("ft::vector"));
  }
  size_type recommend(size_type new_size) const {
    const size_type ms = max_size();
    if (new_size > ms) this->throw_length_error();
    const size_type cap = capacity();
    if (cap >= ms / 2) return ms;
    return std::max<size_type>(2 * cap, new_size);
  }
  iterator make_iterator(pointer p) { return iterator(p); }
  const_iterator make_iterator(const_pointer p) const {
    return const_iterator(p);
  }
  pointer _vallocate(size_type n, const value_type &val = value_type()) {
    if (n > max_size()) this->throw_length_error();
    pointer p = _default_allocator().allocate(n);
    pointer temp = p;
    while (n--) _default_allocator().construct(temp++, val);
    return p;
  }
  void _construct_node(pointer p, value_type val = value_type()) {
    p = this->_alloc.construct(p, val);
  }
  void _vdeallocate(void) {
    if (this->_begin != ft_nullptr) {
      clear();
      this->_alloc.deallocate(this->_begin, capacity());
      this->_begin = ft_nullptr;
      this->_end = ft_nullptr;
      this->_end_capacity = ft_nullptr;
    }
  }
  pointer move_range(pointer first, pointer last, pointer d_first) {
    vector temp(first, last);
    iterator beg = temp.begin();
    while (beg != temp.end()) *d_first++ = *beg++;
    return d_first;
  }
  template <class InputIterator>
  void construct_with_range(
      InputIterator first, InputIterator last,
      typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                             InputIterator>::type * = ft_nullptr) {
    difference_type n = ft::distance(first, last);
    this->_begin = this->_alloc.allocate(n);
    this->_end = this->_begin;
    this->_end_capacity = this->_begin + n;
    while (n--) this->_alloc.construct(this->_end++, *first++);
  }
  template <class InputIterator>
  void construct_with_range(
      InputIterator first, InputIterator last, size_type capacity,
      typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                             InputIterator>::type * = ft_nullptr) {
    difference_type n = ft::distance(first, last);
    this->_begin = this->_alloc.allocate(capacity);
    this->_end = this->_begin;
    this->_end_capacity = this->_begin + capacity;
    while (n--) this->_alloc.construct(this->_end++, *first++);
  }

 public:
  // * Constructor
  // * Default Constructor
  vector(void) : _base() {}
  // explicit vector(const Allocator &alloc) : {}
  // * Fill Constructor
  vector(size_type n, const value_type &val = value_type(),
         const Allocator &alloc = Allocator())
      : _base(alloc) {
    this->_begin = _vallocate(n, val);
    this->_end = this->_begin + n;
    this->_end_capacity = this->_end;
  }
  // * Range Constructor
  template <class InputIterator>
  vector(InputIterator first, InputIterator last,
         const Allocator &alloc = Allocator(),
         typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                InputIterator>::type * = ft_nullptr)
      : _base(alloc) {
    construct_with_range(first, last);
  }
  // * Copy Constructor
  vector(const vector &x) { construct_with_range(x.begin(), x.end()); }
  // * operator=
  vector &operator=(const vector &x) {
    clear();
    assign(x.begin(), x.end());
    return *this;
  }

  // * Destructor
  ~vector(void) {}
  // * Assign
  void assign(size_type n, const T &value) {
    if (n >= capacity()) reserve(recommend(n));
    clear();
    while (n--) push_back(value);
  };
  template <class InputIterator>
  void assign(InputIterator first, InputIterator last,
              typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                     InputIterator>::type * = ft_nullptr) {
    difference_type n = ft::distance(first, last);
    if (static_cast<size_type>(n) >= capacity()) reserve(recommend(n));
    clear();
    for (; first != last; ++first) push_back(*first);
  }
  // * Allocator
  allocator_type get_allocator(void) const { return this->_allocator(); }
  // * Iterator
  iterator begin(void) { return make_iterator(this->_begin); }
  const_iterator begin(void) const { return make_iterator(this->_begin); }
  iterator end(void) { return make_iterator(this->_end); }
  const_iterator end(void) const { return make_iterator(this->_end); }
  reverse_iterator rbegin(void) { return reverse_iterator(end()); }
  const_reverse_iterator rbegin(void) const {
    return const_reverse_iterator(end());
  }
  reverse_iterator rend(void) { return reverse_iterator(begin()); }
  const_reverse_iterator rend(void) const { return reverse_iterator(begin()); }
  // * capacity
  size_type size(void) const { return end() - begin(); }
  size_type max_size(void) const { return get_allocator().max_size(); }
  void resize(size_type n, value_type val = value_type()) {
    size_type sz = size();
    if (n > max_size())
      throw(std::length_error("vector::resize"));
    else if (sz > n)
      for (; sz != n; sz--) get_allocator().destroy(this->_end--);
    else
      for (; sz != n; sz++) get_allocator().construct(this->_end++, val);
  }
  size_type capacity(void) const { return this->_capacity(); }
  bool empty(void) const { return size() == 0 ? true : false; }
  void reserve(size_type n) {
    if (n > max_size())
      throw(std::length_error("vector::reserve"));
    else if (n > capacity()) {
      pointer new_begin = _vallocate(n);
      size_type sz = size();
      move_range(this->_begin, this->_end, new_begin);
      _vdeallocate();
      this->_begin = new_begin;
      this->_end = new_begin + sz;
      this->_end_capacity = new_begin + n;
    }
  }

  // * Element access
  reference operator[](size_type n) { return *(begin() + n); }
  const_reference operator[](size_type n) const { return *(begin() + n); }
  reference at(size_type n) {
    if (n >= size()) throw(std::out_of_range("vector::at"));
    return *(begin() + n);
  }
  const_reference at(size_type n) const {
    if (n >= size()) throw(std::out_of_range("vector::at"));
    return *(begin() + n);
  }
  reference front(void) { return *(begin()); }
  const_reference front(void) const { return *(begin()); }
  reference back(void) { return *(end() - 1); }
  const_reference back(void) const { return *(end() - 1); }
  // * modifiers

  void swap(vector &x) {
    allocator_type temp_alloc = get_allocator();
    pointer temp_begin = this->_begin;
    pointer temp_end = this->_end;
    pointer temp_cap = this->_end_capacity;

    this->_alloc = x.get_allocator();
    this->_begin = x._begin;
    this->_end = x._end;
    this->_end_capacity = x._end_capacity;

    x._alloc = temp_alloc;
    x._begin = temp_begin;
    x._end = temp_end;
    x._end_capacity = temp_cap;
  }
  void push_back(const T &x) {
    if (size() >= capacity()) reserve(recommend(size() + 1));
    this->_alloc.construct(this->_end++, x);
  }  // - impl
  void pop_back(void) {
    if (!empty()) this->_destruct_at_end(this->_end - 1);
  }
  iterator insert(iterator position, const T &x) {
    difference_type pos = position - begin();
    if (size() >= capacity()) reserve(recommend(size() + 1));
    pointer p = this->_begin + pos;
    move_range(p, end().base(), p + 1);
    this->_alloc.construct(p, x);
    this->_end++;
    return make_iterator(p);
  }  // - impl
  void insert(iterator position, size_type n, const T &x) {
    difference_type pos = position - begin();
    if (size() + n > capacity()) reserve(recommend(size() + n));
    pointer p = this->_begin + pos;
    move_range(p, end().base(), p + n);
    while (n--) {
      this->_alloc.construct(p++, x);
      this->_end++;
    }
  }
  template <class InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last,
              typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                     InputIterator>::type * = ft_nullptr) {
    difference_type pos = position - begin();
    size_type n = last - first;
    if (size() + n > capacity()) reserve(recommend(size() + n));
    pointer p = this->_begin + pos;
    move_range(p, end().base(), p + n);
    while (first != last) {
      this->_alloc.construct(p++, *first++);
      this->_end++;
    }
  }
  iterator erase(iterator position) {
    difference_type pos = position - this->begin();
    pointer p = this->_begin + pos;
    __destruct_at_end(move_range(p + 1, end().base(), p));
    iterator r = make_iterator(p);
    return r;
  }
  iterator erase(iterator first, iterator last) {
    difference_type pos = first - begin();
    pointer p = this->_begin + pos;
    if (first != last)
      __destruct_at_end(move_range(p + (last - first), end().base(), p));
    iterator r = make_iterator(p);
    return r;
  }
  void clear(void) { __destruct_at_end(begin().base()); }
};

template <class T, class Allocator>
bool operator==(const vector<T, Allocator> &lhs,
                const vector<T, Allocator> &rhs) {
  const typename vector<T, Allocator>::size_type sz = lhs.size();
  return sz == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}
template <class T, class Allocator>
bool operator!=(const vector<T, Allocator> &lhs,
                const vector<T, Allocator> &rhs) {
  return !(lhs == rhs);
}
template <class T, class Allocator>
bool operator<(const vector<T, Allocator> &lhs,
               const vector<T, Allocator> &rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}
template <class T, class Allocator>
bool operator<=(const vector<T, Allocator> &lhs,
                const vector<T, Allocator> &rhs) {
  return !(rhs < lhs);
}
template <class T, class Allocator>
bool operator>(const vector<T, Allocator> &lhs,
               const vector<T, Allocator> &rhs) {
  return (rhs < lhs);
}
template <class T, class Allocator>
bool operator>=(const vector<T, Allocator> &lhs,
                const vector<T, Allocator> &rhs) {
  return !(lhs < rhs);
}
template <class T, class Allocator>
void swap(vector<T, Allocator> &x, vector<T, Allocator> &y) {
  x.swap(y);
}

_END_NAMESPACE_FT

#endif