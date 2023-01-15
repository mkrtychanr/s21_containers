#ifndef CPP2_S21_CONTAINERS_SRC_HEADERS_S21_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_HEADERS_S21_LIST_H_

#include <cstddef>
#include <cstdio>
#include <iostream>



namespace s21 {

template <typename T>
class list {
 private:
  struct ListNode;

 public:
  class ListIterator;
  class ListConstIterator;

  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;
  using pointer = ListNode*;

  class ListIterator {
    friend class list;
    friend class ListConstIterator;
   public:
    ListIterator() {}

    ListIterator(const iterator& other) { operator=(other); }

    iterator& operator=(const iterator& other) {
      node_ = other.node_;
      SetCoPointers();
      return *this;
    }
    
    iterator& operator++() { 
      node_ = next_;
      SetCoPointers();
      return *this;
    }

    iterator& operator--() {
      node_ = previous_;
      SetCoPointers();
      return *this;
    }

    reference operator*() { return node_ -> value_; }

    friend bool operator==(const iterator& lhs, const iterator& rhs) {
      return lhs.node_ == rhs.node_;
    }

    friend bool operator!=(const iterator& lhs, const iterator& rhs) {
      return !(lhs == rhs);
    }

   private:

    ListIterator(const pointer node) : node_(node) { SetCoPointers(); }

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

  class ListConstIterator {
    friend class list;
   public:
    ListConstIterator() {}

    ListConstIterator(const const_iterator& other) { operator=(other); }

    ListConstIterator(const iterator& it) : node_(it.node_) { SetCoPointers(); }

    const_iterator& operator=(const const_iterator& other) {
      node_ = other.node_;
      SetCoPointers();
      return *this;
    }
    
    const_iterator& operator++() { 
      node_ = next_;
      SetCoPointers();
      return *this;
    }

    const_iterator& operator--() {
      node_ = previous_;
      SetCoPointers();
      return *this;
    }

    const_reference operator*() { return node_ -> value_; }

    friend bool operator==(const const_iterator& lhs, const const_iterator& rhs) {
      return lhs.node_ == rhs.node_;
    }

    friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs) {
      return !(lhs == rhs);
    }

   private:

    ListConstIterator(const pointer node) : node_(node) { SetCoPointers(); }

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

  list() {
    clear();
  }

  list(size_type n) {
    list();
    for (size_type i = 0; i < n; i++) {
      push_back(value_type());
    }
  }

  list(std::initializer_list<value_type> const &items) {
    clear();
    for (auto& i : items) {
      push_back(i);
    }
  }

  list(const list& l) {
    operator=(l);
  }

  list(list&& l) {
    operator=(std::move(l));
  }

  ~list() {
    clear();
  }

  list& operator=(list &&l) {
    if (this != &l) {
      this -> first_ = l.first_;
      this -> last_ = l.last_;
      this -> size_ = l.size_;
      l.first_ = nullptr;
      l.last_ = nullptr;
      l.size_ = 0;
    }
    return *this;
  }

  list& operator=(const list& l) {
    clear();
    for (const_iterator it = l.begin(); it != l.end(); ++it) {
      push_back(*it);
    }
    return *this;
  }

  reference front() {
    if (first_ == nullptr) {
      push_back(0);
      return front();
    }
    return first_->value_;
  }

  reference back() {
    if (last_ == nullptr) {
      push_back(0);
      return back();
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
    return iterator(first_);
  }

  iterator end() {
    return iterator(nullptr);
  }

  const_iterator begin() const {
    return const_iterator(first_);
  }

  const_iterator end() const {
    return const_iterator(nullptr);
  }

  bool empty() const { return size_ == 0; }

  size_type size() const { return size_; }

  // надо доделать, работает 100 процентов не так,
  // возможно, что нужно высчитывать максимальное значение в памяти,
  // а не просто максимум size_type
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
  }

  void clear() {
    while (!empty()) {
      pop_back();
    }
    first_ = nullptr;
    last_ = nullptr;
  }

  iterator insert(iterator pos, const_reference value) {
    if (size_ + 1 > max_size()) throw "Maximum of container";
    iterator returnIterator = iterator();
    if (pos.node_ == nullptr) {
      if (last_ == nullptr) {
        last_ = new ListNode(value);
        first_ = last_;
        returnIterator = iterator(last_);
      } else {
        last_ = new ListNode(value, last_);
        last_->previous_->next_ = last_;
        returnIterator = iterator(last_);
      }
    } else if (pos.node_->previous_ == nullptr) {
      first_ = new ListNode(value, nullptr, first_);
      first_->next_->previous_ = first_;
      returnIterator = iterator(first_); 
    } else {
      auto newNode = new ListNode(value, pos.node_->previous_, pos.node_);
      newNode->previous_->next_ = newNode;
      newNode->next_->previous_ = newNode;
      returnIterator = iterator(newNode);
    }
    size_++;
    return returnIterator;
  }

  void erase(iterator pos) {
    if (pos.node_ != nullptr) {
      auto newNextForPrevious = pos.node_ -> next_;
      auto newPreviousForNext = pos.node_ -> previous_;
      if (pos.node_ -> previous_ != nullptr) {
        pos.node_ -> previous_ -> next_ = newNextForPrevious;
      } else {
        first_ = newNextForPrevious;
      }
      if (pos.node_ -> next_ != nullptr) {
        pos.node_ -> next_ -> previous_ = newPreviousForNext;
      } else {
        last_ = newPreviousForNext;
      }
      delete pos.node_;
      size_--;
    }
  }

  void push_back(const_reference value) {
    insert(end(), value);
  }

  void pop_back() {
    if (!empty()) {
      erase(iterator(last_));
    }
  }

  void push_front(const_reference value) {
    insert(begin(), value);
  }

  void pop_front() {
    if (!empty()) {
      erase(first_);
    }
  }

  void swap(list& other) {
    auto temp = list(std::move(other));
    other = *this;
    *this = list(std::move(temp));
  }

  void merge(list& other) {
    if (size_ + other.size_ > max_size()) throw "Maximum of container";
    auto temp = list(size_ + other.size_);
    auto lhsIterator = begin();
    auto rhsIterator = other.begin();
    for (auto newIterator = temp.begin(); newIterator != temp.end(); ++newIterator) {
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
    for (size_type i = 0; i < size_/2; i++) {
      auto temp = *leftIterator;
      *leftIterator = *rigthIterator;
      *rigthIterator = temp;
      ++leftIterator;
      --rigthIterator;
    }
  }

  //дописать когда будет готов set
  void unique();
  
  //дописать когда будет готов vector
  void sort();

private:

  pointer first_ = nullptr;

  pointer last_ = nullptr;

  size_type size_ = 0;

  struct ListNode {
    value_type value_ = value_type();
    ListNode* previous_ = nullptr;
    ListNode* next_ = nullptr;
    ListNode(value_type value = value_type(), ListNode* previous = nullptr, ListNode* next = nullptr) : value_(value), previous_(previous), next_(next) {}
  };
};
}

#endif  // CPP2_S21_CONTAINERS_SRC_HEADERS_S21_LIST_H_