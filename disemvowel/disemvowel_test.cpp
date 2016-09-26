#include <gtest/gtest.h>

#include "disemvowel.h"

TEST(Disemvowel, HandleEmptyString) {
  char *dis = disemvowel((char*) "");
  ASSERT_STREQ("", dis);
  free(dis);
}

TEST(Disemvowel, HandleNoVowels) {
  char *dis = disemvowel((char*) "pqrst");
  ASSERT_STREQ("pqrst", dis);
  free(dis);
}

TEST(Disemvowel, HandleOnlyVowels) {
  char *dis = disemvowel((char*) "aeiouAEIOUOIEAuoiea");
  ASSERT_STREQ("", dis);
  free(dis);
}

TEST(Disemvowel, HandleMorrisMinnesota) {
  char *dis = disemvowel((char*) "Morris, Minnesota");
  ASSERT_STREQ("Mrrs, Mnnst", dis);
  free(dis);
}

TEST(Disemvowel, HandlePunctuation) {
  char *dis = disemvowel((char*) "An (Unexplained) Elephant!");
  ASSERT_STREQ("n (nxplnd) lphnt!", dis);
  free(dis);
}

TEST(Disemvowel, HandleLongString) {
  char* str;
  int size;
  int i;

  size = 50000;
  str = (char*) calloc(size, sizeof(char));
  str[0] = 'x';
  str[1] = 'y';
  str[2] = 'z';
  for (i = 3; i < size-1; ++i) {
    str[i] = 'a';
  }
  str[size-1] = '\0';

  char *dis = disemvowel(str);
  ASSERT_STREQ("xyz", dis);
  free(dis);
  free(str);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
