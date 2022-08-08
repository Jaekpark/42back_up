#ifndef _FT_TREE_CONST_ITERATOR_HPP
#define _FT_TREE_CONST_ITERATOR_HPP

#include "../config.hpp"
#include "../utility/rb_node.hpp"
#include "./iterator.hpp"
#include "./iterator_traits.hpp"

// namespace_start
_BEGIN_NAMESPACE_FT
template <class T>
class tree_const_iterator {
 public:
  typedef ft::bidirectional_iterator_tag iterator_category;
  typedef typename ft::iterator_traits<T*>::value_type value_type;
  typedef typename ft::iterator_traits<T*>::reference reference;
  typedef typename ft::iterator_traits<T*>::difference_type difference_type;
  typedef typename ft::iterator_traits<T*>::pointer pointer;
  typedef typename ft::rb_node<T> *node_pointer;

 private:
  node_pointer _node;

 public:
  tree_const_iterator() {}
  tree_const_iterator(node_pointer node) : _node(node) {}
  tree_const_iterator(const tree_const_iterator &x) { *this = x; }
  tree_const_iterator &operator=(const tree_const_iterator &x) {
    this->_node = x._node;
    return *this;
  }
  ~tree_const_iterator() {}
  node_pointer min(node_pointer n) const {
    while (n->left != NULL && !n->left->is_nil) n = n->left;
    return n;
  }
  node_pointer max(node_pointer n) const {
    while (!n->right->is_nil) n = n->right;
    return n;
  }
  reference operator*() const { return *(_node->value); }
  pointer operator->() const { return _node->value; }
  tree_const_iterator &operator++() {
    if (_node->right && !_node->right->is_nil) {
      _node = min(_node->right);
    } else {
      node_pointer tmp = _node->parent;
      while (tmp != NULL && _node == tmp->right) {
        _node = tmp;
        tmp = tmp->parent;
      }
      _node = tmp;
    }
    return *this;
  }
  tree_const_iterator operator++(int) {
    tree_const_iterator temp = *this;
    if (!_node->right->is_nil) {
      _node = min(_node->right);
    } else {
      node_pointer tmp = _node->parent;
      while (tmp != NULL && _node == tmp->right) {
        _node = tmp;
        tmp = tmp->parent;
      }
      _node = tmp;
    }
    return temp;
  }

  tree_const_iterator &operator--() {
    if (_node->left && !_node->left->is_nil) {
      _node = max(_node->left);
    } else {
      node_pointer tmp = _node->parent;
      while (tmp != NULL && _node == tmp->left) {
        _node = tmp;
        tmp = tmp->parent;
      }
      _node = tmp;
    }
    return *this;
  }

  tree_const_iterator operator--(int) {
    tree_const_iterator temp = *this;
    if (_node->left && !_node->left->is_nil) {
      _node = max(_node->left);
    } else {
      node_pointer tmp = _node->parent;
      while (tmp != NULL && _node == tmp->left) {
        _node = tmp;
        tmp = tmp->parent;
      }
      _node = tmp;
    }
    return *temp;
  }
  node_pointer node() const { return _node; }
};

template <class T1, class T2>
bool operator==(const tree_const_iterator<T1> &lhs,
                const tree_const_iterator<T2> &rhs) {
  return (lhs.node() == rhs.node());
}

template <class T1, class T2>
bool operator!=(const tree_const_iterator<T1> &lhs,
                const tree_const_iterator<T2> &rhs) {
  return (lhs.node() != rhs.node());
}
_END_NAMESPACE_FT
// namespace_end
#endif