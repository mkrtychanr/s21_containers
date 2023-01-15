#ifndef CPP2_S21_CONTAINERS_SRC_HEADERS_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_SRC_HEADERS_S21_QUEUE_H_

#include <cstddef>
#include <cstdio>
#include <iostream>

namespace s21 {

template <typename T>
class queue {
 private:
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  // Member functions
  queue() {}
  queue(std::initializer_list<value_type> const &items) {}
  queue(const queue &q) {}
  queue(queue &&q) {}
  ~queue() {}
  operator=(queue &&q) {}

  // Element access
  const_reference front() {}
  const_reference back() {}

  // Capacity
  bool empty() {}
  size_type size() {}

  // Modifiers
  void push(const_reference value) {}
  void pop() {}
  void swap(queue &other) {}
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_HEADERS_S21_QUEUE_H_