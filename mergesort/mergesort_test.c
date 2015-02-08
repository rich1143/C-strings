#include <stdarg.h>
#include <setjmp.h>
#include <stdlib.h>

#include "../include/cmockery.h"
#include "mergesort.h"

bool arrays_match(int size, int a[], int b[]) {
  int i;

  for (i=0; i<size; ++i) {
    assert_int_equal(a[i], b[i]);
  }

  return true;
}

void test_empty_list() {
  int a[] = { };
  int b[] = { };
  mergesort(0, b);
  assert_true(arrays_match(0, a, b));
}

void test_singleton_list() {
  int a[] = { 5 };
  int b[] = { 5 };
  mergesort(1, b);
  assert_true(arrays_match(1, a, b));
}

void test_ordered_pair() {
  int a[] = { 5, 8 };
  int expected[] = { 5, 8 };
  mergesort(2, a);
  assert_true(arrays_match(2, a, expected));
}

void test_unordered_pair() {
  int a[] = { 8, 5 };
  int expected[] = { 5, 8 };
  mergesort(2, a);
  assert_true(arrays_match(2, a, expected));
}

void test_mixed() {
  int a[] = { 5, 8, 9, 6, 3, 2, 0 };
  int expected[] = { 0, 2, 3, 5, 6, 8, 9 };
  mergesort(7, a);
  assert_true(arrays_match(7, a, expected));
}

void test_ordered() {
  int a[] = { 0, 2, 3, 5, 6, 8, 9 };
  int expected[] = { 0, 2, 3, 5, 6, 8, 9 };
  mergesort(7, a);
  assert_true(arrays_match(7, a, expected));
}

void test_reversed() {
  int a[] = { 9, 8, 6, 5, 3, 2, 0 };
  int expected[] = { 0, 2, 3, 5, 6, 8, 9 };
  mergesort(7, a);
  assert_true(arrays_match(7, a, expected));
}

int main(int argc, char* argv[]) {
  UnitTest tests[] = {
    unit_test(test_empty_list),
    unit_test(test_singleton_list),
    unit_test(test_ordered_pair),
    unit_test(test_unordered_pair),
    unit_test(test_mixed),
    unit_test(test_ordered),
    unit_test(test_reversed)
  };
  return run_tests(tests);
}
