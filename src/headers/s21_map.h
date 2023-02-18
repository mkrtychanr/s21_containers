#ifndef CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_MAP_H_
#define CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_MAP_H_

#include <limits>

#include "iterators/s21_map_iterators.h"
#include "s21_list.h"
#include "s21_list_node.h"
#include "s21_vector.h"

namespace s21 {

template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MapIterator<Key, T>;
  using const_iterator = MapConstIterator<Key, T>;
  using size_type = size_t;

  map() {
    pointers_.resize(1 / maxLoadFactor_);
    for (size_t i = 0; i < pointers_.size(); i++) {
      pointers_[i] = nullptr;
    }
  }

  map(std::initializer_list<value_type> const& items) {
    pointers_.resize(items.size() * (1 / maxLoadFactor_));
    for (size_t i = 0; i < pointers_.size(); i++) {
      pointers_[i] = nullptr;
    }
    for (auto i : items) {
      insert(i);
    }
  }

  map(const map& m) { operator=(m); }

  map(map&& m) { operator=(std::move(m)); }

  ~map() { clear(); }

  map& operator=(const map& m) {
    if (this != &m) {
      pointers_ = m.pointers_;
      list_ = m.list_;
      maxLoadFactor_ = m.maxLoadFactor_;
    }
    return *this;
  }

  map& operator=(map&& m) {
    if (this != &m) {
      pointers_ = std::move(m.pointers_);
      list_ = std::move(m.list_);
      maxLoadFactor_ = m.maxLoadFactor_;
    }
    return *this;
  }

  T& at(const Key& key) {
    auto result = findByKey_(key);
    if (!result.second) throw "key is not presented in collection";
    return result.first->second;
  }

  T& operator[](const Key& key) {
    auto result = findByKey_(key);
    if (result.second) {
      return result.first->second;
    }
    result = insertNewElement_(key, mapped_type());
    return result.first->second;
  }

  inline iterator begin() { return iterator(list_.begin()); }

  inline iterator end() { return iterator(list_.end()); }

  inline const_iterator begin() const { return const_iterator(list_.begin()); }

  inline const_iterator end() const { return const_iterator(list_.end()); }

  inline bool empty() { return list_.empty(); }

  inline size_type size() { return list_.size(); }

  size_type max_size() { return std::numeric_limits<size_type>::max(); }

  inline void clear() {
    pointers_.resize(1 / maxLoadFactor_);
    for (size_t i = 0; i < pointers_.size(); i++) {
      pointers_[i] = nullptr;
    }
    list_.clear();
  }

  std::pair<iterator, bool> insert(const_reference value) {
    return insert(value.first, value.second);
  }

  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    if (size() + 1 > max_size()) throw "Maximum of container";
    if (newLoadFactor_() > maxLoadFactor_) {
      rehash_();
    }
    std::pair<iterator, bool> result = findByKey_(key);
    if (result.second) {
      return decltype(result)(result.first, false);
    }
    return insertNewElement_(key, obj);
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    auto result = findByKey_(key);
    if (result.second) {
      result.first->second = obj;
      return result;
    } else {
      return insert(key, obj);
    }
  }

  void erase(iterator pos) {
    if (pos != end()) {
      auto hash = getHash_(pos->first);
      auto index = hash % pointers_.size();
      auto it = iterator(pointers_[index]);
      list_.erase(it);
      pointers_[index] = nullptr;
    }
  }

  void swap(map& other) {
    auto temp = std::move(other);
    other = std::move(*this);
    *this = std::move(temp);
  }

  void merge(map& other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(*it);
    }
  }

  inline bool contains(const Key& key) { return findByKey_(key).second; }

  inline double loadFactor() { return double(size()) / double(capacity()); }

  inline size_type capacity() { return pointers_.size(); }

 private:
  vector<ListNode<value_type>*> pointers_{nullptr};
  list<value_type> list_;
  double maxLoadFactor_ = 0.0625;

  inline size_type getHash_(const key_type& key) {
    return std::hash<key_type>{}(key);
  }

  inline double newLoadFactor_() {
    return double(size() + 1) / double(capacity());
  }

  std::pair<iterator, bool> insertNewElement_(const Key& key, const T& obj) {
    std::pair<iterator, bool> result;
    auto hash = getHash_(key);
    auto index = hash % pointers_.size();
    if (pointers_[index] == nullptr) {
      result = insertWithoutCollision_(key, obj, index);
    } else {
      result = insertInCollision_(key, obj, hash, index);
    }
    return result;
  }

  std::pair<iterator, bool> insertWithoutCollision_(const Key& key,
                                                    const T& obj,
                                                    size_type index) {
    list_.push_back(value_type(key, obj));
    pointers_[index] = list_.last_;
    return std::pair<iterator, bool>(iterator(list_.last_), true);
  }

  std::pair<iterator, bool> insertInCollision_(const Key& key, const T& obj,
                                               size_type hash,
                                               size_type index) {
    std::pair<iterator, bool> result;
    auto it = iterator(pointers_[index]);
    while (it != end() && getHash_(it->first) == hash) {
      ++it;
    }
    if (it == end()) {
      list_.push_back(value_type(key, obj));
      result = std::pair<iterator, bool>(iterator(list_.last_), true);
    } else {
      result = std::pair<iterator, bool>(
          iterator(list_.insert(ListIterator(it), value_type(key, obj))), true);
    }
    return result;
  }

  std::pair<iterator, bool> findByKey_(const Key& key) {
    auto hash = getHash_(key);
    auto index = hash % pointers_.size();
    if (pointers_[index] != nullptr) {
      for (auto it = iterator(pointers_[index]);
           it != end() && getHash_(it->first) == hash; ++it) {
        if (it->first == key) {
          return std::pair<iterator, bool>(it, true);
        }
      }
    }
    return std::pair<iterator, bool>(end(), false);
  }

  void rehash_() {
    map tempMap;
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

#endif  // CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_MAP_H_
