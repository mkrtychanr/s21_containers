#ifndef CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_LIST_ITERATORS_S21_LIST_ITERATOR_H_
#define CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_LIST_ITERATORS_S21_LIST_ITERATOR_H_

#include "../../s21_list_node.h"
#include "../s21_map_iterators.h"

namespace s21 {

template <typename T>
class ListIterator {
  friend class list<T>;
  friend class ListConstIterator<T>;

  using pointer = ListNode<T>*;

 public:
  ListIterator() {}

  ListIterator(const ListIterator& other) { operator=(other); }

  ListIterator& operator=(const ListIterator& other) {
    node_ = other.node_;
    SetCoPointers();
    return *this;
  }

  ListIterator& operator++() {
    if (next_ != nullptr) {
      node_ = next_;
      SetCoPointers();
    }
    return *this;
  }

  ListIterator& operator--() {
    if (next_ == nullptr) {
      SetCoPointers();
    }
    if (previous_ != nullptr) {
      node_ = previous_;
      SetCoPointers();
    }
    return *this;
  }

  T& operator*() { return node_->value_; }

  T* operator->() { return &(node_->value_); }

  friend bool operator==(const ListIterator& lhs, const ListIterator& rhs) {
    return lhs.node_ == rhs.node_;
  }

  friend bool operator!=(const ListIterator& lhs, const ListIterator& rhs) {
    return !(lhs == rhs);
  }

 protected:
  explicit ListIterator(const pointer node) : node_(node) { SetCoPointers(); }

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

#endif  // CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_LIST_ITERATORS_S21_LIST_ITERATOR_H_