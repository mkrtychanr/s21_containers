#ifndef CPP2_S21_CONTAINERS_SRC_S21_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_S21_LIST_H_

template <typename T>
class list<T> {
 public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef ListIterator<value_type> iterator;
  typedef ListConstIterator<value_type> const_iterator;
  typedef size_t size_type;

  class ListIterator<value_type> {};
  class ListConstIterator<value_type> {};

  list();

  list(size_type n);

  list(std::initalizer_list<value_type> const &items);

  list(const list& l);

  list(list&& l);

  ~list();

  list& operator=(list &&l);

  list& operator=(cosnt list& l);

  const_reference front() const;

  const_reference back() const;

  iterator begin();

  iterator end();

  bool empty() const;

  size_type size() const;

  size_type max_size() const;

  void clear();

  iterator insert(iterator pos, const_reference value);

  void erase(iterator pos);

  void push_back(const_reference value);

  void pop_back();

  void push_front(const_reference value);

  void pop_front();

  void swap(list& other);

  void merge(list& other);

  void splice(const_iterator pos, list& other);

  void reverse();

  void unique();
  
  void sort();

 private:
  struct ListNode<value_type> {
    value_type value = value_type();
    ListNode* previous = nullptr;
    ListNode* next = nullptr;
  };
};

#endif  // CPP2_S21_CONTAINERS_SRC_S21_LIST_H_