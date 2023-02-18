#ifndef CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_MAP_ITERATORS_S21_SET_CONST_ITERATOR_H_
#define CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_MAP_ITERATORS_S21_SET_CONST_ITERATOR_H_

#include "../../s21_list_node.h"
#include "../s21_list_iterators.h"

namespace s21 {

template <typename T>
class SetConstIterator : ListConstIterator<T> {
  friend class set<T>;

  using pointer = ListNode<T>*;

 public:
  SetConstIterator() {}

  SetConstIterator(const SetConstIterator& other) { operator=(other); }

  SetConstIterator& operator=(const SetConstIterator& other) {
    this->node_ = other.node_;
    this->SetCoPointers();
    return *this;
  }

  SetConstIterator& operator++() {
    if (this->next_ != nullptr) {
      this->node_ = this->next_;
      this->SetCoPointers();
    }
    return *this;
  }

  SetConstIterator& operator--() {
    if (this->next_ == nullptr) {
      this->SetCoPointers();
    }
    if (this->previous_ != nullptr) {
      this->node_ = this->previous_;
      this->SetCoPointers();
    }
    return *this;
  }

  const T& operator*() { return this->node_->value_; }

  const T* operator->() { return &(this->node_->value_); }

  friend bool operator==(const SetConstIterator& lhs,
                         const SetConstIterator& rhs) {
    return lhs.node_ == rhs.node_;
  }

  friend bool operator!=(const SetConstIterator& lhs,
                         const SetConstIterator& rhs) {
    return !(lhs == rhs);
  }

 private:
  explicit SetConstIterator(const pointer node) : ListConstIterator<T>(node) {}

  explicit SetConstIterator(const ListConstIterator<T> it)
      : ListConstIterator<T>(it) {}
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_MAP_ITERATORS_S21_SET_CONST_ITERATOR_H_