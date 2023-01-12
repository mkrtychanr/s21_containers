#ifndef CPP2_S21_CONTAINERS_SRC_S21_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_S21_LIST_H_

#include <cstddef>
#include <cstdio>
#include <iostream>

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
  using const_iterator =  const ListConstIterator;
  using size_type = size_t;
  using pointer = ListNode*;

  class ListIterator {
    friend class list;
   public:
    ListIterator() : node_(ListNode()) {}

    ListIterator(const iterator& other) { operator=(other); }

    iterator& operator=(const iterator& other) {
      node_ = other.node_;
      return *this;
    }
    
    iterator& operator++() { 
      node_ = node_ -> next_;
      return *this;
    }

    iterator& operator--() {
      node_ = node_ -> previous_;
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

    ListIterator(const pointer node) : node_(node) {}

    pointer node_;
  };

  class ListConstIterator {
    friend class list;
   public:
    ListConstIterator() : node_(ListNode()) {}

    ListConstIterator(const_iterator& other) { operator=(other); }

    const_iterator& operator=(const_iterator& other) {
      node_ = other.node_;
      return *this;
    }
    
    const_iterator& operator++() { 
      node_ = node_ -> next_;
      return *this;
    }

    const_iterator& operator--() {
      node_ = node_ -> previous_;
      return *this;
    }

    const_reference operator*() const { return node_ -> value_; }

    friend bool operator==(const_iterator& lhs, const_iterator& rhs) {
      return lhs.node_ == rhs.node_;
    }

    friend bool operator!=(const_iterator& lhs, const_iterator& rhs) {
      return !(lhs == rhs);
    }

   private:

    ListConstIterator(const pointer node) : node_(node) {}

    pointer node_;
  };

  list() {
    clear();
    first_ = nullptr;
    last_ = nullptr;
    size_ = 0;
  }

  list(size_type n) {
    list();
    for (size_type i = 0; i < n; i++) {
      push_back(value_type());
    }
  }

  // list(std::initalizer_list<value_type> const &items);

  list(const list& l) {
    operator=(l);
  }

  list(list&& l) {
    operator=(l);
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
    for (auto it = l.begin(); it != l.end(); ++it) {
      push_back(*it);
    }
    return *this;
  }

  const_reference front() const {
    if (first_ == nullptr) {
      return value_type();
    }
    return *first_;
  }

  const_reference back() const {
    if (last_ == nullptr) {
      return value_type();
    }
    return *last_;
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
    return const_iterator(last_);
  }

  bool empty() const { return size_ == 0; }

  size_type size() const { return size_; }

  size_type max_size() const;

  void clear() {
    while (!empty()) {
      pop_back();
    }
  }

  iterator insert(iterator pos, const_reference value);

  void erase(iterator pos) {
    if (pos.node_ != nullptr) {
      auto newNextForPrevious = pos.node_ -> next_;
      auto newPreviousForNext = pos.node_ -> previous_;
      if (pos.node_ -> previous_ != nullptr) {
        pos.node_ -> previous_ -> next_ = newNextForPrevious;
      }
      if (pos.node_ -> next_ != nullptr) {
        pos.node_ -> next_ -> previous_ = newPreviousForNext;
      }
      delete pos.node_;
    }
  }

  void push_back(const_reference value) {
    if (last_ == nullptr) {
      last_ = new ListNode(value);
      first_ = last_;
    } else {
      last_ -> next_ = new ListNode(value, last_);
      last_ = last_ -> next_;
    }
    size_++;
  }

  void pop_back() {
    if (last_ != nullptr) {
      auto toDelete = last_;
      if (last_ -> previous_ == nullptr) {
        first_ = nullptr;
      } else {
        last_ = last_ -> previous_;
        last_ -> next_ = nullptr;
      }
      erase(iterator(toDelete));
      size_--;
    }
  }

  void push_front(const_reference value);

  void pop_front();

  void swap(list& other);

  void merge(list& other);

  void splice(const_iterator pos, list& other);

  void reverse();

  void unique();
  
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

#endif  // CPP2_S21_CONTAINERS_SRC_S21_LIST_H_