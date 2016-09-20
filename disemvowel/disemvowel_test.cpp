#include <stdarg.h>
#include <setjmp.h>
#include <stdlib.h>

#include "../include/cmockery.h"
#include "disemvowel.h"

void test_empty_str() {
  assert_string_equal("", disemvowel(""));
}

void test_no_vowels() {
  assert_string_equal("pqrst", disemvowel("pqrst"));
}

void test_only_vowels() {
  assert_string_equal("", disemvowel("aeiouAEIOUOIEAuoiea"));
}

void test_my_name() {
  assert_string_equal("Nchls Frtg McPh", 
		      disemvowel("Nicholas Freitag McPhee"));
}

void test_punctuation() {
  assert_string_equal("n (nxplnd) lphnt!", 
		      disemvowel("An (Unexplained) Elephant!"));
}

void test_long_string() {
  char* str;
  int size;
  int i;

  size = 50000;
  str = calloc(size, sizeof(char));
  str[0] = 'x';
  str[1] = 'y';
  str[2] = 'z';
  for (i = 3; i < size-1; ++i) {
    str[i] = 'a';
  }
  str[size-1] = '\0';
  
  assert_string_equal("xyz", disemvowel(str));

  free(str);
}

int main(int argc, char* argv[]) {
  UnitTest tests[] = {
    unit_test(test_empty_str),
    unit_test(test_no_vowels),
    unit_test(test_only_vowels),
    unit_test(test_my_name),
    unit_test(test_punctuation),
    unit_test(test_long_string)
  };
  return run_tests(tests);
}
