#include "test_header.h"

namespace {
TEST(Set, Constructor_Default) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, Constructor_Initializer_list) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  std::set<int> std_set = {1, 2, 3, 4};
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, Constructor_Copy) {
  s21::set<char> s21_set_1 = {'a', 'b', 'c', 'd', 'a', 'b', 'f'};
  std::set<char> std_set_1 = {'a', 'b', 'c', 'd', 'a', 'b', 'f'};
  s21::set<char> s21_set_2 = s21_set_1;
  std::set<char> std_set_2 = std_set_1;

  EXPECT_EQ(s21_set_1.size(), s21_set_2.size());
  EXPECT_EQ(std_set_1.size(), std_set_2.size());
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Set, Constructor_Move) {
  s21::set<char> s21_set_1 = {'a', 'b', 'c', 'd'};
  std::set<char> std_set_1 = {'a', 'b', 'c', 'd'};
  s21::set<char> s21_set_2 = std::move(s21_set_1);
  std::set<char> std_set_2 = std::move(std_set_1);

  EXPECT_EQ(s21_set_2.size(), std_set_2.size());
  EXPECT_EQ(s21_set_1.size(), std_set_1.size());
  EXPECT_EQ(s21_set_1.empty(), std_set_1.empty());
  auto it1 = s21_set_2.begin();
  auto it2 = std_set_2.begin();
  while (it1 != s21_set_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Set, Modifier_Insert_1) {
  s21::set<char> s21_set_1 = {'a', 'c', 'd'};
  s21::set<char> s21_set_2 = {'a', 'c', 'd', 'b'};

  auto it = s21_set_1.begin();
  ++it;
  s21_set_1.insert('b');
  s21_set_1.insert('a');
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_2.size());
}

TEST(Set, Modifier_Insert_2) {
  s21::set<char> s21_set;

  s21_set.insert('b');
  s21_set.insert('b');
  s21_set.insert('b');

  EXPECT_EQ(s21_set.size(), size_t(1));
}

TEST(Set, Modifier_Insert_3) {
  s21::set<float> s21_set;
  std::set<float> std_set;

  s21_set.insert(0.0000000000000000000000000000000000000000001);
  s21_set.insert(0.000000000000000000000000000000000000000000099);
  std_set.insert(0.0000000000000000000000000000000000000000001);
  std_set.insert(0.000000000000000000000000000000000000000000099);

  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(Set, Modifier_Erase) {
  s21::set<char> s21_set_1 = {'a', 'c', 'd'};
  s21::set<char> s21_set_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_set_2.begin();
  ++it;
  s21_set_2.erase(it);
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_2.size());
}

TEST(Set, Modifier_Swap) {
  s21::set<char> s21_set_1 = {'a', 'b', 'o', 'b', 'a'};
  s21::set<char> s21_set_2 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21::set<char> s21_set_3 = {'a', 'b', 'o', 'b', 'a'};
  s21::set<char> s21_set_4 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21_set_1.swap(s21_set_2);
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  auto it3 = s21_set_3.begin();
  auto it4 = s21_set_4.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != s21_set_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_4.size());
  EXPECT_EQ(s21_set_2.size(), s21_set_3.size());
}

TEST(Set, Modifier_Merge) {
  s21::set<int> s21_set_1 = {1, 2, 3};
  s21::set<int> s21_set_2 = {3, 4, 5, 6};
  s21::set<int> s21_set_3 = {1, 2, 3, 4, 5, 6};
  s21_set_1.merge(s21_set_2);
  auto it1 = s21_set_1.begin();
  auto it3 = s21_set_3.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it3);
    ++it1, ++it3;
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_3.size());
}

TEST(Set, Lookup_Contains) {
  s21::set<int> s21_set;
  s21_set.insert(1);
  s21_set.insert(2);
  s21_set.insert(3);
  s21_set.insert(4);
  EXPECT_EQ(s21_set.contains(1), true);
  EXPECT_EQ(s21_set.contains(2), true);
  EXPECT_EQ(s21_set.contains(3), true);
  EXPECT_EQ(s21_set.contains(4), true);
  EXPECT_EQ(s21_set.contains(7), false);
  EXPECT_EQ(s21_set.contains(-2), false);
  EXPECT_EQ(s21_set.contains(0), false);
}

