#include "bit_manip.h"
#include "unity.h"
#include "unity_fixture.h"
#include "sha1.h"

TEST_GROUP(sha1);

TEST_SETUP(sha1)
{
}

TEST_TEAR_DOWN(sha1)
{
}

TEST(sha1, sha1_f)
{
  TEST_ASSERT_EQUAL_UINT32(0b11001010,sha1_f(10,0b11110000,0b11001100,0b10101010));
  TEST_ASSERT_EQUAL_UINT32(0b10010110,sha1_f(30,0b11110000,0b11001100,0b10101010));
  TEST_ASSERT_EQUAL_UINT32(0b11101000,sha1_f(50,0b11110000,0b11001100,0b10101010));
  TEST_ASSERT_EQUAL_UINT32(0b10010110,sha1_f(70,0b11110000,0b11001100,0b10101010));
}

TEST(sha1, sha1_with_short_input)
{
  char sha[45];
  const char* teststr="abc";
  TEST_ASSERT_EQUAL_INT(0,sha1(sha,strlen(teststr),(uint8_t*)teststr));
  TEST_ASSERT_EQUAL_STRING("a9993e364706816aba3e25717850c26c9cd0d89d", sha);
}

TEST(sha1, sha1_with_long_input)
{
  char sha[45];
  const char* teststr="The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog.";
  TEST_ASSERT_EQUAL_INT(0,sha1(sha,strlen(teststr),(uint8_t*)teststr));
  TEST_ASSERT_EQUAL_STRING("8eb09e076e6afa8aaaf8ff172f76cee84c791994", sha);
}


TEST(sha1, sha1_string)
{
  char sha[41];
  const char* teststr="The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog.";
  TEST_ASSERT_EQUAL_INT(0,sha1_string(sha,teststr));
  TEST_ASSERT_EQUAL_STRING("8eb09e076e6afa8aaaf8ff172f76cee84c791994", sha);
}
