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
  TEST_ASSERT_EQUAL_UINT32(0x00000002, rotl32(1,0x00000001));
  // Ensure wrap-around
  TEST_ASSERT_EQUAL_UINT32(0x00000001, rotl32(1,0x80000000));
  
  TEST_ASSERT_EQUAL_UINT32(0x12345678, rotl32(32,0x12345678));
  TEST_ASSERT_EQUAL_UINT32(0x56781234, rotl32(16,0x12345678));
}

TEST(bit_manip, rotr32)
{
  // Ensure wrap-around
  TEST_ASSERT_EQUAL_UINT32(0x80000000, rotr32(1,0x00000001));
  // Ensure shifting
  TEST_ASSERT_EQUAL_UINT32(0x40000000, rotr32(1,0x80000000));
  
  TEST_ASSERT_EQUAL_UINT32(0x12345678, rotr32(32,0x12345678));
  TEST_ASSERT_EQUAL_UINT32(0x56781234, rotr32(16,0x12345678));
}

TEST(bit_manip, rotl64)
{
  // Ensure shifting
  TEST_ASSERT_EQUAL_UINT64(0x0000000000000002, rotl64(1,0x0000000000000001));
  // Ensure wrap-around
  TEST_ASSERT_EQUAL_UINT64(0x0000000000000001, rotl64(1,0x8000000000000000));
  
  TEST_ASSERT_EQUAL_UINT64(0x1234567890abcdef, rotl64(64,0x1234567890abcdef));
  TEST_ASSERT_EQUAL_UINT64(0x90abcdef12345678, rotl64(32,0x1234567890abcdef));
}

TEST(bit_manip, rotr64)
{
  // Ensure wrap-around
  TEST_ASSERT_EQUAL_UINT64(0x8000000000000000, rotr64(1,0x0000000000000001));
  // Ensure shifting
  TEST_ASSERT_EQUAL_UINT64(0x4000000000000000, rotr64(1,0x8000000000000000));
  
  TEST_ASSERT_EQUAL_UINT64(0x1234567890abcdef, rotr64(64,0x1234567890abcdef));
  TEST_ASSERT_EQUAL_UINT64(0x90abcdef12345678, rotr64(32,0x1234567890abcdef));
}

TEST(bit_manip, bytes_to_uint32)
{
  uint8_t bytes1[4]={0x81,0x18,0xf0,0x0f};
  TEST_ASSERT_EQUAL_UINT32(0x8118f00f, bytes_to_uint32(bytes1));

  uint8_t bytes2[4]={0xff,0x00,0xaa,0xcc};
  TEST_ASSERT_EQUAL_UINT32(0xff00aacc, bytes_to_uint32(bytes2));
}

TEST(bit_manip, bytes_to_uint64)
{
  uint8_t bytes[8]={0x81,0x18,0xf0,0x0f,0xff,0x00,0xaa,0xcc};
  TEST_ASSERT_EQUAL_UINT64(0x8118f00fff00aacc, bytes_to_uint64(bytes));
}

TEST(bit_manip, bytes_to_uint32_arr)
{
  uint8_t bytes8[]={
    0x81,0x18,0xf0,0x0f,
    0xff,0x00,0xaa,0xcc,
    0x00,0x00,0x00,0x00
  };
  uint32_t* bytes32=bytes_to_uint32_arr(3,bytes8);
  TEST_ASSERT_EQUAL_UINT32(0x8118f00f, bytes32[0]);
  TEST_ASSERT_EQUAL_UINT32(0xff00aacc, bytes32[1]);
  TEST_ASSERT_EQUAL_UINT32(0x00000000, bytes32[2]);
}
 
