#ifndef _FT_RB_TREE_HPP
#define _FT_RB_TREE_HPP

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
#include "../utility/make_pair.hpp"
#include "../utility/nullptr_t.hpp"
#include "../utility/pair.hpp"
#include "../utility/rb_node.hpp"
#include "../utility/utility.hpp"

#define ORPHAN 0
#define ROOT 1
#define LEFT_CHILD 2
#define RIGHT_CHILD 3

_BEGIN_NAMESPACE_FT
// namespace_start
template <class T, class Compare = std::less<T>,
          class Alloc = std::allocator<T>, class Node = ft::rb_node<T>,
          class Node_alloc = std::allocator<Node> >
class rb_tree {
 public:
  typedef T value_type;
  typedef Compare value_compare;
  typedef Alloc allocator_type;
  typedef Node_alloc node_allocator;
  typedef ft::tree_iterator<T> iterator;
  typedef ft::tree_const_iterator<const T> const_iterator;
  typedef Node* node_pointer;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename allocator_type::size_type size_type;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

 private:
  allocator_type _alloc;
  node_allocator _node_alloc;
  value_compare _comp;
  node_pointer _nil;
  node_pointer _header;
  node_pointer _root;
  size_type _sz;

  node_pointer _min(node_pointer n) const {
    while (n != NULL && !_is_nil(n->left)) n = n->left;
    return n;
  }
  node_pointer _max(node_pointer n) const {
    while (n != NULL && !_is_nil(n->right)) n = n->right;
    return n;
  }

  void _rr(node_pointer n) {
    node_pointer tmp = n->left;
    n->left = tmp->right;
    if (!_is_nil(tmp->right)) tmp->right->parent = n;
    tmp->parent = n->parent;
    if (n->parent == NULL)
      _root = tmp;
    else if (n == n->parent->left)
      n->parent->left = tmp;
    else
      n->parent->right = tmp;
    tmp->right = n;
    n->parent = tmp;
  }

  void _rl(node_pointer n) {
    node_pointer tmp = n->right;
    n->right = tmp->left;
    if (!_is_nil(tmp->left)) tmp->left->parent = n;
    tmp->parent = n->parent;
    if (n->parent == NULL)
      _root = tmp;
    else if (n == n->parent->left)
      n->parent->left = tmp;
    else
      n->parent->right = tmp;
    tmp->left = n;
    n->parent = tmp;
  }

  node_pointer _insert(node_pointer new_node) {
    if (_root == _header)
      _root = new_node;
    else
      _insert_new_node(_root, new_node);
    return new_node;
  }

  node_pointer _insert_new_node(node_pointer root, node_pointer new_node) {
    if (_comp(*new_node->value, *root->value)) {
      if (!_is_nil(root->left)) return (_insert_new_node(root->left, new_node));
      root->left = new_node;
    } else {
      if (!_is_nil(root->right))
        return (_insert_new_node(root->right, new_node));
      root->right = new_node;
    }
    new_node->parent = root;
    return new_node;
  }

  node_pointer _insert_node(node_pointer new_node, node_pointer to) {
    if (_root == _header)
      _root = new_node;
    else
      _insert_new_node(to, new_node);
    return new_node;
  }

  int _whoami(node_pointer n) {
    if (!n)
      return -1;
    else if (n == _root)
      return ROOT;
    else if (n == n->parent->left)
      return LEFT_CHILD;
    else
      return RIGHT_CHILD;
  }

  void _l_balancing(node_pointer n) {
    node_pointer uncle = n->parent->parent->right;
    if (!uncle->is_black) {
      n->parent->is_black = true;
      uncle->is_black = true;
      n->parent->parent->is_black = false;
      n = n->parent->parent;
    } else {
      if (_whoami(n) == RIGHT_CHILD) {
        n = n->parent;
        _rl(n);
      }
      n->parent->is_black = true;
      n->parent->parent->is_black = false;
      _rr(n->parent->parent);
    }
  }

  void _r_balancing(node_pointer n) {
    node_pointer uncle = n->parent->parent->left;
    if (!uncle->is_black) {
      n->parent->is_black = true;
      uncle->is_black = true;
      n->parent->parent->is_black = false;
      n = n->parent->parent;
    } else {
      if (_whoami(n) == LEFT_CHILD) {
        n = n->parent;
        _rr(n);
      }
      n->parent->is_black = true;
      n->parent->parent->is_black = false;
      _rl(n->parent->parent);
    }
  }

  void _balancing(node_pointer n) {
    if (n == _root && n->parent == _root) {
      _root->is_black = true;
      return;
    }
    while (n != _root && !n->parent->is_black) {
      if (_whoami(n->parent) == LEFT_CHILD)
        _l_balancing(n);
      else
        _r_balancing(n);
    }
  }

