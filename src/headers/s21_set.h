#ifndef CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_SET_H_
#define CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_SET_H_

#include "iterators/s21_set_iterators.h"
#include "s21_list.h"
#include "s21_list_node.h"
#include "s21_vector.h"

namespace s21 {

template <typename T>
class set {
 public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = SetIterator<T>;
  using const_iterator = SetConstIterator<T>;
  using size_type = size_t;

  set() {
    pointers_.resize(1 / maxLoadFactor_);
    for (size_t i = 0; i < pointers_.size(); i++) {
      pointers_[i] = nullptr;
    }
  }

  set(std::initializer_list<value_type> const& items) {
    pointers_.resize(items.size() * (1 / maxLoadFactor_));
    for (size_t i = 0; i < pointers_.size(); i++) {
      pointers_[i] = nullptr;
    }
    for (const auto& i : items) {
      insert(i);
    }
  }

  set(const set& s) { operator=(s); }

  set(set&& s) { operator=(std::move(s)); }

  ~set() { clear(); }

  set& operator=(const set& s) {
    if (this != &s) {
      pointers_ = s.pointers_;
      list_ = s.list_;
      maxLoadFactor_ = s.maxLoadFactor_;
    }
    return *this;
  }

  set& operator=(set&& s) {
    if (this != &s) {
      pointers_ = std::move(s.pointers_);
      list_ = std::move(s.list_);
      maxLoadFactor_ = s.maxLoadFactor_;
    }
    return *this;
  }

  inline iterator begin() { return iterator(list_.begin()); }

  inline iterator end() { return iterator(list_.end()); }

  inline const_iterator begin() const { return const_iterator(list_.begin()); }

  inline const_iterator end() const { return const_iterator(list_.end()); }

  inline bool empty() { return list_.empty(); }

  inline size_type size() { return list_.size(); }

  inline size_type max_size() { return std::numeric_limits<size_type>::max(); }

  inline void clear() {
    pointers_.clear();
    list_.clear();
  }

  std::pair<iterator, bool> insert(const_reference value) {
    if (size() + 1 > max_size()) throw "Maximum of container";
    if (newLoadFactor_() > maxLoadFactor_) {
      rehash_();
    }
    std::pair<iterator, bool> result = findByKey_(value);
    if (result.second) {
      return decltype(result)(result.first, false);
    }
    return insertNewElement_(value);
  }

  void erase(iterator pos) {
    if (pos != end()) {
      auto hash = getHash_(*pos);
      auto index = hash % pointers_.size();
      auto it = iterator(pointers_[index]);
      list_.erase(it);
      pointers_[index] = nullptr;
    }
  }

  void swap(set& other) {
    auto temp = std::move(other);
    other = std::move(*this);
    *this = std::move(temp);
  }

  void merge(set& other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(*it);
    }
    other.clear();
  }

  iterator find(const_reference key) {
    auto result = findByKey_(key);
    if (result.second) {
      return result.first;
    } else {
      return end();
    }
  }

  bool contains(const_reference key) { return findByKey_(key).second; }

  inline double loadFactor() { return double(size()) / double(capacity()); }

  inline size_type capacity() { return pointers_.size(); }

 private:
  vector<ListNode<value_type>*> pointers_{nullptr};
  list<value_type> list_;
  double maxLoadFactor_ = 0.0625;

  inline size_type getHash_(const value_type& key) {
    return std::hash<value_type>{}(key);
  }

  inline double newLoadFactor_() {
    return double(size() + 1) / double(capacity());
  }

  std::pair<iterator, bool> insertNewElement_(const_reference value) {
    std::pair<iterator, bool> result;
    auto hash = getHash_(value);
    auto index = hash % pointers_.size();
    if (pointers_[index] == nullptr) {
      result = insertWithoutCollision_(value, index);
    } else {
      result = insertInCollision_(value, hash, index);
    }
    return result;
  }

  std::pair<iterator, bool> insertWithoutCollision_(const_reference value,
                                                    size_type index) {
    list_.push_back(value);
    pointers_[index] = list_.last_;
    return std::pair<iterator, bool>(iterator(list_.last_), true);
  }

  std::pair<iterator, bool> insertInCollision_(const_reference value,
                                               size_type hash,
                                               size_type index) {
    std::pair<iterator, bool> result;
    auto it = iterator(pointers_[index]);
    while (it != end() && getHash_(*it) == hash) {
      ++it;
    }
    if (it == end()) {
      list_.push_back(value);
      result = std::pair<iterator, bool>(iterator(list_.last_), true);
    } else {
      result = std::pair<iterator, bool>(
          iterator(list_.insert(ListIterator(it), value)), true);
    }
    return result;
  }

  std::pair<iterator, bool> findByKey_(const_reference value) {
    auto hash = getHash_(value);
    auto index = hash % pointers_.size();
    if (pointers_[index] != nullptr) {
      for (auto it = iterator(pointers_[index]);
           it != end() && getHash_(*it) == hash; ++it) {
        if (*it == value) {
          return std::pair<iterator, bool>(it, true);
        }
      }
    }
    return std::pair<iterator, bool>(end(), false);
  }

  void rehash_() {
    set tempMap;
    tempMap.pointers_.resize(pointers_.size() / maxLoadFactor_);
    for (size_t i = 0; i < tempMap.pointers_.size(); i++) {
      tempMap.pointers_[i] = nullptr;
    }
    for (auto it = begin(); it != end(); ++it) {
      tempMap.insert(*it);
    }
    *this = std::move(tempMap);
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_SET_H_
