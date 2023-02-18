#include "test_header.h"

namespace {
TEST(Map, Constructor_Default) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(Map, Constructor_Initializer_list) {
  s21::map<int, std::string> s21_map = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  std::map<int, std::string> std_map = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(Map, Constructor_Copy) {
  s21::map<int, std::string> s21_map_1 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  std::map<int, std::string> std_map_1 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  s21::map<int, std::string> s21_map_2 = s21_map_1;
  std::map<int, std::string> std_map_2 = std_map_1;

  EXPECT_EQ(s21_map_1.size(), s21_map_2.size());
  EXPECT_EQ(std_map_1.size(), std_map_2.size());
  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Map, Constructor_Move) {
  s21::map<int, std::string> s21_map_1 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  std::map<int, std::string> std_map_1 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  s21::map<int, std::string> s21_map_2 = std::move(s21_map_1);
  std::map<int, std::string> std_map_2 = std::move(std_map_1);

  EXPECT_EQ(s21_map_2.size(), std_map_2.size());
  EXPECT_EQ(s21_map_1.size(), std_map_1.size());
  EXPECT_EQ(s21_map_1.empty(), std_map_1.empty());
  auto it1 = s21_map_2.begin();
  auto it2 = std_map_2.begin();
  while (it1 != s21_map_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Map, Modifier_Insert) {
  s21::map<char, int> s21_map_1 = {{'b', 228}, {'c', 1337}};
  s21::map<char, int> s21_map_2 = {
      {'b', 228},
      {'c', 1337},
      {'d', 322},
      {'a', 5},
  };

  EXPECT_EQ(s21_map_1.insert('d', 322).second, true);
  EXPECT_EQ(s21_map_1.insert('d', 14).second, false);

  std::pair<char, int> pair1('a', 5);
  std::pair<char, int> pair2('a', 28);

  EXPECT_EQ(s21_map_1.insert(pair1).second, true);
  EXPECT_EQ(s21_map_1.insert(pair2).second, false);

  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_2.size());
}

TEST(Map, Rehash_And_Insert_In_Collision) {
  s21::map<std::string, int> s21_map;
  s21_map.insert("asd", 0);
  s21_map.insert("asa", 1);
  s21_map.insert("asf", 2);
  s21_map.insert("asg", 3);
  s21_map.insert("ash", 4);
  s21_map.insert("aqw", 5);
  s21_map.insert("fgh", 6);
  s21_map.insert("ghf", 7);
  s21_map.insert("dghfg", 8);
  s21_map.insert("dghfdsg", 9);
  s21_map.insert("dghfgfsadfsd", 10);
  s21_map.insert("dghfgfsadfsdasd", 11);
  s21_map.insert("dghfgfsadfsasdasdd", 12);
  s21_map.insert("dghfgfsadfsdasdasd", 13);
  s21_map.insert("dghfgfdsasadfdsasasdsadsad", 14);
  s21_map.insert("dghdsafgfsadfdsasasdsadsad", 15);
  s21_map.insert("ådsdghfgfsadfdsasasdsadsad", 16);
  s21_map.insert("dghfgfsadfdsasasdsaddsasad", 17);
  s21_map.insert("dghfgfsadfdsasassadadsadsad", 18);
  s21_map.insert("dghfgfsadfdsasdasasdsadsad", 19);
  s21_map.insert("dghasdaasdfgfsadfsasdsadsad", 20);
  s21_map.insert("asddghfgfsadfsasaß∂asdsadsad", 21);
  s21_map.insert("dghfgfsadfasdsasdsadsad", 22);
  s21_map.insert("dghfgfsadfsasdsadsad", 23);
  s21_map.insert("dghfgfsasdadfsasdsadsad", 24);
  s21_map.insert("asdsadadghfgfsadfsasdsadsad", 25);
  std::unordered_map<std::string, int> std_map;
  std_map.insert(std::pair<std::string, int>("asd", 0));
  std_map.insert(std::pair<std::string, int>("asa", 1));
  std_map.insert(std::pair<std::string, int>("asf", 2));
  std_map.insert(std::pair<std::string, int>("asg", 3));
  std_map.insert(std::pair<std::string, int>("ash", 4));
  std_map.insert(std::pair<std::string, int>("aqw", 5));
  std_map.insert(std::pair<std::string, int>("fgh", 6));
  std_map.insert(std::pair<std::string, int>("ghf", 7));
  std_map.insert(std::pair<std::string, int>("dghfg", 8));
  std_map.insert(std::pair<std::string, int>("dghfdsg", 9));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsd", 10));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsdasd", 11));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsasdasdd", 12));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsdasdasd", 13));
  std_map.insert(std::pair<std::string, int>("dghfgfdsasadfdsasasdsadsad", 14));
  std_map.insert(std::pair<std::string, int>("dghdsafgfsadfdsasasdsadsad", 15));
  std_map.insert(std::pair<std::string, int>("ådsdghfgfsadfdsasasdsadsad", 16));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfdsasasdsaddsasad", 17));
  std_map.insert(
      std::pair<std::string, int>("dghfgfsadfdsasassadadsadsad", 18));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfdsasdasasdsadsad", 19));
  std_map.insert(
      std::pair<std::string, int>("dghasdaasdfgfsadfsasdsadsad", 20));
  std_map.insert(
      std::pair<std::string, int>("asddghfgfsadfsasaß∂asdsadsad", 21));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfasdsasdsadsad", 22));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsasdsadsad", 23));
  std_map.insert(std::pair<std::string, int>("dghfgfsasdadfsasdsadsad", 24));
  std_map.insert(
      std::pair<std::string, int>("asdsadadghfgfsadfsasdsadsad", 25));
  for (auto i : std_map) {
    EXPECT_EQ(i.second, s21_map[i.first]);
  }
  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(Map, Modifier_Get_Value) {
  s21::map<std::string, int> m;
  m["123"] = 5;
  EXPECT_EQ(5, m["123"]);
}

