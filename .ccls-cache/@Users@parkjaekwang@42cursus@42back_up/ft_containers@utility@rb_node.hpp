#ifndef _FT_RB_NODE_HPP
#define _FT_RB_NODE_HPP

#include "../config.hpp"
#include "../utility/nullptr_t.hpp"

// namespace_start
_BEGIN_NAMESPACE_FT

template <class T>
class rb_node {
 public:
  typedef rb_node* node_pointer;
  typedef rb_node& node_reference;

  T* value;
  rb_node* parent;
  rb_node* left;
  rb_node* right;
  bool is_black;
  bool is_nil;

  rb_node(T* val = 0)
      : value(val),
        parent(ft_nullptr),
        left(ft_nullptr),
        right(ft_nullptr),
        is_black(false),
        is_nil(false) {}

  // copy_constructor
  rb_node(const rb_node& x) {
    this->value = x.value;
    this->parent = x.parent;
    this->left = x.left;
    this->right = x.right;
    this->is_black = x.is_black;
    this->is_nil = x.is_nil;
  }
  // operator=
  rb_node& operator=(const rb_node& x) {
    this->value = x.value;
    this->parent = x.parent;
    this->left = x.left;
    this->right = x.right;
    this->is_black = x.is_black;
    this->is_nil = x.is_nil;
    return *this;
  }
  // destructor
  ~rb_node(void) {}
};
// namespace_end
_END_NAMESPACE_FT

#endif