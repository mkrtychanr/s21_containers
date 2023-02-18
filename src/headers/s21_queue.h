#ifndef CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_QUEUE_H_

#include <cstddef>
#include <cstdio>
#include <iostream>

#include "s21_list.h"

namespace s21 {

template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  // Member functions
  queue() { data_.clear(); }

  queue(std::initializer_list<value_type> const &items) {
    data_.clear();
    for (const auto &i : items) {
      push(i);
    }
  }

  queue(const queue &q) { operator=(q); }

  queue(queue &&q) { operator=(std::move(q)); }

  ~queue() { data_.clear(); }

  queue &operator=(queue &&q) {
    this->data_ = std::move(q.data_);
    return *this;
  }

  queue &operator=(const queue &q) {
    this->data_ = q.data_;
    return *this;
  }

  // Element access
  const_reference front() { return data_.front(); }
  const_reference back() { return data_.back(); }

  // Capacity
  bool empty() { return data_.empty(); }
  size_type size() { return data_.size(); }

  // Modifiers
  void push(const_reference value) { data_.push_back(value); }
  void pop() { data_.pop_front(); }
  void swap(queue &other) { data_.swap(other.data_); }

 private:
  list<value_type> data_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_QUEUE_H_