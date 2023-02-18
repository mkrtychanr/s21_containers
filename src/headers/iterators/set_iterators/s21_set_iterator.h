#ifndef CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_MAP_ITERATORS_S21_SET_ITERATOR_H_
#define CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_MAP_ITERATORS_S21_SET_ITERATOR_H_

#include "../../s21_list_node.h"
#include "../s21_list_iterators.h"

namespace s21 {

template <typename T>
class SetIterator : ListIterator<T> {
  friend class set<T>;

  using pointer = ListNode<T>*;

 public:
  SetIterator() {}

  SetIterator(const SetIterator& other) : SetIterator() { operator=(other); }

  SetIterator& operator=(const SetIterator& other) {
    this->node_ = other.node_;
    this->SetCoPointers();
    return *this;
  }

  SetIterator& operator++() {
    if (this->next_ != nullptr) {
      this->node_ = this->next_;
      this->SetCoPointers();
    }
    return *this;
  }

  SetIterator& operator--() {
    if (this->next_ == nullptr) {
      this->SetCoPointers();
    }
    if (this->previous_ != nullptr) {
      this->node_ = this->previous_;
      this->SetCoPointers();
    }
    return *this;
  }

  T& operator*() { return this->node_->value_; }

  T* operator->() { return &(this->node_->value_); }

  friend bool operator==(const SetIterator& lhs, const SetIterator& rhs) {
    return lhs.node_ == rhs.node_;
  }

  friend bool operator!=(const SetIterator& lhs, const SetIterator& rhs) {
    return !(lhs == rhs);
  }

 private:
  explicit SetIterator(const pointer node) : ListIterator<T>(node) {}

  explicit SetIterator(const ListIterator<T> it) : ListIterator<T>(it) {}
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_MAP_ITERATORS_S21_SET_ITERATOR_H_