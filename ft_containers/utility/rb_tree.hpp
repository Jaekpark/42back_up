#ifndef _FT_RB_TREE_HPP
#define _FT_RB_TREE_HPP

#include <memory>

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

/**
 * RED BLACK TREE
 * 이진 탐색 트리
 * https://t1.daumcdn.net/cfile/tistory/990B3B33598965B71D
 * 레드-블랙 트리
 * https://upload.wikimedia.org/wikipedia/commons/thumb/6/66/Red-black_tree_example.svg/1000px-Red-black_tree_example.svg.png
 *
 * 이진 탐색 트리의 한 종류 -> bst : 스스로 균형을 잡는 트리
 * 트리가 편향되지 않게 함으로써 시간복잡도를 개선한 이진 탐색 트리
 *
 * 특징 : 모든 노드는 레드 혹은 블랙
 *
 * nil node
 * 존재하지 않음을 의미하는 노드
 * 자녀가 없을 대 자녀를 nil 노드로 표기
 * 값이 있는 노드와 동등하게 취급
 * 레드-블랙 트리에서 리프 노드는 nil 노드
 *
 * 속성 1 : 모든 노드는 red or black
 * 속성 2 : root 노드는 반드시 black
 * 속성 3 :모든 nil(leaf) 노드는 black
 * 속성 4 : red의 자녀들은 black = red 노드가 연속적으로 존재할 수 없다.
 * 속성 5 : 임의의 노드에서 자손 nil 노드들까지 가는 경로의 black 수는 같다.
 * (자기 자신 카운트 제외)
 * 		-> 노드 x의 black height : 노드 x에서 임의의 자손 nil 노드까지
 * 내려가는 경로에서의 black 수
 * 		-> 색을 바꾸면서도 속성 5 유지하기 : 레드-블랙 트리가 속성 5를
 * 만족하고 있고 두 자녀가 같은 색을 가질 때 부모와 두 자녀의 색을 바꿔줘도 5번
 * 속승은 여전히 만족한다.
 *
 * 그렇다면 레드-블랙 트리는 어떻게 균형을 잡는가?
 *
 * 레드-블랙 트리는 삽입/삭제 시 주로 속성 4,5를 위반하게 되는데 이를
 * 해결하다보면 자연스럽게 균형이 잡힌다.
 *
 * 레드-블랙 트리의 삽입(insertion)
 * 1. 이진 탐색 트리와 동일하게 노드 삽입
 * 2. 레드-블랙 트리 속성 위반 여부 확인
 * 3. 속성 위반 시 트리 조정
 * 4. 속성 만족
 *
 * 레드-블랙 트리의 삽입 속성
 * 1. 삽입 되는 노드의 색은 항상 red
 *
 * 속성 2 위반
 * - 루트 노드를 black으로 바꾼다.
 * -
 * 속성 4 위반
 * - red 가 한쪽으로 몰려있는경우 red 노드 한 개를 반대편으로 옮긴다.
 * - 이 때 bst 특징 또한 유지하려면 회전을 시켜야 한다.
 * case.3 : 삽입된 레드 노드가 부모의 (왼쪽) 자녀이고, 부모도 레드이고
 * 할아버지의 (왼쪽) 자녀이면서 삼촌(부모의 형제) 노드는 블랙이라면 부모와
 * 할아버지의 색을 바꾼 후 할아버지 노드 기준으로 (오른쪽)으로 회전한다.
 * case.3-1 : 삽입된 레드 노드가 부모의 (오른쪽) 자녀이고, 부모도 레드이고
 * 할어버지의 (오른쪽) 자녀이면서 삼촌 노드는 블랙이라면 부모와 할아버지의 색을
 * 바꾼 후 할아버지 노드 기준으로 (왼쪽) 으로 회전한다. ! case.3 는 할아버지
 * 노드까지 경로가 쭉 뻗어 있는 형태 case 2 : 삽입된 레드 노드가 부모의 (오른쪽)
 * 자녀이고, 부모도 레드이고 할어버지의 (왼쪽) 자녀 이면서 삼촌 노드는
 * 블랙이라면 부모를 기준으로 (왼쪽)으로 회전한 뒤 case.3 방식으로 해결 ! case.2
 * 는 할아버지 노드까지 경로가 꺾인 형태
 *
 * case.1 : 삽입된 레드 노드의 부모도 레드 부모의 형제도 레드라면 부모와 삼촌을
 * 블랙으로 바꾸고 할어버지를 레드로 바꾼 뒤 할아버지 노드에서 다시
 * 확인해야한다.
 *
 */

