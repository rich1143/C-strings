#include <gtest/gtest.h>

#include "palindrome.h"

void is_palindrome(char* str) {
  char *pal = palindrome(str);
  ASSERT_STREQ(pal, "Yes");
  free(pal);
}

void not_palindrome(char* str) {
  char *not_your_pal = palindrome(str);
  ASSERT_STREQ(not_your_pal, "No");
  free(not_your_pal);
}

TEST(Palindrome, HandlesEmptyString) {
  is_palindrome((char*) "");
}

TEST(Palindrome, HandlesSingletons) {
  is_palindrome((char*) "a");
  is_palindrome((char*) "b");
  is_palindrome((char*) "c");
}

TEST(Palindrome, HandlesLengthTwo) {
  is_palindrome((char*) "aa");
  is_palindrome((char*) "bb");
  not_palindrome((char*) "ab");
}

TEST(Palindrome, HandlesLengthThree) {
  is_palindrome((char*) "aaa");
  is_palindrome((char*) "bab");
  not_palindrome((char*) "abc");
  not_palindrome((char*) "abb");
}

TEST(Palindrome, HandlesLengthFour) {
  is_palindrome((char*) "aaaa");
  is_palindrome((char*) "baab");
  not_palindrome((char*) "abcd");
  not_palindrome((char*) "aabb");
  not_palindrome((char*) "abbc");
  not_palindrome((char*) "abca");
}

TEST(Palindrome, HandlesLongerStrings) {
  is_palindrome((char*) "aaaaaaaaaaa");
  is_palindrome((char*) "aaaaaaaaaaaa");
  is_palindrome((char*) "abcdefgfedcba");
  is_palindrome((char*) "abcdefggfedcba");
  not_palindrome((char*) "abcdefghijk");
  not_palindrome((char*) "aaaaaaaaaaaabaaaa");
  not_palindrome((char*) "abcdxfgfedcba");
  not_palindrome((char*) "abcdefggfexcba");
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
