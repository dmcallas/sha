#include "bit_manip.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(bit_manip);


TEST_SETUP(bit_manip)
{
}

TEST_TEAR_DOWN(bit_manip)
{
}

TEST(bit_manip, rotl32)
{
  // Ensure shifting
  TEST_ASSERT_EQUAL_UINT32(0x2, rotl32(1,0x00000001));
  // Ensure wrap-around
  TEST_ASSERT_EQUAL_UINT32(0x1, rotl32(1,0x80000000));
  TEST_ASSERT_EQUAL_UINT32(0x12345678, rotl32(32,0x12345678));
}

TEST(bit_manip, rotr32)
{
  // Ensure wrap-around
  TEST_ASSERT_EQUAL_UINT32(0x80000000, rotr32(1,0x00000001));
  // Ensure shifting
  TEST_ASSERT_EQUAL_UINT32(0x40000000, rotr32(1,0x80000000));
  TEST_ASSERT_EQUAL_UINT32(0x12345678, rotr32(32,0x12345678));
}