  bool _is_nil(node_pointer n) const { return n == _nil || n == _header; }

  void _clear_node(node_pointer n) {
    if (n && !_is_nil(n)) {
      _clear_node(n->right);
      _clear_node(n->left);
      _alloc.destroy(n->value);
      _alloc.deallocate(n->value, 1);
      _node_alloc.deallocate(n, 1);
    }
  }

  void _initialize() {
    _nil = _node_alloc.allocate(1);
    _node_alloc.construct(_nil, Node());
    _nil->is_black = true;
    _nil->is_nil = true;
    _header = _node_alloc.allocate(1);
    _node_alloc.construct(_header, Node());
    _header->value = _alloc.allocate(1);
    _alloc.construct(_header->value, value_type());
    _header->is_black = true;
  }

  void _move(node_pointer to, node_pointer from) {
    if (to == _root)
      _root = from;
    else if (to == to->parent->left)
      to->parent->left = from;
    else
      to->parent->right = from;
    from->parent = to->parent;
  }

  void _free_node(node_pointer n) {
    _alloc.destroy(n->value);
    _alloc.deallocate(n->value, 1);
    _node_alloc.deallocate(n, 1);
  }

 public:
  iterator begin() {
    if (_sz == 0)
      return (iterator(_header));
    else
      return (iterator(_min(_root)));
  }
  const_iterator begin() const {
    if (_sz == 0)
      return (const_iterator(_header));
    else
      return (const_iterator(_min(_root)));
  }
  iterator end() { return (iterator(_header)); }
  const_iterator end() const { return (const_iterator(_header)); }
  reverse_iterator rbegin() { return (reverse_iterator(end())); }
  const_reverse_iterator rbegin() const {
    return (const_reverse_iterator(end()));
  }
  reverse_iterator rend() { return (reverse_iterator(begin())); }
  const_reverse_iterator rend() const {
    return (const_reverse_iterator(begin()));
  }

  pointer create_val(const value_type& val) {
    pointer tmp = _alloc.allocate(1);
    _alloc.construct(tmp, val);
    return tmp;
  }

  node_pointer copy(node_pointer n) {
    node_pointer tmp = _node_alloc.allocate(1);
    _node_alloc.construct(tmp, Node());
    tmp->is_black = n->is_black;
    tmp->is_nil = n->is_nil;
    if (n->value) {
      tmp->value = _alloc.allocate(1);
      _alloc.construct(tmp->value, *n->value);
    }
    return (tmp);
  }

  void copy_assign(node_pointer to, node_pointer from) {
    if (from->left->is_nil)
      to->left = _nil;
    else {
      to->left = copy(from->left);
      to->left->parent = to;
      copy_assign(to->left, from->left);
    }
    if (from->right->is_nil)
      to->right = _nil;
    else if (from->right->right == NULL) {
      to->right = _header;
      _header->parent = to;
    } else {
      to->right = copy(from->right);
      to->right->parent = to;
      copy_assign(to->right, from->right);
    }
  }

  node_pointer find_node(const value_type& val, node_pointer n) const {
    if (!n || _is_nil(n)) return NULL;
    if (_comp(val, *n->value)) return find_node(val, n->left);
    if (_comp(*n->value, val)) return find_node(val, n->right);
    return n;
  }

  iterator find(const value_type& val) {
    node_pointer tmp = find_node(val, _root);
    return (tmp == NULL ? end() : iterator(tmp));
  }

  const_iterator find(const value_type& val) const {
    node_pointer tmp = find_node(val, _root);
    return (tmp == NULL ? end() : const_iterator(tmp));
  }

  ft::pair<iterator, bool> insert(const value_type& val) {
    node_pointer exist = find_node(val, _root);
    if (exist) return ft::pair<iterator, bool>(iterator(exist), false);
    node_pointer tmp = _node_alloc.allocate(1);
    _node_alloc.construct(tmp, Node(create_val(val)));
    tmp->left = _nil;
    tmp->right = _nil;
    _insert_node(tmp, _root);
    ft::pair<iterator, bool> ret(iterator(tmp), true);
    _balancing(tmp);
    _sz++;
    tmp = _max(_root);
    tmp->right = _header;
    _header->parent = tmp;
    return ret;
  }

  iterator insert(iterator position, const value_type& val) {
    node_pointer exist = find_node(val, _root);
    if (exist) return (iterator(exist));
    node_pointer tmp = _node_alloc.allocate(1);
    _node_alloc.construct(tmp, Node(create_val(val)));
    tmp->left = _nil;
    tmp->right = _nil;
    if (position == begin()) {
      if (position != end() && _comp(val, *position))
        _insert_node(tmp, _min(_root));
      else
        _insert_node(tmp, _root);
    } else if (position == end()) {
      if (position != begin() && _comp(*(--position), val))
        _insert_node(tmp, _header->parent);
      else
        _insert_node(tmp, _root);
    } else
      _insert_node(tmp, _root);
    _balancing(tmp);
    _sz++;
    node_pointer max_node = _max(_root);
    max_node->right = _header;
    _header->parent = max_node;
    return (iterator(tmp));
  }

