#ifndef CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_LIST_H_
#define CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_LIST_H_

#include <cstddef>
#include <limits>
#include <utility>

#include "iterators/s21_list_iterators.h"
#include "s21_list_node.h"
#include "s21_vector.h"

namespace s21 {

template <typename T>
class list {
  template <typename key_type, typename mapped_type>
  friend class map;

  template <typename key_type>
  friend class set;

 public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using size_type = size_t;
  using pointer = ListNode<T>*;

  list() : end_(new ListNode(value_type())) {}

  explicit list(size_type n) : list() {
    for (size_type i = 0; i < n; i += 1) {
      push_back(value_type());
    }
  }

  list(std::initializer_list<value_type> const& items) : list() {
    for (const auto& i : items) {
      push_back(i);
    }
  }

  list(const list& l) : list() { operator=(l); }

  list(list&& l) : list() { operator=(std::move(l)); }

  ~list() {
    clear();
    delete end_;
  }

  list& operator=(list&& l) {
    if (this != &l) {
      clear();
      first_ = l.first_;
      last_ = l.last_;
      size_ = l.size_;
      end_->previous_ = last_;
      if (last_ != nullptr) last_->next_ = end_;
      l.first_ = nullptr;
      l.last_ = nullptr;
      l.end_->previous_ = nullptr;
      l.size_ = 0;
    }
    return *this;
  }

  list& operator=(const list& l) {
    if (this != &l) {
      clear();
      for (const_iterator it = l.begin(); it != l.end(); ++it) {
        push_back(*it);
      }
    }
    return *this;
  }

  reference front() {
    if (first_ == nullptr) {
      throw "Collection is empty";
    }
    return first_->value_;
  }

  reference back() {
    if (last_ == nullptr) {
      throw "Collection is empty";
    }
    return last_->value_;
  }

  const_reference front() const {
    if (first_ == nullptr) {
      return value_type();
    }
    return first_->value_;
  }

  const_reference back() const {
    if (last_ == nullptr) {
      return value_type();
    }
    return last_->value_;
  }

  iterator begin() {
    if (size_ == 0) return iterator(end_);
    return iterator(first_);
  }

  iterator end() { return iterator(end_); }

  const_iterator begin() const {
    if (size_ == 0) return const_iterator(end_);
    return const_iterator(first_);
  }

  const_iterator end() const { return const_iterator(end_); }

  bool empty() const { return size_ == 0; }

  size_type size() const { return size_; }

  size_type max_size() const noexcept {
    return (std::numeric_limits<size_type>::max() / sizeof(ListNode<T>) / 2);
  }

  void clear() {
    while (!empty()) {
      pop_back();
    }
    first_ = nullptr;
    last_ = nullptr;
    end_->previous_ = nullptr;
  }

  iterator insert(iterator pos, const_reference value) {
    if (size_ + 1 > max_size()) throw "Maximum of container";
    iterator returnIterator = iterator();
    if (pos.node_ == end_) {
      if (last_ == nullptr) {
        last_ = new ListNode<value_type>(value);
        first_ = last_;
        returnIterator = iterator(last_);
      } else {
        last_ = new ListNode<value_type>(value, last_);
        last_->previous_->next_ = last_;
        returnIterator = iterator(last_);
      }
      last_->next_ = end_;
      end_->previous_ = last_;
    } else if (pos.node_->previous_ == nullptr) {
      first_ = new ListNode<value_type>(value, nullptr, first_);
      first_->next_->previous_ = first_;
      returnIterator = iterator(first_);
    } else {
      auto newNode =
          new ListNode<value_type>(value, pos.node_->previous_, pos.node_);
      newNode->previous_->next_ = newNode;
      newNode->next_->previous_ = newNode;
      returnIterator = iterator(newNode);
    }
    size_ += 1;
    return returnIterator;
  }

  void erase(iterator pos) {
    if (size_ != 0 && pos.node_ != nullptr && pos.node_ != end_) {
      if (size_ == 1) {
        first_ = nullptr;
        last_ = nullptr;
        delete end_->previous_;
        end_->previous_ = nullptr;
      } else {
        if (pos.node_ == first_) {
          deleteFirst_();
        } else if (pos.node_ == last_) {
          deleteLast_();
        } else {
          deleteInTheMiddle_(pos.node_);
        }
      }
      size_ -= 1;
    }
  }

  void push_back(const_reference value) { insert(iterator(end_), value); }

  void pop_back() {
    if (!empty()) {
      erase(iterator(last_));
    }
  }

  void push_front(const_reference value) {
    if (empty()) {
      push_back(value);
    } else {
      insert(begin(), value);
    }
  }

  void pop_front() {
    if (!empty()) {
      erase(iterator(first_));
    }
  }

  void swap(list& other) {
    auto temp = std::move(other);
    other = std::move(*this);
    *this = std::move(temp);
  }

  void merge(list& other) {
    if (size_ + other.size_ > max_size()) throw "Maximum of container";
    auto temp = list(size_ + other.size_);
    auto lhsIterator = begin();
    auto rhsIterator = other.begin();
    for (auto newIterator = temp.begin(); newIterator != temp.end();
         ++newIterator) {
      if (lhsIterator != end() && rhsIterator != other.end()) {
        if (*lhsIterator < *rhsIterator) {
          *newIterator = *lhsIterator;
          ++lhsIterator;
        } else {
          *newIterator = *rhsIterator;
          ++rhsIterator;
        }
      } else if (lhsIterator != end()) {
        *newIterator = *lhsIterator;
        ++lhsIterator;
      } else {
        *newIterator = *rhsIterator;
        ++rhsIterator;
      }
    }
    clear();
    other.clear();
    *this = list(std::move(temp));
  }

  void splice(const_iterator pos, list& other) {
    iterator tempIterator = iterator(pos.node_);
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(tempIterator, *it);
    }
    other.clear();
  }

  void reverse() {
    auto leftIterator = begin();
    auto rigthIterator = iterator(last_);
    for (size_type i = 0; i < size_ / 2; i += 1) {
      auto temp = *leftIterator;
      *leftIterator = *rigthIterator;
      *rigthIterator = temp;
      ++leftIterator;
      --rigthIterator;
    }
  }

  void unique() {
    auto it = begin();
    auto actual = *it;
    ++it;
    while (it != end()) {
      if (*it == actual) {
        erase(it);
      } else {
        actual = *it;
      }
      ++it;
    }
  }

  void sort() {
    vector<value_type> nums;
    nums.resize(size_);
    int i = 0;
    for (auto it = begin(); it != end(); ++it) {
      nums[i] = *it;
      i++;
    }
    nums.sort();
    i = 0;
    for (auto it = begin(); it != end(); ++it) {
      *it = nums[i];
      i++;
    }
  }

 private:
  pointer first_ = nullptr;

  pointer last_ = nullptr;

  pointer end_ = nullptr;

  size_type size_ = 0;

  void deleteFirst_() {
    first_ = first_->next_;
    delete first_->previous_;
    first_->previous_ = nullptr;
  }

  void deleteLast_() {
    last_ = last_->previous_;
    delete end_->previous_;
    end_->previous_ = last_;
    last_->next_ = end_;
  }

  void deleteInTheMiddle_(pointer node) {
    auto newPrevious = node->previous_;
    auto newNext = node->next_;
    delete node;
    newPrevious->next_ = newNext;
    newNext->previous_ = newPrevious;
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_LIST_H_