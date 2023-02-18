#ifndef CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_LIST_NODE_H_
#define CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_LIST_NODE_H_

namespace s21 {

template <typename T>
class list;

template <typename T>
class ListIterator;

template <typename T>
class ListConstIterator;

template <typename Key, typename T>
class map;

template <typename Key, typename T>
class MapIterator;

template <typename Key, typename T>
class MapConstIterator;

template <typename T>
class set;

template <typename T>
class SetIterator;

template <typename T>
class SetConstIterator;

template <typename T>
struct ListNode {
  T value_ = T();
  ListNode* previous_ = nullptr;
  ListNode* next_ = nullptr;
  explicit ListNode(T value = T(), ListNode* previous = nullptr,
                    ListNode* next = nullptr)
      : value_(value), previous_(previous), next_(next) {}
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_0_SRC_HEADERS_S21_LIST_NODE_H_