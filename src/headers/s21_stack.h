#ifndef CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_STACK_H_
#define CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_STACK_H_

#include <cstddef>
#include <cstdio>
#include <iostream>

#include "s21_list.h"

namespace s21 {

template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  // Member functions
  stack() { data_.clear(); }

  stack(std::initializer_list<value_type> const &items) {
    data_.clear();
    for (const auto &i : items) {
      push(i);
    }
  }

  stack(const stack &s) { operator=(s); }

  stack(stack &&s) { operator=(std::move(s)); }

  ~stack() { data_.clear(); }

  stack &operator=(stack &&s) {
    this->data_ = std::move(s.data_);
    return *this;
  }

  stack &operator=(const stack &s) {
    this->data_ = s.data_;
    return *this;
  }

  // Element access
  const_reference top() { return data_.front(); }

  // Capacity
  bool empty() { return data_.empty(); }
  size_type size() { return data_.size(); }

  // Modifiers
  void push(const_reference value) { data_.push_front(value); }
  void pop() { data_.pop_front(); }
  void swap(stack &other) { data_.swap(other.data_); }

 private:
  list<value_type> data_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_STACK_H_