_BEGIN_NAMESPACE_FT
// namespace_start
template <class T, class Compare = std::less<T>,
          class Alloc = std::allocator<T>, class Node = ft::rb_node<T>,
          class Node_alloc = std::allocator<ft::rb_node<T> > >
class rb_tree {
 public:
  typedef T value_type;
  typedef Compare value_compare;
  typedef Alloc allocator_type;
  // typedef std::allocator<ft::rb_node<T> > node_allocator;
  typedef typename Alloc::template rebind<Node>::other node_allocator;
  typedef std::allocator_traits<node_allocator> node_traits;
  typedef typename node_allocator::pointer node_pointer;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename allocator_type::size_type size_type;
  typedef tree_iterator<T> iterator;
  typedef tree_const_iterator<T> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

 private:
  allocator_type _alloc;
  node_allocator _node_alloc;
  value_compare _compare;
  node_pointer _nil;
  node_pointer _past_last;
  node_pointer _root;
  size_type _size;

  node_pointer __min(node_pointer n) const {
    while (n != NULL && !is_nil(n->left)) n = n->left;
    return n;
  }

  node_pointer __max(node_pointer n) const {
    while (n != NULL && !is_nil(n->right)) n = n->right;
    return n;
  }

  void __rb_rotate_r(node_pointer node) {
    node_pointer tmp;
    tmp = node->left;
    node->left = tmp->right;
    if (!is_nil(tmp->right)) tmp->right->parent = node;
    tmp->parent = node->parent;
    if (node->parent == NULL)
      _root = tmp;
    else if (node == node->parent->left)
      node->parent->left = tmp;
    else
      node->parent->right = tmp;
    tmp->right = node;
    node->parent = tmp;
  }
  void __rb_rotate_l(node_pointer node) {
    node_pointer tmp;
    tmp = node->right;
    node->right = tmp->left;
    if (!is_nil(tmp->left)) tmp->left->parent = node;
    tmp->parent = node->parent;
    if (node->parent == NULL)
      _root = tmp;
    else if (node == node->parent->left)
      node->parent->left = tmp;
    else
      node->parent->right = tmp;
    tmp->left = node;
    node->parent = tmp;
  }
  node_pointer __ins(node_pointer new_n) {
    if (_root == _past_last)
      _root = new_n;
    else
      __ins_to_node(_root, new_n);
    return new_n;
  }

  node_pointer __ins_to_node(node_pointer root, node_pointer new_n) {
    if (_compare(*new_n->value, *root->value)) {
      if (!is_nil(root->left)) return (__ins_to_node(root->left, new_n));
      root->left = new_n;
    } else {
      if (!is_nil(root->right)) return (__ins_to_node(root->right, new_n));
      root->right = new_n;
    }
    new_n->parent = root;
    return (new_n);
  }

  node_pointer __ins_node_in_tree(node_pointer new_n, node_pointer to) {
    if (_root == _past_last)
      _root = new_n;
    else
      __ins_to_node(to, new_n);
    return (new_n);
  }

  void __ins_fixup(node_pointer node) {
    if (node != _root && node->parent != _root) {
      while (node != _root && !node->parent->is_black) {
        if (node->parent == node->parent->parent->left) {
          node_pointer uncle = node->parent->parent->right;
          if (!uncle->is_black) {
            node->parent->is_black = true;
            uncle->is_black = true;
            node->parent->parent->is_black = false;
            node = node->parent->parent;
          } else {
            if (node == node->parent->right) {
              node = node->parent;
              __rb_rotate_l(node);
            }
            node->parent->is_black = true;
            node->parent->parent->is_black = false;
            __rb_rotate_r(node->parent->parent);
          }
        } else {
          node_pointer uncle = node->parent->parent->left;
          if (!uncle->is_black) {
            node->parent->is_black = true;
            uncle->is_black = true;
            node->parent->parent->is_black = false;
            node = node->parent->parent;
          } else {
            if (node == node->parent->left) {
              node = node->parent;
              __rb_rotate_r(node);
            }
            node->parent->is_black = true;
            node->parent->parent->is_black = false;
            __rb_rotate_l(node->parent->parent);
          }
        }
      }
    }
    _root->is_black = true;
  }

  bool is_nil(node_pointer node) const {
    return node == _nil || node == _past_last;
  }

  void clear_node(node_pointer node) {
    if (node && !is_nil(node)) {
      clear_node(node->right);
      clear_node(node->left);
      _alloc.destroy(node->value);
      _alloc.deallocate(node->value, 1);
      _node_alloc.deallocate(node, 1);
    }
  }

