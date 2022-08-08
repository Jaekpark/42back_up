#ifndef _FT_MAP_HPP
#define _FT_MAP_HPP

#include <functional>
#include <memory>

#include "../algorithm/equal.hpp"
#include "../algorithm/lexicographical_compare.hpp"
#include "../config.hpp"
#include "../iterator/bst_const_iterator.hpp"
#include "../iterator/bst_iterator.hpp"
#include "../iterator/iterator.hpp"
#include "../iterator/iterator_traits.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../type_traits/enable_if.hpp"
#include "../type_traits/is_integral.hpp"
#include "../type_traits/remove_const.hpp"
#include "../utility/binary_search_tree.hpp"
#include "../utility/bst_node.hpp"
#include "../utility/make_pair.hpp"
#include "../utility/nullptr_t.hpp"
#include "../utility/pair.hpp"
#include "../utility/utility.hpp"

_BEGIN_NAMESPACE_FT
// namespace_start
template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
 private:
  typedef ft::binary_search_tree<ft::pair<Key, T> > _tree_type;
  typedef typename _tree_type::n_pointer n_pointer;
  typedef typename _tree_type::node_type node_type;

 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef ft::pair<key_type, mapped_type> value_type;
  typedef Compare key_compare;
  typedef Allocator allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;
  typedef ft::bst_iterator<node_type> iterator;
  typedef ft::bst_const_iterator<node_type> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  class value_compare
      : public ft::binary_function<value_type, value_type, bool> {
    friend class map;

   protected:
    key_compare comp;
    value_compare(const key_compare& compare) : comp(compare) {}

   public:
    bool operator()(const value_type& x, const value_type& y) const {
      return (comp(x.first, y.first));
    }
  };

 private:
  key_compare _comp;
  allocator_type _alloc;
  _tree_type _bst;

 public:
  /* ---------------------- DEFAULT CONSTRUCTOR --------------------- */
  explicit map(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
      : _comp(comp), _alloc(alloc), _bst() {}
  /* ----------------------- RANGE CONSTRUCTOR ---------------------- */
  template <class InputIterator>
  map(InputIterator first, InputIterator last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type())
      : _comp(comp), _alloc(alloc), _bst() {
    while (first != last) insert(*first++);
  }
  /* ----------------------- COPY CONSTRUCTOR ----------------------- */
  map(const map& x) : _comp(x._comp), _alloc(x._alloc), _bst() {
    for (iterator it = x.begin(); it != x.end(); it++) insert(*it);
  }
  /* -------------------------- DESTRUCTOR -------------------------- */
  ~map(void) {}

  /* ---------------------------------------------------------------- */
  /*                       ASSIGNMENT OPERATOR=                       */
  /* ---------------------------------------------------------------- */
  map& operator=(const map& x) {
    if (this == &x) return *this;
    this->clear();
    this->insert(x.begin(), x.end());
  }

  /* ---------------------------------------------------------------- */
  /*                             ITERATORS                            */
  /* ---------------------------------------------------------------- */

  iterator begin() {
    if (_bst.get_size() == 1)
      return iterator(_bst.get_root());
    else if (_bst.get_size() > 1 && _bst.get_root())
      return iterator(_bst.min(_bst.get_root()));
    return iterator(_bst.get_last());
  }
  const_iterator begin() const {
    if (_bst.get_size() == 1)
      return const_iterator(_bst.get_root());
    else if (_bst.get_size() > 1 && _bst.get_root())
      return const_iterator(_bst.min(_bst.get_root()));
    return const_iterator(_bst.get_last());
  }
  iterator end() { return iterator(_bst.get_last()); }
  const_iterator end() const { return const_iterator(_bst.get_last()); }
  reverse_iterator rbegin() { return (reverse_iterator(this->end())); }
  const_reverse_iterator rbegin() const {
    return (const_reverse_iterator(this->end()));
  }
  reverse_iterator rend() { return (reverse_iterator(this->begin())); }
  const_reverse_iterator rend() const {
    return (const_reverse_iterator(this->begin()));
  }

  /* ---------------------------------------------------------------- */
  /*                             CAPACITY                             */
  /* ---------------------------------------------------------------- */
  // - done
  bool empty() const {
    if (!_bst.get_size()) return true;
    return false;
  }
  size_type size() const { return static_cast<size_type>(_bst.get_size()); }
  size_type max_size() const {
    return static_cast<size_type>(_bst.get_max_size());
  }

  /* ---------------------------------------------------------------- */
  /*                          ELEMENT ACCESS                          */
  /* ---------------------------------------------------------------- */

  mapped_type& operator[](const key_type& k) {
    iterator tmp = this->find(k);

    if (tmp == this->end()) this->insert(ft::make_pair(k, mapped_type()));
    tmp = this->find(k);
    return ((*tmp).second);
    n_pointer target = _bst.find(_bst.get_root(), k);
    if (target && target != end()._base())
      return target->get_value_ref().second;
    value_type val = ft::make_pair<key_type, mapped_type>(k, mapped_type());
    return _bst.insert(_bst.get_root(), val)->get_value_ref().second;
  }

  /* ---------------------------------------------------------------- */
  /*                             MODIFIERS                            */
  /* ---------------------------------------------------------------- */

  ft::pair<iterator, bool> insert(const value_type& val) {
    n_pointer node_exist = _bst.find(_bst.get_root(), val);
    if (node_exist != _bst.get_last())
      return ft::pair<iterator, bool>(iterator(node_exist), false);
    return ft::pair<iterator, bool>(iterator(_bst.insert(_bst.get_root(), val)),
                                    true);
  }
  iterator insert(iterator position, const value_type& val) {
    if (position->first > val.first) {
      iterator prev(position);
      --prev;
      while (prev >= begin() && prev->first >= val.first) {
        --position;
        --prev;
      }
    } else if (position->first < val.first) {
      iterator next(position);
      ++next;
      while (next != end() && next->first <= val.first) {
        ++position;
        ++next;
      }
    }
    if (position != end() && val.first == position->first) return position;
    return iterator(_bst.insert(position._base(), val));
  }

  template <class InputIterator>
  void insert(
      InputIterator first, InputIterator last,
      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* =
          ft_nullptr) {
    while (first != last) insert(*first++);
  }

  void erase(iterator position) {
    if (position != end()) _bst.delete_node(position._base());
  }
  size_type erase(const key_type& k) {
    n_pointer target = _bst.find(_bst.get_root(), k);
    if (!target) return 0;
    if (target != end()._base()) _bst.delete_node(target);
    return 1;
  }
  void erase(iterator first, iterator last) {
    while (first != last) this->erase((*(first++)).first);
  }

  void swap(map& x) {
    key_compare _comp_tmp = _comp;
    allocator_type _alloc_tmp = _alloc;

    _comp = x._comp;
    _alloc = x._alloc;
    _bst.swap(x._bst);
    x._comp = _comp_tmp;
    x._alloc = _alloc_tmp;
  }
  void clear() {
    _bst.destroy(_bst.get_root());
    _bst.set_size(0);
  }

  /* ---------------------------------------------------------------- */
  /*                             OBSERVERS                            */
  /* ---------------------------------------------------------------- */

  key_compare key_comp() const { return key_compare(); }
  value_compare value_comp() const { return value_compare(key_compare()); }

  /* ---------------------------------------------------------------- */
  /*                            OPERATIONS                            */
  /* ---------------------------------------------------------------- */

  iterator find(const key_type& k) {
    return iterator(_bst.find(_bst.get_root(), k));
  }
  const_iterator find(const key_type& k) const {
    return const_iterator(_bst.find(_bst.get_root(), k));
  }
  size_type count(const key_type& k) const {
    size_type cnt = 0;
    _bst.preorder_count(_bst.get_root(), k, cnt);
    return cnt;
  }
  iterator lower_bound(const key_type& k) {
    iterator begin = this->begin();
    iterator end = this->end();

    while (begin != end) {
      if (_comp((*begin).first, k) == false) break;
      begin++;
    }
    return begin;
  }
  const_iterator lower_bound(const key_type& k) const {
    return const_iterator(this->lower_bound(k));
  }
  iterator upper_bound(const key_type& k) {
    iterator begin = this->begin();
    iterator end = this->end();
    while (begin != end) {
      if (_comp(k, (*begin).first)) break;
      begin++;
    }
    return begin;
  }
  const_iterator upper_bound(const key_type& k) const {
    return const_iterator(this->upper_bound(k));
  }
  ft::pair<const_iterator, const_iterator> equal_range(
      const key_type& k) const {
    return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
  }

  ft::pair<iterator, iterator> equal_range(const key_type& k) {
    return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
  }
  /* ---------------------------------------------------------------- */
  /*                             ALLOCATOR                            */
  /* ---------------------------------------------------------------- */
  allocator_type& get_allocator() const { return _alloc; }
};

template <class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs) {
  if (lhs.size() != rhs.size()) return (lhs.size() == rhs.size());
  return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs) {
  return (!(lhs == rhs));
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key, T, Compare, Alloc>& lhs,
               const map<Key, T, Compare, Alloc>& rhs) {
  return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                      rhs.end()));
}
template <class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key, T, Compare, Alloc>& lhs,
               const map<Key, T, Compare, Alloc>& rhs) {
  return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(),
                                      lhs.end()));
}
template <class Key, class T, class Compare, class Alloc>
bool operator>=(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs) {
  if (lhs > rhs || lhs == rhs) return (true);
  return (false);
}
template <class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key, T, Compare, Alloc>& lhs,
                const map<Key, T, Compare, Alloc>& rhs) {
  if (lhs < rhs || lhs == rhs) return (true);
  return (false);
}
template <class Key, class T, class Compare, class Alloc>
void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y) {
  x.swap(y);
}
_END_NAMESPACE_FT
// namespace_end
#endif