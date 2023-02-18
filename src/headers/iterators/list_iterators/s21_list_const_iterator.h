#ifndef CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_LIST_ITERATORS_S21_LIST_CONST_ITERATOR_H_
#define CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_LIST_ITERATORS_S21_LIST_CONST_ITERATOR_H_

#include "../../s21_list_node.h"
#include "s21_list_iterator.h"

namespace s21 {

template <typename T>
class ListConstIterator {
  friend class list<T>;
  using pointer = ListNode<T>*;

 public:
  ListConstIterator() {}

  ListConstIterator(const ListConstIterator& other) { operator=(other); }

  explicit ListConstIterator(const ListIterator<T>& it) : node_(it.node_) {
    SetCoPointers();
  }

  ListConstIterator& operator=(const ListConstIterator& other) {
    node_ = other.node_;
    SetCoPointers();
    return *this;
  }

  ListConstIterator& operator++() {
    if (next_ != nullptr) {
      node_ = next_;
      SetCoPointers();
    }
    return *this;
  }

  ListConstIterator& operator--() {
    if (next_ == nullptr) {
      SetCoPointers();
    }
    if (previous_ != nullptr) {
      node_ = previous_;
      SetCoPointers();
    }
    return *this;
  }

  const T& operator*() { return node_->value_; }

  const T* operator->() { return &(node_->value_); }

  friend bool operator==(const ListConstIterator& lhs,
                         const ListConstIterator& rhs) {
    return lhs.node_ == rhs.node_;
  }

  friend bool operator!=(const ListConstIterator& lhs,
                         const ListConstIterator& rhs) {
    return !(lhs == rhs);
  }

 protected:
  explicit ListConstIterator(const pointer node) : node_(node) {
    SetCoPointers();
  }

  void SetCoPointers() {
    if (node_ != nullptr) {
      previous_ = node_->previous_;
      next_ = node_->next_;
    }
  }

  pointer node_ = nullptr;

  pointer previous_ = nullptr;

  pointer next_ = nullptr;
};

}  // namespace s21

#endif