  void init_rb_tree() {
    _nil = _node_alloc.allocate(1);
    _node_alloc.construct(_nil, rb_node<T>());
    _nil->is_black = true;
    _nil->is_nil = true;
    _past_last = _node_alloc.allocate(1);
    _node_alloc.construct(_past_last, rb_node<T>());
    _past_last->value = _alloc.allocate(1);
    _alloc.construct(_past_last->value, T());
    _past_last->is_black = true;
  }
  void transplant(node_pointer to, node_pointer from) {
    if (to == _root)
      _root = from;
    else if (to == to->parent->left)
      to->parent->left = from;
    else
      to->parent->right = from;
    from->parent = to->parent;
  }

  void free_node(node_pointer node) {
    _alloc.destroy(node->value);
    _alloc.deallocate(node->value, 1);
    _node_alloc.deallocate(node, 1);
  }

 public:
  iterator end() { return (iterator(_past_last)); }

  const_iterator end() const { return (const_iterator(_past_last)); }

  iterator begin() {
    return (iterator(_size == 0 ? _past_last : iterator(__min(_root))));
  }
  const_iterator begin() const {
    return (
        const_iterator(_size == 0 ? _past_last : const_iterator(__min(_root))));
  }

  reverse_iterator rbegin() { return (reverse_iterator(end())); }
  const_reverse_iterator rbegin() const {
    return (const_reverse_iterator(end()));
  }

  reverse_iterator rend() { return (reverse_iterator(begin())); }

  const_reverse_iterator rend() const {
    return (const_reverse_iterator(begin()));
  }

  pointer create_value(const value_type &value) {
    pointer new_val = _alloc.allocate(1);
    _alloc.construct(new_val, value);
    return new_val;
  }
  node_pointer copy_node(node_pointer other) {
    node_pointer new_n = _node_alloc.allocate(1);
    _node_alloc.construct(new_n, rb_node<T>());
    new_n->is_black = other->is_black;
    new_n->is_nil = other->is_nil;
    if (other->value) {
      new_n->value = _alloc.allocate(1);
      _alloc.construct(new_n->value, *other->value);
    }
    return (new_n);
  }

  void copy_child(node_pointer my_node, node_pointer other) {
    if (other->left->is_nil)
      my_node->left = _nil;
    else {
      my_node->left = copy_node(other->left);
      my_node->left->parent = my_node;
      copy_child(my_node->left, other->left);
    }
    if (other->right->is_nil)
      my_node->right = _nil;
    else if (other->right->right == NULL) {
      my_node->right = _past_last;
      _past_last->parent = my_node;
    } else {
      my_node->right = copy_node(other->right);
      my_node->right->parent = my_node;
      copy_child(my_node->right, other->right);
    }
  }

  node_pointer find_node(const value_type &value, node_pointer node) const {
    if (!node || is_nil(node)) return NULL;
    if (_compare(value, *node->value)) return find_node(value, node->left);
    if (_compare(*node->value, value)) return find_node(value, node->right);
    return node;
  }

  iterator find(const value_type &value) {
    node_pointer exist = find_node(value, _root);
    return (exist == NULL ? end() : iterator(exist));
  }

  const_iterator find(const value_type &value) const {
    node_pointer exist = find_node(value, _root);
    return (exist == NULL ? end() : const_iterator(exist));
  }

  ft::pair<iterator, bool> insert(value_type const &value) {
    node_pointer exist = find_node(value, _root);
    if (exist) return ft::pair<iterator, bool>(iterator(exist), false);
    node_pointer new_n = _node_alloc.allocate(1);
    _node_alloc.construct(new_n, rb_node<value_type>(create_value(value)));
    new_n->left = _nil;
    new_n->right = _nil;
    __ins_node_in_tree(new_n, _root);
    ft::pair<iterator, bool> res(iterator(new_n), true);
    __ins_fixup(new_n);
    _size++;
    new_n = __max(_root);
    new_n->right = _past_last;
    _past_last->parent = new_n;
    return res;
  }

  iterator insert(iterator position, const value_type &value) {
    node_pointer new_n = find_node(value, _root);
    if (new_n) return (iterator(new_n));
    new_n = _node_alloc.allocate(1);
    _node_alloc.construct(new_n, rb_node<value_type>(create_value(value)));
    new_n->left = _nil;
    new_n->right = _nil;
    if (position == begin()) {
      if (position != end() && _compare(value, *position))
        __ins_node_in_tree(new_n, __min(_root));
      else
        __ins_node_in_tree(new_n, _root);
    } else if (position == end()) {
      if (position != begin() && _compare(*(--position), value))
        __ins_node_in_tree(new_n, _past_last->parent);
      else
        __ins_node_in_tree(new_n, _root);
    } else
      __ins_node_in_tree(new_n, _root);
    __ins_fixup(new_n);
    _size++;
    node_pointer max_of_tree = __max(_root);
    max_of_tree->right = _past_last;
    _past_last->parent = max_of_tree;
    return (iterator(new_n));
  }