TEST(Map, Modifier_Insert_or_assign) {
  s21::map<char, int> s21_map_1 = {{'b', 228}, {'c', 1337}};
  s21::map<char, int> s21_map_2 = {
      {'b', 228},
      {'c', 1337},
      {'d', 14},
      {'a', 28},
  };

  EXPECT_EQ(s21_map_1.insert_or_assign('d', 322).second, true);
  EXPECT_EQ(s21_map_1.insert_or_assign('d', 14).second, true);

  EXPECT_EQ(s21_map_1.insert_or_assign('a', 5).second, true);
  EXPECT_EQ(s21_map_1.insert_or_assign('a', 28).second, true);

  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_2.size());
}

TEST(Map, Modifier_Erase_1) {
  s21::map<int, std::string> s21_map_1 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  s21::map<int, std::string> s21_map_2 = {
      {1, "aboba"}, {3, "amogus"}, {4, "abobus"}};
  auto it = s21_map_1.begin();
  ++it;
  s21_map_1.erase(it);
  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_2.size());
}

TEST(Map, Modifier_Erase_2) {
  s21::map<int, std::string> s21_map = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  for (auto it = s21_map.begin(); it != s21_map.end(); ++it) {
    s21_map.erase(it);
  }

  EXPECT_EQ(s21_map.empty(), true);
  EXPECT_EQ(s21_map.size(), size_t(0));

  s21_map.insert(1, "aboba");

  EXPECT_EQ(s21_map.empty(), false);
  EXPECT_EQ(s21_map.size(), size_t(1));
  EXPECT_EQ(s21_map.contains(1), true);
}

TEST(Map, Modifier_Swap) {
  s21::map<int, std::string> s21_map_1 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  s21::map<int, std::string> s21_map_2 = {
      {10, "shtirlits"}, {12, "vovochka"}, {13, "poruchik"}, {14, "chepaev"}};
  s21::map<int, std::string> s21_map_3 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  s21::map<int, std::string> s21_map_4 = {
      {10, "shtirlits"}, {12, "vovochka"}, {13, "poruchik"}, {14, "chepaev"}};

  s21_map_1.swap(s21_map_2);
  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  auto it3 = s21_map_3.begin();
  auto it4 = s21_map_4.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != s21_map_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_4.size());
  EXPECT_EQ(s21_map_2.size(), s21_map_3.size());
}

TEST(Map, Modifier_Mem_Merge) {
  s21::map<int, std::string> s21_map_1 = {
      {1, "diksi"}, {2, "podval so zmeyami"}, {3, "introvskie klouny"}};
  s21::map<int, std::string> s21_map_2 = {
      {3, "introvskie klouny"}, {4, "sbebr platforma"}, {5, "avito"}};
  s21::map<int, std::string> s21_map_3 = {{1, "diksi"},
                                          {2, "podval so zmeyami"},
                                          {3, "introvskie klouny"},
                                          {4, "sbebr platforma"},
                                          {5, "avito"}};
  s21_map_1.merge(s21_map_2);
  auto it1 = s21_map_1.begin();
  auto it3 = s21_map_3.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it3);
    ++it1, ++it3;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_3.size());
}

TEST(Map, Lookup_Contains) {
  s21::map<int, std::string> s21_map;
  s21_map.insert(1, "salamandry");
  s21_map.insert(2, "medoedy");
  s21_map.insert(3, "kapibary");
  s21_map.insert(4, "alpaki");
  EXPECT_EQ(s21_map.contains(1), true);
  EXPECT_EQ(s21_map.contains(2), true);
  EXPECT_EQ(s21_map.contains(3), true);
  EXPECT_EQ(s21_map.contains(4), true);
  EXPECT_EQ(s21_map.contains(7), false);
  EXPECT_EQ(s21_map.contains(-2), false);
  EXPECT_EQ(s21_map.contains(0), false);
}

}  // namespace