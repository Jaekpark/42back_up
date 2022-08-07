#ifndef _FT_RB_NODE_HPP
#define _FT_RB_NODE_HPP

#include "../config.hpp"
#include "../utility/nullptr_t.hpp"
// namespace_start
_BEGIN_NAMESPACE_FT

template <class Value>
class rb_node {
 public:
  Value* value;
  Node* parent;
  Node* left;
  Node* right;
  bool is_black;
  bool is_nil;

  Node(Value* val = 0)
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
  // destructor
  ~rb_node(void) {}
  // operator=
  rb_node operator=(const rb_node& x) {
    this->value = x.value;
    this->parent = x.parent;
    this->left = x.left;
    this->right = x.right;
    this->is_black = x.is_black;
    this->is_nil = x.is_nil;
    return *this;
  }
};
// namespace_end
_END_NAMESPACE_FT

#endif