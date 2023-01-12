#include "s21_list.h"
#include <iostream>

class Test {
  public:
    Test(int val) : value(val) {}
    int& operator*() { return value; }
    void GetAdress() {
      std::cout<<&value<<std::endl;
    }

  private:
    int value = 5;
};

int main() {
  list<int> test;
  for (int i = 0; i < 21; i++) {
    test.push_back(i);
  }
  const list<int> test1 = test;
  std::cout<<test1.size()<<std::endl;
  auto it = test1.begin();
  *it = 5;
  return 0;
}