TEST(Set, Lookup_Find) {
  s21::set<int> s21_set;
  s21_set.insert(1);
  s21_set.insert(2);
  s21_set.insert(3);
  s21_set.insert(4);
  auto it_end = s21_set.end();
  EXPECT_EQ(*(s21_set.find(1)), 1);
  EXPECT_EQ(*(s21_set.find(3)), 3);
  EXPECT_EQ(*(s21_set.find(4)), 4);
  EXPECT_EQ(*(s21_set.find(2)), 2);
  EXPECT_EQ(s21_set.find(-4), it_end);
  EXPECT_EQ(s21_set.find(0), it_end);
  EXPECT_EQ(s21_set.find(120), it_end);
}

TEST(Set, Rehash_And_Insert_In_Collision) {
  s21::set<std::string> s21_set;
  std::unordered_set<std::string> std_set;
  s21_set.insert("asd");
  s21_set.insert("asa");
  s21_set.insert("asf");
  s21_set.insert("asg");
  s21_set.insert("ash");
  s21_set.insert("aqw");
  s21_set.insert("fgh");
  s21_set.insert("ghf");
  s21_set.insert("dghfg");
  s21_set.insert("dghfdsg");
  s21_set.insert("dghfgfsadfsd");
  s21_set.insert("dghfgfsadfsdasd");
  s21_set.insert("dghfgfsadfsasdasdd");
  s21_set.insert("dghfgfsadfsdasdasd");
  s21_set.insert("dghfgfdsasadfdsasasdsadsad");
  s21_set.insert("dghdsafgfsadfdsasasdsadsad");
  s21_set.insert("ådsdghfgfsadfdsasasdsadsad");
  s21_set.insert("dghfgfsadfdsasasdsaddsasad");
  s21_set.insert("dghfgfsadfdsasassadadsadsad");
  s21_set.insert("dghfgfsadfdsasdasasdsadsad");
  s21_set.insert("dghasdaasdfgfsadfsasdsadsad");
  s21_set.insert("asddghfgfsadfsasaß∂asdsadsad");
  s21_set.insert("dghfgfsadfasdsasdsadsad");
  s21_set.insert("dghfgfsadfsasdsadsad");
  s21_set.insert("dghfgfsasdadfsasdsadsad");
  s21_set.insert("asdsadadghfgfsadfsasdsadsad");
  std_set.insert("asd");
  std_set.insert("asa");
  std_set.insert("asf");
  std_set.insert("asg");
  std_set.insert("ash");
  std_set.insert("aqw");
  std_set.insert("fgh");
  std_set.insert("ghf");
  std_set.insert("dghfg");
  std_set.insert("dghfdsg");
  std_set.insert("dghfgfsadfsd");
  std_set.insert("dghfgfsadfsdasd");
  std_set.insert("dghfgfsadfsasdasdd");
  std_set.insert("dghfgfsadfsdasdasd");
  std_set.insert("dghfgfdsasadfdsasasdsadsad");
  std_set.insert("dghdsafgfsadfdsasasdsadsad");
  std_set.insert("ådsdghfgfsadfdsasasdsadsad");
  std_set.insert("dghfgfsadfdsasasdsaddsasad");
  std_set.insert("dghfgfsadfdsasassadadsadsad");
  std_set.insert("dghfgfsadfdsasdasasdsadsad");
  std_set.insert("dghasdaasdfgfsadfsasdsadsad");
  std_set.insert("asddghfgfsadfsasaß∂asdsadsad");
  std_set.insert("dghfgfsadfasdsasdsadsad");
  std_set.insert("dghfgfsadfsasdsadsad");
  std_set.insert("dghfgfsasdadfsasdsadsad");
  std_set.insert("asdsadadghfgfsadfsasdsadsad");
  for (auto i : std_set) {
    EXPECT_TRUE(s21_set.find(i) != s21_set.end());
  }
  EXPECT_EQ(s21_set.size(), std_set.size());
}

}  // namespace