  template <class InputIterator>
  void insert(
      InputIterator first, InputIterator last,
      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* =
          ft_nullptr) {
    for (; first != last; ++first) insert(*first);
  }

  void erase(iterator position) {
    node_pointer target = position.node();
    node_pointer backup, del = target;
    bool target_is_black = target->is_black;
    if (_is_nil(target->left)) {
      backup = target->right;
      _move(target, target->right);
    } else if (_is_nil(target->right)) {
      backup = target->left;
      _move(target, target->left);
    } else {
      node_pointer tmp = target;
      target = _min(tmp->right);
      target_is_black = target->is_black;
      backup = target->right;
      if (target->parent != tmp) {
        _move(target, target->right);
        target->right = tmp->right;
        tmp->right->parent = target;
      }
      move(tmp, target);
      target->left = tmp->left;
      target->left->parent = target;
      target->is_black = tmp->is_black;
    }
    free_node(del);
    if (target_is_black) balancing_after_erase(backup);
    _sz--;
    _nil->parent = NULL;
    if (_sz == 0)
      _root = _header;
    else {
      if (_sz != 1)
        backup = _max(_root);
      else
        backup = _root;
      backup->right = _header;
      _header->parent = backup;
    }
  }

  size_type erase(const value_type& val) {
    node_pointer tmp = find_node(val, _root);
    if (tmp) erase(iterator(tmp));
    return (tmp != NULL);
  }

  void erase(iterator first, iterator last) {
    while (first != last) erase(first++);
  }

  void balancing_after_erase(node_pointer n) {
    node_pointer bro;
    while (n != _root && n->is_black) {
      if (n == n->parent->left) {
        bro = n->parent->right;
        if (!bro->is_black) {
          bro->is_black = true;
          n->parent->is_black = false;
          _rl(n->parent);
          bro = n->parent->right;
        }
        if (bro->left->is_black && bro->right->is_black) {
          bro->is_black = false;
          n = n->parent;
        } else {
          if (bro->right->is_black) {
            bro->left->is_black = true;
            bro->is_black = false;
            _rr(bro);
            bro = n->parent->right;
          }
          bro->is_black = n->parent->is_black;
          n->parent->is_black = true;
          bro->right->is_black = true;
          _rl(n->parent);
          n = _root;
        }
      } else {
        bro = n->parent->left;
        if (!bro->is_black) {
          bro->is_black = true;
          n->parent->is_black = false;
          _rr(n->parent);
          bro = n->parent->left;
        }
        if (bro->right->is_black && bro->left->iis_black) {
          bro->is_black = false;
          n = n->parent;
        } else {
          if (bro->left->is_black) {
            bro->right->is_black = true;
            bro->is_black = false;
            _rl(bro);
            bro = n->parent->left;
          }
          bro->is_black = n->parent->is_black;
          n->parent->is_black = true;
          bro->left->is_black = true;
          _rr(n->parent);
          n = _root;
        }
      }
    }
  }

  rb_tree(const Compare& comp = Compare(),
          const allocator_type& alloc = allocator_type())
      : _alloc(alloc),
        _node_alloc(node_allocator()),
        _comp(comp),
        _nil(ft_nullptr),
        _header(ft_nullptr),
        _root(ft_nullptr),
        _sz(0) {
    _initialize();
    _root = _header;
  }

  rb_tree(const rb_tree& x)
      : _alloc(allocator_type()),
        _node_alloc(node_allocator()),
        _comp(x._comp),
        _nil(ft_nullptr),
        _header(ft_nullptr),
        _root(ft_nullptr),
        _sz(0) {
    *this = x;
  }

  template <class InputIterator>
  rb_tree(typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                 InputIterator>::type first,
          InputIterator last, const value_type& comp,
          const allocator_type& alloc = allocator_type())
      : _alloc(alloc), _node_alloc(node_allocator()), _comp(comp) {
    _initialize();
    _root = _header;
    for (; first != last; ++first) insert(*first);
  }

  rb_tree& operator=(const rb_tree& x) {
    if (this == &x) return *this;
    this->_alloc = x._alloc;
    this->_node_alloc = x._node_alloc;
    this->_comp = x._comp;
    if (this->_root == NULL)
      _initialize();
    else
      _clear_node(_root);
    if (x._sz == 0)
      this->_root = this->_header;
    else {
      this->_root = copy(x._root);
      copy_assign(this->_root, x._root);
    }
    this->_sz = x._sz;
    return *this;
  }