  template <class InputIt>
  void insert(typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                     InputIt>::type first,
              InputIt last) {
    for (; first != last; ++first) insert(*first);
  }

  void erase(iterator position) {
    node_pointer tmp = position.node(), backup, target = tmp;
    bool rb_flag = tmp->is_black;
    if (is_nil(tmp->left)) {
      backup = tmp->right;
      transplant(tmp, tmp->right);
    } else if (is_nil(tmp->right)) {
      backup = tmp->left;
      transplant(tmp, tmp->left);
    } else {
      node_pointer tmp1 = tmp;
      tmp = __min(tmp1->right);
      rb_flag = tmp->is_black;
      backup = tmp->right;
      if (tmp->parent != tmp1) {
        transplant(tmp, tmp->right);
        tmp->right = tmp1->right;
        tmp1->right->parent = tmp;
      }
      transplant(tmp1, tmp);
      tmp->left = tmp1->left;
      tmp->left->parent = tmp;
      tmp->is_black = tmp1->is_black;
    }
    free_node(target);
    if (rb_flag) erase_fixup(backup);
    _size--;
    _nil->parent = NULL;
    if (_size == 0)
      _root = _past_last;
    else {
      if (_size != 1)
        backup = __max(_root);
      else
        backup = _root;
      backup->right = _past_last;
      _past_last->parent = backup;
    }
  }

  size_type erase(const value_type &value) {
    node_pointer res = find_node(value, _root);
    if (res) erase(iterator(res));
    return (res != NULL);
  }

  void erase(iterator first, iterator last) {
    while (first != last) erase(first++);
  }

  void erase_fixup(node_pointer x) {
    node_pointer brother;
    while (x != _root && x->is_black) {
      if (x == x->parent->left) {
        brother = x->parent->right;
        if (!brother->is_black) {
          brother->is_black = true;
          x->parent->is_black = false;
          __rb_rotate_l(x->parent);
          brother = x->parent->right;
        }
        if (brother->left->is_black && brother->right->is_black) {
          brother->is_black = false;
          x = x->parent;
        } else {
          // case 3
          if (brother->right->is_black) {
            brother->left->is_black = true;
            brother->is_black = false;
            __rb_rotate_r(brother);
            brother = x->parent->right;
          }
          // case 4
          brother->is_black = x->parent->is_black;
          x->parent->is_black = true;
          brother->right->is_black = true;
          __rb_rotate_l(x->parent);
          x = _root;
        }
      } else {
        brother = x->parent->left;
        if (!brother->is_black) {
          brother->is_black = true;
          x->parent->is_black = false;
          __rb_rotate_r(x->parent);
          brother = x->parent->left;
        }
        if (brother->right->is_black && brother->left->is_black) {
          brother->is_black = false;
          x = x->parent;
        } else {
          if (brother->left->is_black) {
            brother->right->is_black = true;
            brother->is_black = false;
            __rb_rotate_l(brother);
            brother = x->parent->left;
          }
          brother->is_black = x->parent->is_black;
          x->parent->is_black = true;
          brother->left->is_black = true;
          __rb_rotate_r(x->parent);
          x = _root;
        }
      }
    }
  }
  rb_tree(const Compare &comp, const allocator_type &a = allocator_type())
      : _alloc(a),
        _node_alloc(node_allocator()),
        _compare(comp),
        _root(0),
        _size(0) {
    init_rb_tree();
    _root = _past_last;
  }

  rb_tree()
      : _root(0),
        _alloc(allocator_type()),
        _node_alloc(node_allocator()),
        _compare(value_compare()),
        _size(0) {
    init_rb_tree();
    _root = _past_last;
  }

  rb_tree(const rb_tree &src) : _compare(src._compare), _root(NULL) {
    *this = src;
  }
  template <class InputIt>
  rb_tree(typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                 InputIt>::type first,
          InputIt last, const value_compare &comp,
          const allocator_type &alloc = allocator_type())
      : _alloc(alloc), _node_alloc(node_allocator()), _compare(comp) {
    init_rb_tree();
    _root = _past_last;
    for (; first != last; ++first) insert(*first);
  }

  rb_tree &operator=(const rb_tree &src) {
    if (this == &src) return *this;
    this->_node_alloc = src._node_alloc;
    this->_alloc = src._alloc;
    this->_compare = src._compare;
    if (this->_root == NULL)
      init_rb_tree();
    else
      clear_node(_root);
    if (src._size == 0)
      this->_root = this->_past_last;
    else {
      this->_root = copy_node(src._root);
      copy_child(this->_root, src._root);
    }
    this->_size = src._size;
    return *this;
  }

