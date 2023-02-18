#include "test_header.h"

namespace {
TEST(Stack, Constructor_Default) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(Stack, Constructor_Initializer_stack) {
  s21::stack<int> s21_stack = {1, 2, 3, 4};
  EXPECT_EQ(s21_stack.top(), 4);
  EXPECT_EQ(s21_stack.size(), size_t(4));
  EXPECT_EQ(s21_stack.empty(), false);
}

TEST(Stack, Constructor_Copy) {
  s21::stack<char> s21_stack_1 = {'a', 'b', 'c', 'd'};
  s21::stack<char> s21_stack_2 = s21_stack_1;

  EXPECT_EQ(s21_stack_1.size(), s21_stack_2.size());

  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_stack_1.top(), s21_stack_2.top());
    EXPECT_EQ(s21_stack_1.size(), s21_stack_2.size());
    s21_stack_1.pop(), s21_stack_2.pop();
  }
}

TEST(Stack, Constructor_Move) {
  s21::stack<char> s21_stack_1 = {'a', 'b', 'c', 'd'};
  s21::stack<char> s21_stack_2 = std::move(s21_stack_1);
  s21::stack<char> s21_stack_3 = {'a', 'b', 'c', 'd'};

  EXPECT_EQ(s21_stack_2.size(), s21_stack_3.size());
  EXPECT_EQ(s21_stack_1.size(), size_t(0));
  EXPECT_EQ(s21_stack_1.empty(), true);
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_stack_3.top(), s21_stack_2.top());
    EXPECT_EQ(s21_stack_3.size(), s21_stack_2.size());
    s21_stack_3.pop(), s21_stack_2.pop();
  }
}

TEST(Stack, Modifier_Push) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  s21_stack.push(5);
  s21_stack.push(0);
  std_stack.push(5);
  std_stack.push(0);
  EXPECT_EQ(s21_stack.top(), std_stack.top());
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(Stack, Modifier_Pop) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  s21_stack.push(5);
  s21_stack.push(0);
  std_stack.push(5);
  std_stack.push(0);
  s21_stack.pop();
  s21_stack.pop();
  std_stack.pop();
  std_stack.pop();
  s21_stack.push(15);
  s21_stack.push(10);
  std_stack.push(15);
  std_stack.push(10);
  s21_stack.pop();
  std_stack.pop();
  EXPECT_EQ(s21_stack.top(), std_stack.top());
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(Stack, Modifier_Swap) {
  s21::stack<std::string> s21_stack_1 = {"aboba", "shleppa", "amogus",
                                         "abobus"};
  s21::stack<std::string> s21_stack_2 = {"shtirlits", "vovochka", "poruchik"};
  s21::stack<std::string> s21_stack_3 = {"aboba", "shleppa", "amogus",
                                         "abobus"};
  s21::stack<std::string> s21_stack_4 = {"shtirlits", "vovochka", "poruchik"};

  s21_stack_1.swap(s21_stack_2);

  EXPECT_EQ(s21_stack_1.size(), s21_stack_4.size());
  EXPECT_EQ(s21_stack_2.size(), s21_stack_3.size());
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_stack_3.top(), s21_stack_2.top());
    EXPECT_EQ(s21_stack_3.size(), s21_stack_2.size());
    s21_stack_3.pop(), s21_stack_2.pop();
  }
  for (auto i = 0; i < 3; i++) {
    EXPECT_EQ(s21_stack_1.top(), s21_stack_4.top());
    EXPECT_EQ(s21_stack_1.size(), s21_stack_4.size());
    s21_stack_1.pop(), s21_stack_4.pop();
  }
}

}  // namespace