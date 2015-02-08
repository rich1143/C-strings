#include <stdarg.h>
#include <setjmp.h>
#include <stdlib.h>

#include "../include/cmockery.h"
#include "palindrome.h"

void is_palindrome(char* str) {
  assert_string_equal(palindrome(str), "Yes");  
}

void not_palindrome(char* str) {
  assert_string_equal(palindrome(str), "No");  
}

void test_empty_str() {
  is_palindrome("");
}

void test_singleton() {
  is_palindrome("a");
  is_palindrome("b");
  is_palindrome("c");
}

void test_length_two() {
  is_palindrome("aa");
  is_palindrome("bb");
  not_palindrome("ab");
}

void test_length_three() {
  is_palindrome("aaa");
  is_palindrome("bab");
  not_palindrome("abc");
  not_palindrome("abb");
}

void test_length_four() {
  is_palindrome("aaaa");
  is_palindrome("baab");
  not_palindrome("abcd");
  not_palindrome("aabb");
  not_palindrome("abbc");
  not_palindrome("abca");
}

void test_long_strings() {
  is_palindrome("aaaaaaaaaaa");
  is_palindrome("aaaaaaaaaaaa");
  is_palindrome("abcdefgfedcba");
  is_palindrome("abcdefggfedcba");
  not_palindrome("abcdefghijk");
  not_palindrome("aaaaaaaaaaaabaaaa");
  not_palindrome("abcdxfgfedcba");
  not_palindrome("abcdefggfexcba");
}

int main(int argc, char* argv[]) {
  UnitTest tests[] = {
    unit_test(test_empty_str),
    unit_test(test_singleton),
    unit_test(test_length_two),
    unit_test(test_length_three),
    unit_test(test_length_four),
    unit_test(test_long_strings)
  };
  return run_tests(tests);
}