  ~rb_tree() {
    clear_node(_root);
    _alloc.destroy(_past_last->value);
    _alloc.deallocate(_past_last->value, 1);
    _node_alloc.deallocate(_nil, 1);
    _node_alloc.deallocate(_past_last, 1);
  }

  size_type size() const { return (_size); }

  size_type max_size() const {
    return std::min<size_type>(std::numeric_limits<difference_type>::max(),
                               node_traits::max_size(node_allocator()));
  }

  bool empty() const { return (_size == 0); }

  value_compare value_comp() const { return (_compare); }

  void clear() {
    clear_node(_root);
    _root = _past_last;
    _past_last->parent = NULL;
    _size = 0;
  }

  size_type count(const value_type &value) const {
    return (find(value) != end());
  }

  iterator lower_bound(const value_type &value) {
    iterator last = end();
    for (iterator first = begin(); first != last; ++first) {
      if (!_compare(*first, value)) return (first);
    }
    return (last);
  }

  const_iterator lower_bound(const value_type &value) const {
    const_iterator last = end();
    for (const_iterator first = begin(); first != last; ++first) {
      if (!_compare(*first, value)) return (first);
    }
    return (last);
  }

  iterator upper_bound(const value_type &value) {
    iterator begin = this->begin();
    iterator end = this->end();
    while (begin != end) {
      if (_compare(value, *begin)) break;
      begin++;
    }
    return begin;
  }

  const_iterator upper_bound(const value_type &value) const {
    return const_iterator(this->upper_bound(value));
  }

  void swap(rb_tree &other) {
    std::swap(this->_alloc, other._alloc);
    std::swap(this->_node_alloc, other._node_alloc);
    std::swap(this->_compare, other._compare);
    std::swap(this->_root, other._root);
    std::swap(this->_nil, other._nil);
    std::swap(this->_past_last, other._past_last);
    std::swap(this->_size, other._size);
  }

  ft::pair<iterator, iterator> equal_range(const value_type &value) {
    return (ft::make_pair(lower_bound(value), upper_bound(value)));
  }

  allocator_type get_allocator() const { return (_alloc); }
};

template <class T, class Compare, class Alloc, class Node, class Node_alloc>
bool operator==(const rb_tree<T, Compare, Alloc, Node, Node_alloc> &lhs,
                const rb_tree<T, Compare, Alloc, Node, Node_alloc> &rhs) {
  if (lhs.size() != rhs.size()) return (lhs.size() == rhs.size());
  return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Compare, class Alloc, class Node, class Node_alloc>
bool operator!=(const rb_tree<T, Compare, Alloc, Node, Node_alloc> &lhs,
                const rb_tree<T, Compare, Alloc, Node, Node_alloc> &rhs) {
  return (!(lhs == rhs));
}

template <class T, class Compare, class Alloc, class Node, class Node_alloc>
bool operator<(const rb_tree<T, Compare, Alloc, Node, Node_alloc> &lhs,
               const rb_tree<T, Compare, Alloc, Node, Node_alloc> &rhs) {
  return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                      rhs.end()));
}

template <class T, class Compare, class Alloc, class Node, class Node_alloc>
bool operator>(const rb_tree<T, Compare, Alloc, Node, Node_alloc> &lhs,
               const rb_tree<T, Compare, Alloc, Node, Node_alloc> &rhs) {
  return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(),
                                      lhs.end()));
}

template <class T, class Compare, class Alloc, class Node, class Node_alloc>
bool operator>=(const rb_tree<T, Compare, Alloc, Node, Node_alloc> &lhs,
                const rb_tree<T, Compare, Alloc, Node, Node_alloc> &rhs) {
  if (lhs > rhs || lhs == rhs) return (true);
  return (false);
}

template <class T, class Compare, class Alloc, class Node, class Node_alloc>
bool operator<=(const rb_tree<T, Compare, Alloc, Node, Node_alloc> &lhs,
                const rb_tree<T, Compare, Alloc, Node, Node_alloc> &rhs) {
  if (lhs < rhs || lhs == rhs) return (true);
  return (false);
}

template <class T, class Compare, class Alloc, class Node, class Node_alloc>
void swap(rb_tree<T, Compare, Alloc, Node, Node_alloc> &lhs,
          rb_tree<T, Compare, Alloc, Node, Node_alloc> &rhs) {
  lhs.swap(rhs);
}

_END_NAMESPACE_FT

#endif