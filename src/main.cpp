#include "headers/s21_list.h"
#include <iostream>

void printList(const s21::list<int> l) {
  for (auto it = l.begin(); it != l.end(); ++it) {
    std::cout<<*it<<" ";
  }
  std::cout<<std::endl;
}

int main() {
  s21::list<int> a;
  s21::list<int> b;
  for (int i = 10; i < 50; i += 10) {
    a.push_back(i);
    b.push_back(i/10);
  }
  a.splice(a.begin(), b);
  printList(a);
  a.reverse();
  printList(a);
  s21::list<int> c {1, 2, 4, 2};
  printList(c);
  return 0;
}