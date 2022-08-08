#ifndef _FT_BINARY_SEARCH_TREE_HPP
#define _FT_BINARY_SEARCH_TREE_HPP

#include <functional>
#include <memory>

#include "../config.hpp"
#include "../iterator/bst_const_iterator.hpp"
#include "../iterator/bst_iterator.hpp"
#include "../utility/bst_node.hpp"
#include "../utility/nullptr_t.hpp"

_BEGIN_NAMESPACE_FT
template <class T, class Compare = std::less<T>, class Node = ft::bst_node<T>,
          class Allocator = std::allocator<T>,
          class Node_Allocator = std::allocator<Node> >
class binary_search_tree {
  /* ---------------------------------------------------------------- */
  /*                           TYPE ALIASES                           */
  /* ---------------------------------------------------------------- */

 public:
  typedef binary_search_tree tree;
  typedef tree &tree_reference;
  typedef tree *tree_pointer;

  typedef T value_type;
  typedef const T const_value_type;
  typedef Allocator allocator_type;
  typedef typename value_type::first_type key_type;
  typedef typename value_type::second_type mapped_type;
  typedef typename Allocator::reference reference;
  typedef typename Allocator::const_reference const_reference;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;
  typedef typename Allocator::size_type size_type;
  typedef typename Allocator::difference_type difference_type;

  typedef Compare compare;
  typedef Node node_type;
  typedef Node_Allocator n_allocator_type;
  typedef typename n_allocator_type::reference n_reference;
  typedef typename n_allocator_type::const_reference n_const_reference;
  typedef typename n_allocator_type::pointer n_pointer;
  typedef typename n_allocator_type::const_pointer n_const_pointer;
  typedef typename n_allocator_type::size_type n_size_type;
  typedef typename n_allocator_type::difference_type n_difference_type;
  typedef ft::bst_iterator<Node> iterator;
  typedef ft::bst_const_iterator<Node> const_iterator;

  /* ---------------------------------------------------------------- */
  /*                            ATTRIBUTES                            */
  /* ---------------------------------------------------------------- */
 private:
  n_size_type _sz;          // Number of nodes in this bst
  n_allocator_type _alloc;  // Allocator for bst_node
  n_pointer _root;          // A pointer variable pointing to root node
  n_pointer _last;          // A pointer variable pointing to last node

 public:
  /* ---------------------- DEFAULT CONSTRUCTOR --------------------- */
  binary_search_tree(const n_allocator_type &alloc = n_allocator_type())
      : _sz(0),
        _alloc(alloc),
        _root(ft_nullptr),
        _last(create_node(const_value_type())) {}

