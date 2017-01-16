#include "bit_manip.h"
#include "unity.h"
#include "unity_fixture.h"
#include "sha512.h"

TEST_GROUP(sha512);


TEST_SETUP(sha512)
{
}

TEST_TEAR_DOWN(sha512)
{
}

TEST(sha512, sha512_with_short_input)
{
  char sha[129];
  const char* teststr="abc";
  TEST_ASSERT_EQUAL_INT(0,sha512(sha,strlen(teststr),(uint8_t*)teststr));
  TEST_ASSERT_EQUAL_STRING("ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f", sha);
}

TEST(sha512, sha512_with_long_input)
{
  char sha[129];
  const char* teststr="The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog.";
  TEST_ASSERT_EQUAL_INT(0,sha512(sha,strlen(teststr),(uint8_t*)teststr));
  TEST_ASSERT_EQUAL_STRING("eadacad7da6a99f7058fcba27e5ee6986de052ed4e2a24475b88acb863fe95a6bfe996e1523d86c085dbe45655f96d9f85ad10e2cb6e93d22500c59bc2ae4a34", sha);
}

TEST(sha512, sha512_string)
{
  char sha[129];
  const char* teststr="abc";
  TEST_ASSERT_EQUAL_INT(0,sha512_string(sha,teststr));
  TEST_ASSERT_EQUAL_STRING("ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f", sha);
  const char* teststr2="The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog.";
  TEST_ASSERT_EQUAL_INT(0,sha512_string(sha,teststr2));
  TEST_ASSERT_EQUAL_STRING("eadacad7da6a99f7058fcba27e5ee6986de052ed4e2a24475b88acb863fe95a6bfe996e1523d86c085dbe45655f96d9f85ad10e2cb6e93d22500c59bc2ae4a34", sha);
}