  ~rb_tree() {
    _clear_node(_root);
    _alloc.destroy(_header->value);
    _alloc.deallocate(_header->value, 1);
    _node_alloc.deallocate(_nil, 1);
    _node_alloc.deallocate(_header, 1);
  }

  size_type size() const { return _sz; }
  size_type max_size() const { return _alloc.max_size(); }
  bool empty() const { return (_sz == 0); }
  value_compare value_comp() const { return _comp; }

  void clear() {
    clear_node(_root);
    _root = _header;
    _header->parent = NULL;
    _sz = 0;
  }

  size_type count(const value_type& val) const {
    return (find_node(val) != end());
  }

  iterator lower_bound(const value_type& val) {
    iterator last = end();
    for (iterator first = begin(); first != last; ++first) {
      if (!_compare(*first, val)) return first;
    }
    return last;
  }

  const_iterator lower_bound(const value_type& val) const {
    const_iterator last = end();
    for (const_iterator first = begin(); first != last; ++first) {
      if (!_compare(*first, val)) return first;
    }
    return last;
  }

  iterator upper_bound(const value_type& val) {
    iterator last = end();
    for (iterator first = begin(); first != last; ++first) {
      if (_compare(val, *first)) return first;
    }
    return last;
  }

  const_iterator upper_bound(const value_type& val) const {
    const_iterator last = end();
    for (const_iterator first = begin(); first != last; ++first) {
      if (_compare(val, *first)) return first;
    }
    return last;
  }

  ft::pair<iterator, iterator> equal_range(const value_type& val) {
    return (ft::make_pair(lower_bound(val), upper_bound(val)));
  }

  allocator_type get_allocator() const { return _alloc; }

  void swap(rb_tree& x) {
    allocator_type _alloc_tmp = _alloc;
    node_allocator _node_alloc_tmp = _node_alloc;
    value_compare _comp_tmp = _comp;
    node_pointer _root_tmp = _root;
    node_pointer _nil_tmp = _nil;
    node_pointer _header_tmp = _header;
    size_type _sz_tmp = _sz;

    _alloc = x._alloc;
    _node_alloc = x._node_alloc;
    _comp = x._comp;
    _root = x._root;
    _nil = x._nil;
    _header = x._header;
    _sz = x._sz;
    x._alloc = _alloc_tmp;
    x._node_alloc = _node_alloc_tmp;
    x._comp = _comp_tmp;
    x._root = _root_tmp;
    x._nil = _nil_tmp;
    x._header = _header_tmp;
    x._sz = _sz_tmp;
  }
};

template <class T, class Compare, class Alloc, class Node, class Node_alloc>
bool operator==(const rb_tree<T, Compare, Alloc, Node, Node_alloc>& lhs,
                const rb_tree<T, Compare, Alloc, Node, Node_alloc>& rhs) {
  if (lhs.size() != rhs.size()) return (lhs.size() == rhs.size());
  return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Compare, class Alloc, class Node, class Node_alloc>
bool operator!=(const rb_tree<T, Compare, Alloc, Node, Node_alloc>& lhs,
                const rb_tree<T, Compare, Alloc, Node, Node_alloc>& rhs) {
  return (!(lhs == rhs));
}

template <class T, class Compare, class Alloc, class Node, class Node_alloc>
bool operator<(const rb_tree<T, Compare, Alloc, Node, Node_alloc>& lhs,
               const rb_tree<T, Compare, Alloc, Node, Node_alloc>& rhs) {
  return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                      rhs.end()));
}

template <class T, class Compare, class Alloc, class Node, class Node_alloc>
bool operator>(const rb_tree<T, Compare, Alloc, Node, Node_alloc>& lhs,
               const rb_tree<T, Compare, Alloc, Node, Node_alloc>& rhs) {
  return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(),
                                      lhs.end()));
}

template <class T, class Compare, class Alloc, class Node, class Node_alloc>
bool operator>=(const rb_tree<T, Compare, Alloc, Node, Node_alloc>& lhs,
                const rb_tree<T, Compare, Alloc, Node, Node_alloc>& rhs) {
  if (lhs > rhs || lhs == rhs) return (true);
  return (false);
}

template <class T, class Compare, class Alloc, class Node, class Node_alloc>
bool operator<=(const rb_tree<T, Compare, Alloc, Node, Node_alloc>& lhs,
                const rb_tree<T, Compare, Alloc, Node, Node_alloc>& rhs) {
  if (lhs < rhs || lhs == rhs) return (true);
  return (false);
}

template <class T, class Compare, class Alloc, class Node, class Node_alloc>
void swap(rb_tree<T, Compare, Alloc, Node, Node_alloc>& lhs,
          rb_tree<T, Compare, Alloc, Node, Node_alloc>& rhs) {
  lhs.swap(rhs);
}

_END_NAMESPACE_FT

#endif