  /* -------------------------- DESTRUCTOR -------------------------- */
  ~binary_search_tree(void) {
    if (_sz) destroy(_root);
    if (_last) deallocate_node(_last);
  };
  // * member functions
  void swap(tree &x) {
    n_size_type sz_tmp = _sz;
    n_allocator_type alloc_tmp = _alloc;
    n_pointer root_tmp = _root;
    n_pointer last_tmp = _last;

    _sz = x._sz;
    _alloc = x._alloc;
    _root = x._root;
    _last = x._last;

    x._sz = sz_tmp;
    x._alloc = alloc_tmp;
    x._root = root_tmp;
    x._last = last_tmp;
  }
  n_size_type get_size(void) const { return _sz; }
  void set_size(n_size_type new_sz) { this->_sz = new_sz; }
  n_size_type get_max_size() const { return _alloc.max_size(); }
  n_pointer get_root(void) const { return _root; }
  n_pointer get_last(void) const { return _last; }
  void set_root(n_pointer node) { this->_root = node; }
  void set_last(n_pointer node) { this->_last = node; }
  int get_depth(n_pointer start, n_pointer target, int depth) {
    if (!start || !target) return -1;
    if (start == target) return depth;
    if (start->get_left_node() < target)
      return get_depth(start->get_right_node(), target, ++depth);
    return get_depth(start->get_left_node(), target, ++depth);
  }
  n_pointer find(n_pointer start, const value_type &val) {
    if (!start)
      return _last;
    else if (start->get_value_ref() == val)
      return start;
    else if (start->get_value_ref() < val)
      return find(start->get_right_node(), val);
    return find(start->get_left_node(), val);
  }
  n_pointer find(n_pointer start, const key_type &k) {
    if (!start)
      return _last;
    else if (start->get_value_ref().first == k)
      return start;
    else if (start->get_value_ref().first < k)
      return find(start->get_right_node(), k);
    return find(start->get_left_node(), k);
  }
  n_pointer create_node(const value_type &val, n_pointer parent = ft_nullptr,
                        n_pointer left = ft_nullptr,
                        n_pointer right = ft_nullptr) {
    n_pointer new_node = this->_alloc.allocate(1);
    new_node->set_value(val);
    new_node->set_parent_node(parent);
    new_node->set_left_node(left);
    new_node->set_right_node(right);
    new_node->set_last_node(this->_last);
    return new_node;
  }
  n_pointer insert(n_pointer node, const value_type &val) {
    if (!node && _sz) {
      this->_sz++;  // note : 확인
      return create_node(val);
    } else if (!node && !_sz) {
      this->_sz++;
      _root = create_node(val);
      _last->set_parent_node(_root);
      return _root;
    }
    if (val.first < node->get_value_ref().first) {
      n_pointer left = insert(node->get_left_node(), val);
      node->set_left_node(left);
      left->set_parent_node(node);
      _last->set_parent_node(max(_root));
    } else if (val.first > node->get_value_ref().first) {
      n_pointer right = insert(node->get_right_node(), val);
      node->set_right_node(right);
      right->set_parent_node(node);
      _last->set_parent_node(max(_root));
    }
    return node;
  }
  void traversal(n_pointer node, n_size_type &size) {
    if (node) {
      ++size;
      traversal(node->get_left_node(), size);
      traversal(node->get_right_node(), size);
    }
  }
  void inorder(n_pointer node, void (*f)(tree *, n_pointer, T)) {
    if (node) {
      inorder(node->get_left_node(), f);
      f(this, node, node->get_value_ref());
      inorder(node->get_right_node(), f);
    }
  }
  void preorder(n_pointer node, void (*f)(tree *, n_pointer, T)) {
    if (node) {
      f(this, node, node->get_value_ref());
      preorder(node->get_left_node(), f);
      preorder(node->get_right_node(), f);
    }
  }
  void postorder(n_pointer node, void (*f)(tree *, n_pointer, T)) {
    if (node) {
      postorder(node->get_left_node(), f);
      postorder(node->get_right_node(), f);
      f(this, node, node->get_value_ref());
    }
  }
  void preorder_count(n_pointer node, const key_type &k, size_t &count) const {
    if (node) {
      if (node->get_value_ref().first == k) ++count;
      preorder_count(node->get_left_node(), k, count);
      preorder_count(node->get_right_node(), k, count);
    }
  }
  void destroy(n_pointer node) {
    if (node) {
      destroy(static_cast<n_pointer>(node->get_left_node()));
      destroy(static_cast<n_pointer>(node->get_right_node()));
      _alloc.deallocate(node, 1);
    }
  }
  void deallocate_node(n_pointer node) {
    if (node) _alloc.deallocate(node, 1);
  }
  void delete_node(n_pointer node) {
    if (node && node != _last) {
      int cond = node->node_relation(node->has_parent(node),
                                     node->has_left_child(node),
                                     node->has_right_child(node));
      switch (cond) {
        case ROOT_NO_CHILD:
          delete_node_has_no_child(node);
          break;
        case ROOT_HAS_LEFT:
          delete_node_has_one_child(node, true);
          break;
        case ROOT_HAS_RIGHT:
          delete_node_has_one_child(node, false);
          break;
        case ROOT_HAS_BOTH:
          delete_node_has_both_child(node);
          break;
        case HAS_PARENT_NO_CHILD:
          delete_node_has_no_child(node);
          break;
        case HAS_PARENT_AND_LEFT:
          delete_node_has_one_child(node, true);
          break;
        case HAS_PARENT_AND_RIGHT:
          delete_node_has_one_child(node, false);
          break;
        case HAS_PARENT_AND_BOTH:
          delete_node_has_both_child(node);
          break;
        default:
          break;
      }
    }
  }
  void delete_node_has_one_child(n_pointer node, bool node_has_left_child) {
    n_pointer parent = node->get_parent_node();
    if (parent && node_has_left_child) {
      if (node->is_left_child(node))
        set_relation(parent, node->get_left_node(), true);
      else
        set_relation(parent, node->get_left_node(), false);
    } else if (parent && !node_has_left_child) {
      if (node->is_left_child(node))
        set_relation(parent, node->get_right_node(), true);
      else
        set_relation(parent, node->get_right_node(), false);
    } else if (!parent && node_has_left_child)
      _root = node->get_left_node();
    else if (!parent && !node_has_left_child)
      _root = node->get_right_node();
    _root->set_parent_node(ft_nullptr);
    if (node) {
      deallocate_node(node);
      this->_sz--;
    }
  }
  void delete_node_has_no_child(n_pointer node) {
    n_pointer parent = node->get_parent_node();
    if (parent) {
      if (node->is_left_child(node))
        set_relation(parent, ft_nullptr, true);
      else
        set_relation(parent, ft_nullptr, false);
    }
    if (node) {
      deallocate_node(node);
      this->_sz--;
    }
  }
  void delete_node_has_both_child(n_pointer node) {
    n_size_type l_subtree = 0;
    n_size_type r_subtree = 0;
    traversal(node->get_left_node(), l_subtree);
    traversal(node->get_right_node(), r_subtree);
    n_pointer target = successor(node);
    if (l_subtree > r_subtree) target = predecessor(node);
    node->set_value(target->get_value());
    if (target->has_no_child(target))
      delete_node_has_no_child(target);
    else
      delete_node_has_one_child(target, target->has_left_child(target));
    // this->_sz--;
  }
  void set_relation(n_pointer parent, n_pointer child, bool left) {
    if (left)
      parent->set_left_node(child);
    else
      parent->set_right_node(child);
    if (child) child->set_parent_node(parent);
  }
  n_pointer min(n_pointer node) const {
    if (!node) return ft_nullptr;
    if (!node->get_left_node()) {
      return node;
    }
    return min(node->get_left_node());
  }
  n_pointer max(n_pointer node) {
    if (!node) return ft_nullptr;
    if (!node->get_right_node()) {
      return node;
    }
    return max(node->get_right_node());
  }
  n_pointer successor(n_pointer node) {
    n_pointer right = node->get_right_node();
    if (right) return min(right);
    return node;
  }
  n_pointer predecessor(n_pointer node) {
    n_pointer left = node->get_left_node();
    if (left) return max(left);
    return node;
  }
};
_END_NAMESPACE_FT
#endif
