#include "test_header.h"

namespace {
TEST(List, Constructor_Default) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List, Constructor_Initializer_list) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List, Constructor_Parameterized) {
  s21::list<double> s21_list(5);
  std::list<double> std_list(5);
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}
TEST(List, Constructor_Copy) {
  s21::list<char> s21_list_1 = {'a', 'b', 'c', 'd'};
  std::list<char> std_list_1 = {'a', 'b', 'c', 'd'};
  s21::list<char> s21_list_2 = s21_list_1;
  std::list<char> std_list_2 = std_list_1;

  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
  EXPECT_EQ(std_list_1.size(), std_list_2.size());
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}
TEST(List, Constructor_Move) {
  s21::list<char> s21_list_1 = {'a', 'b', 'c', 'd'};
  std::list<char> std_list_1 = {'a', 'b', 'c', 'd'};
  s21::list<char> s21_list_2 = std::move(s21_list_1);
  std::list<char> std_list_2 = std::move(std_list_1);

  EXPECT_EQ(s21_list_2.size(), std_list_2.size());
  EXPECT_EQ(s21_list_1.size(), std_list_1.size());
  EXPECT_EQ(s21_list_1.empty(), std_list_1.empty());
  auto it1 = s21_list_2.begin();
  auto it2 = std_list_2.begin();
  while (it1 != s21_list_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(List, Modifier_Insert) {
  s21::list<int> s21_list_1 = {'a', 'c', 'd'};
  s21::list<int> s21_list_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_list_1.begin();
  ++it;
  s21_list_1.insert(it, 'b');
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(List, Modifier_Erase) {
  s21::list<int> s21_list_1 = {'a', 'c', 'd'};
  s21::list<int> s21_list_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_list_2.begin();
  ++it;
  s21_list_2.erase(it);
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(List, Modifier_Push) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  s21_list.push_back(5);
  s21_list.push_front(0);
  std_list.push_back(5);
  std_list.push_front(0);
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(List, Modifier_Pop) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  s21_list.pop_back();
  s21_list.pop_front();
  std_list.pop_back();
  std_list.pop_front();
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(List, Modifier_Swap) {
  s21::list<char> s21_list_1 = {'a', 'b', 'o', 'b', 'a'};
  s21::list<char> s21_list_2 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21::list<char> s21_list_3 = {'a', 'b', 'o', 'b', 'a'};
  s21::list<char> s21_list_4 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21_list_1.swap(s21_list_2);
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  auto it3 = s21_list_3.begin();
  auto it4 = s21_list_4.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != s21_list_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_4.size());
  EXPECT_EQ(s21_list_2.size(), s21_list_3.size());
}

TEST(List, Modifier_Merge) {
  s21::list<int> s21_list_1 = {1, 3, 7};
  s21::list<int> s21_list_2 = {-1, 0, 5, 8};
  std::list<int> std_list_1 = {1, 3, 7};
  std::list<int> std_list_2 = {-1, 0, 5, 8};
  s21_list_1.merge(s21_list_2);
  std_list_1.merge(std_list_2);
  auto it1 = s21_list_1.begin();
  auto it2 = std_list_1.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), std_list_1.size());
}

TEST(List, Modifier_Reverse) {
  s21::list<int> s21_list_1 = {1, 2, 3, 4};
  s21::list<int> s21_list_2 = {4, 3, 2, 1};
  s21_list_1.reverse();
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(List, Modifier_Unique) {
  s21::list<int> s21_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  std::list<int> std_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  s21_list.unique();
  std_list.unique();
  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(List, Modifier_Sort) {
  s21::list<int> s21_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  std::list<int> std_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  s21_list.sort();
  std_list.sort();
  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

}  // namespace