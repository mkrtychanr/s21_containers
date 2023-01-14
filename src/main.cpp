#include "s21_list.h"
#include <iostream>

void printList(const list<int> l) {
  for (auto it = l.begin(); it != l.end(); ++it) {
    std::cout<<*it<<" ";
  }
  std::cout<<std::endl;
}

int main() {
  list<int> a;
  list<int> b;
  for (int i = 10; i < 50; i += 10) {
    a.push_back(i);
    b.push_back(i/10);
  }
  a.splice(a.begin(), b);
  printList(a);
  a.reverse();
  printList(a);
  list<int> c {1, 2, 4, 2};
  printList(c);
  return 0;
}