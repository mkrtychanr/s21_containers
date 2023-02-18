#ifndef CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_MAP_ITERATORS_S21_MAP_CONST_ITERATOR_H_
#define CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_MAP_ITERATORS_S21_MAP_CONST_ITERATOR_H_

#include "../../s21_list_node.h"
#include "../s21_list_iterators.h"

namespace s21 {

template <typename Key, typename T>
class MapConstIterator : ListConstIterator<std::pair<const Key, T>> {
  friend class map<Key, T>;

  using pointer = ListNode<std::pair<const Key, T>>*;

 public:
  MapConstIterator() {}

  MapConstIterator(const MapConstIterator& other) { operator=(other); }

  MapConstIterator& operator=(const MapConstIterator& other) {
    this->node_ = other.node_;
    this->SetCoPointers();
    return *this;
  }

  MapConstIterator& operator++() {
    if (this->next_ != nullptr) {
      this->node_ = this->next_;
      this->SetCoPointers();
    }
    return *this;
  }

  MapConstIterator& operator--() {
    if (this->next_ == nullptr) {
      this->SetCoPointers();
    }
    if (this->previous_ != nullptr) {
      this->node_ = this->previous_;
      this->SetCoPointers();
    }
    return *this;
  }

  const std::pair<const Key, T>& operator*() { return this->node_->value_; }

  const std::pair<const Key, T>* operator->() { return &(this->node_->value_); }

  friend bool operator==(const MapConstIterator& lhs,
                         const MapConstIterator& rhs) {
    return lhs.node_ == rhs.node_;
  }

  friend bool operator!=(const MapConstIterator& lhs,
                         const MapConstIterator& rhs) {
    return !(lhs == rhs);
  }

 private:
  explicit MapConstIterator(const pointer node)
      : ListConstIterator<std::pair<const Key, T>>(node) {}

  explicit MapConstIterator(const ListConstIterator<std::pair<const Key, T>> it)
      : ListConstIterator<std::pair<const Key, T>>(it) {}
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_0_SRC_HEADERS_ITERATORS_MAP_ITERATORS_S21_MAP_CONST_ITERATOR_H_