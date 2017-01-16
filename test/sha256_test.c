#include "bit_manip.h"
#include "unity.h"
#include "unity_fixture.h"
#include "sha256.h"

TEST_GROUP(sha256);


TEST_SETUP(sha256)
{
}

TEST_TEAR_DOWN(sha256)
{
}

TEST(sha256, sha256_with_short_input)
{
  char sha[65];
  const char* teststr="abc";
  TEST_ASSERT_EQUAL_INT(0,sha256(sha,strlen(teststr),(uint8_t*)teststr));
  TEST_ASSERT_EQUAL_STRING("ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad", sha);
}

TEST(sha256, sha256_with_long_input)
{
  char sha[65];
  const char* teststr="The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog.";
  TEST_ASSERT_EQUAL_INT(0,sha256(sha,strlen(teststr),(uint8_t*)teststr));
  TEST_ASSERT_EQUAL_STRING("635241ac823ee4a81fbb410c92be616b0a89191083d8d7b5d232c823dc8df4f5", sha);
}

TEST(sha256, sha256_string)
{
  char sha[65];
  const char* teststr="abc";
  TEST_ASSERT_EQUAL_INT(0,sha256_string(sha,teststr));
  TEST_ASSERT_EQUAL_STRING("ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad", sha);
  const char* teststr2="The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog.";
  TEST_ASSERT_EQUAL_INT(0,sha256_string(sha,teststr2));
  TEST_ASSERT_EQUAL_STRING("635241ac823ee4a81fbb410c92be616b0a89191083d8d7b5d232c823dc8df4f5", sha);
}
