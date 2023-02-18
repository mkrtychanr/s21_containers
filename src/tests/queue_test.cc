#include "test_header.h"

namespace {
TEST(queue, Constructor_Default) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(queue, Constructor_Initializer_queue) {
  s21::queue<int> s21_queue = {1, 2, 3, 4};
  EXPECT_EQ(s21_queue.front(), 1);
  EXPECT_EQ(s21_queue.back(), 4);
  EXPECT_EQ(s21_queue.size(), size_t(4));
  EXPECT_EQ(s21_queue.empty(), false);
}

TEST(queue, Constructor_Copy) {
  s21::queue<char> s21_queue_1 = {'a', 'b', 'c', 'd'};
  s21::queue<char> s21_queue_2 = s21_queue_1;

  EXPECT_EQ(s21_queue_1.size(), s21_queue_2.size());

  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_queue_1.front(), s21_queue_2.front());
    EXPECT_EQ(s21_queue_1.size(), s21_queue_2.size());
    s21_queue_1.pop(), s21_queue_2.pop();
  }
}

TEST(queue, Constructor_Move) {
  s21::queue<char> s21_queue_1 = {'a', 'b', 'c', 'd'};
  s21::queue<char> s21_queue_2 = std::move(s21_queue_1);
  s21::queue<char> s21_queue_3 = {'a', 'b', 'c', 'd'};

  EXPECT_EQ(s21_queue_2.size(), s21_queue_3.size());
  EXPECT_EQ(s21_queue_1.size(), size_t(0));
  EXPECT_EQ(s21_queue_1.empty(), true);
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_queue_3.front(), s21_queue_2.front());
    EXPECT_EQ(s21_queue_3.size(), s21_queue_2.size());
    s21_queue_3.pop(), s21_queue_2.pop();
  }
}

TEST(queue, Modifier_Push) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  s21_queue.push(5);
  s21_queue.push(0);
  std_queue.push(5);
  std_queue.push(0);
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(queue, Modifier_Pop) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  s21_queue.push(5);
  s21_queue.push(0);
  std_queue.push(5);
  std_queue.push(0);
  s21_queue.pop();
  s21_queue.pop();
  std_queue.pop();
  std_queue.pop();
  s21_queue.push(15);
  s21_queue.push(10);
  std_queue.push(15);
  std_queue.push(10);
  s21_queue.pop();
  std_queue.pop();
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(queue, Modifier_Swap) {
  s21::queue<std::string> s21_queue_1 = {"aboba", "shleppa", "amogus",
                                         "abobus"};
  s21::queue<std::string> s21_queue_2 = {"shtirlits", "vovochka", "poruchik"};
  s21::queue<std::string> s21_queue_3 = {"aboba", "shleppa", "amogus",
                                         "abobus"};
  s21::queue<std::string> s21_queue_4 = {"shtirlits", "vovochka", "poruchik"};

  s21_queue_1.swap(s21_queue_2);

  EXPECT_EQ(s21_queue_1.size(), s21_queue_4.size());
  EXPECT_EQ(s21_queue_2.size(), s21_queue_3.size());
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_queue_3.front(), s21_queue_2.front());
    EXPECT_EQ(s21_queue_3.size(), s21_queue_2.size());
    s21_queue_3.pop(), s21_queue_2.pop();
  }
  for (auto i = 0; i < 3; i++) {
    EXPECT_EQ(s21_queue_1.front(), s21_queue_4.front());
    EXPECT_EQ(s21_queue_1.size(), s21_queue_4.size());
    s21_queue_1.pop(), s21_queue_4.pop();
  }
}

}  // namespace