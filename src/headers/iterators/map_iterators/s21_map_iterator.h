#ifndef CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_MAP_ITERATORS_S21_MAP_ITERATOR_H_
#define CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_MAP_ITERATORS_S21_MAP_ITERATOR_H_

#include "../../s21_list_node.h"
#include "../s21_list_iterators.h"

namespace s21 {

template <typename Key, typename T>
class MapIterator : ListIterator<std::pair<const Key, T>> {
  friend class map<Key, T>;

  using pointer = ListNode<std::pair<const Key, T>>*;

 public:
  MapIterator() {}

  MapIterator(const MapIterator& other) : MapIterator() { operator=(other); }

  MapIterator& operator=(const MapIterator& other) {
    this->node_ = other.node_;
    this->SetCoPointers();
    return *this;
  }

  MapIterator& operator++() {
    if (this->next_ != nullptr) {
      this->node_ = this->next_;
      this->SetCoPointers();
    }
    return *this;
  }

  MapIterator& operator--() {
    if (this->next_ == nullptr) {
      this->SetCoPointers();
    }
    if (this->previous_ != nullptr) {
      this->node_ = this->previous_;
      this->SetCoPointers();
    }
    return *this;
  }

  std::pair<const Key, T>& operator*() { return this->node_->value_; }

  std::pair<const Key, T>* operator->() { return &(this->node_->value_); }

  friend bool operator==(const MapIterator& lhs, const MapIterator& rhs) {
    return lhs.node_ == rhs.node_;
  }

  friend bool operator!=(const MapIterator& lhs, const MapIterator& rhs) {
    return !(lhs == rhs);
  }

 private:
  explicit MapIterator(const pointer node)
      : ListIterator<std::pair<const Key, T>>(node) {}

  explicit MapIterator(const ListIterator<std::pair<const Key, T>> it)
      : ListIterator<std::pair<const Key, T>>(it) {}
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_MAP_ITERATORS_S21_MAP_ITERATOR_H_