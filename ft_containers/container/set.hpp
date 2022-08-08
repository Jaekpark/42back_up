#ifndef _FT_SET_HPP
#define _FT_SET_HPP

#include "../algorithm/equal.hpp"
#include "../algorithm/lexicographical_compare.hpp"
#include "../config.hpp"
#include "../iterator/iterator.hpp"
#include "../iterator/iterator_traits.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../iterator/tree_const_iterator.hpp"
#include "../iterator/tree_iterator.hpp"
#include "../type_traits/enable_if.hpp"
#include "../type_traits/is_integral.hpp"
#include "../type_traits/remove_const.hpp"
#include "../utility/make_pair.hpp"
#include "../utility/nullptr_t.hpp"
#include "../utility/pair.hpp"
#include "../utility/rb_tree.hpp"
#include "../utility/utility.hpp"

_BEGIN_NAMESPACE_FT

template <class Key, class Compare = std::less<Key>,
          class Allocator = std::allocator<Key> >
class set {
 public:
  typedef Key key_type;
  typedef Compare key_compare;
  typedef key_compare value_compare;
  typedef key_type value_type;
  typedef Allocator allocator_type;

  typedef ft::rb_tree<value_type, key_compare, allocator_type> tree_type;
  typedef typename tree_type::iterator iterator;
  typedef typename tree_type::const_iterator const_iterator;
  typedef typename tree_type::reverse_iterator reverse_iterator;
  typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;

 private:
  tree_type _tree;

 public:
  explicit set(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
      : _tree(tree_type(comp, alloc)) {}

  template <class InputIterator>
  set(InputIterator first, InputIterator last, const Compare& comp = Compare(),
      const Allocator& alloc = Allocator())
      : _tree(tree_type(first, last, comp, alloc)) {}

  set(const set& other) : _tree(tree_type(other._tree)) {}

  set operator=(const set& other) {
    this->_tree = other._tree;
    return (*this);
  }

  iterator begin() { return (_tree.begin()); }
  const_iterator begin() const { return (_tree.begin()); }
  iterator end() { return (_tree.end()); }
  const_iterator end() const { return (_tree.end()); }
  reverse_iterator rbegin() { return (_tree.rbegin()); }
  const_reverse_iterator rbegin() const { return (_tree.rbegin()); }
  reverse_iterator rend() { return (_tree.rend()); }
  const_reverse_iterator rend() const { return (_tree.rend()); }
  bool empty() const { return (_tree.empty()); }
  size_type size() const { return (_tree.size()); }
  size_type max_size() const { return (_tree.max_size()); }

  void clear() { _tree.clear(); }
  ft::pair<iterator, bool> insert(const value_type& val) {
    return _tree.insert(val);
  }
  iterator insert(iterator position, const value_type& val) {
    return _tree.insert(position, val);
  }
  template <class InputIterator>
  void insert(typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                     InputIterator>::type first,
              InputIterator last) {
    _tree.insert(first, last);
  }
  void erase(iterator position) { _tree.erase(position); }
  size_type erase(const Key& key) { return _tree.erase(key); }
  void erase(iterator first, iterator last) { _tree.erase(first, last); }
  iterator find(const Key& key) { return _tree.find(key); }
  const_iterator find(const Key& key) const { return _tree.find(key); }
  size_type count(const Key& key) const { return _tree.count(key); }
  iterator lower_bound(const key_type& k) { return _tree.lower_bound(k); }
  const_iterator lower_bound(const key_type& k) const {
    return _tree.lower_bound(k);
  }
  iterator upper_bound(const key_type& k) { return _tree.upper_bound(k); }
  const_iterator upper_bound(const key_type& k) const {
    return _tree.upper_bound(k);
  }
  pair<iterator, iterator> equal_range(const key_type& k) {
    return _tree.equal_range(k);
  }
  pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
    return _tree.equal_range(k);
  }
  key_compare key_comp() const { return (value_comp()); }
  value_compare value_comp() const { return (_tree.value_comp()); }
  allocator_type get_allocator() const { return _tree.get_allocator(); }

  void swap(set& x) { _tree.swap(x._tree); }
  template <class K, class C, class A>
  friend bool operator==(const set<K, C, A>& lhs, const set<K, C, A>& rhs);

  template <class K, class C, class A>
  friend bool operator<(const set<K, C, A>& lhs, const set<K, C, A>& rhs);
};

template <class Key, class Compare, class Alloc>
bool operator==(const set<Key, Compare, Alloc>& lhs,
                const set<Key, Compare, Alloc>& rhs) {
  return lhs._tree == rhs._tree;
}

template <class Key, class Compare, class Alloc>
bool operator!=(const set<Key, Compare, Alloc>& lhs,
                const set<Key, Compare, Alloc>& rhs) {
  return !(lhs == rhs);
}

template <class Key, class Compare, class Alloc>
bool operator<(const set<Key, Compare, Alloc>& lhs,
               const set<Key, Compare, Alloc>& rhs) {
  return lhs._tree < rhs._tree;
}

template <class Key, class Compare, class Alloc>
bool operator>(const set<Key, Compare, Alloc>& lhs,
               const set<Key, Compare, Alloc>& rhs) {
  return rhs < lhs;
}

template <class Key, class Compare, class Alloc>
bool operator<=(const set<Key, Compare, Alloc>& lhs,
                const set<Key, Compare, Alloc>& rhs) {
  return !(lhs > rhs);
}

template <class Key, class Compare, class Alloc>
bool operator>=(const set<Key, Compare, Alloc>& lhs,
                const set<Key, Compare, Alloc>& rhs) {
  return !(lhs < rhs);
}

template <class Key, class Compare, class Alloc>
void swap(set<Key, Compare, Alloc>& lhs, set<Key, Compare, Alloc>& rhs) {
  lhs.swap(rhs);
}

_END_NAMESPACE_FT

#endif