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

TEST(sha512, sha512_with_no_input)
{
  char sha[129];
  const char* teststr="";
  TEST_ASSERT_EQUAL_INT(0,sha512(sha,0,(uint8_t*)teststr));
  TEST_ASSERT_EQUAL_STRING("cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e", sha);
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

  char shadbl[129];
  const char* teststr2="The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog.The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog.";
  TEST_ASSERT_EQUAL_INT(0,sha512(shadbl,strlen(teststr2),(uint8_t*)teststr2));
  TEST_ASSERT_EQUAL_STRING("fa70d1288ef549df59de3e907b8c56e124c875bb53f7c3e247b946802013e670395699b0de424c9046707655f14186520f027f25d5221870bfd6cf9c9f35f393", shadbl);

}

TEST(sha512, sha512_string)
{
  char sha[129];
  const char* teststr0="";
  TEST_ASSERT_EQUAL_INT(0,sha512_string(sha,teststr0));
  TEST_ASSERT_EQUAL_STRING("cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e", sha);
  const char* teststr="abc";
  TEST_ASSERT_EQUAL_INT(0,sha512_string(sha,teststr));
  TEST_ASSERT_EQUAL_STRING("ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f", sha);
  const char* teststr2="The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog.";
  TEST_ASSERT_EQUAL_INT(0,sha512_string(sha,teststr2));
  TEST_ASSERT_EQUAL_STRING("eadacad7da6a99f7058fcba27e5ee6986de052ed4e2a24475b88acb863fe95a6bfe996e1523d86c085dbe45655f96d9f85ad10e2cb6e93d22500c59bc2ae4a34", sha);
}

