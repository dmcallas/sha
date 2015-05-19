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

TEST(sha1, ch32_and_ch64)
{
  /* | x | y | z | ~x | x&y | ~x&z | (x&y)^(~x&z) |
   * |---+---+---+----+-----+------+--------------|
   * | 1 | 1 | 1 |  0 |   1 |    0 |            1 |
   * | 1 | 1 | 0 |  0 |   1 |    0 |            1 |
   * | 1 | 0 | 1 |  0 |   0 |    0 |            0 |
   * | 1 | 0 | 0 |  0 |   0 |    0 |            0 |
   * | 0 | 1 | 1 |  1 |   0 |    1 |            1 |
   * | 0 | 1 | 0 |  1 |   0 |    0 |            0 |
   * | 0 | 0 | 1 |  1 |   0 |    1 |            1 |
   * | 0 | 0 | 0 |  1 |   0 |    0 |            0 |
   */
  TEST_ASSERT_EQUAL_UINT32(
			   0b11001010,
			   ch32(
				0b11110000,
				0b11001100,
				0b10101010
				)
			   );
  TEST_ASSERT_EQUAL_UINT64(
			   0b11001010,
			   ch64(
				0b11110000,
				0b11001100,
				0b10101010
				)
			   );
}

TEST(sha1, parity32)
{
  /* | x | y | z | x^y | x^y^z |
   * |---+---+---+-----+-------|
   * | 1 | 1 | 1 |  0  |   1   |
   * | 1 | 1 | 0 |  0  |   0   |
   * | 1 | 0 | 1 |  1  |   0   |
   * | 1 | 0 | 0 |  1  |   1   |
   * | 0 | 1 | 1 |  1  |   0   |
   * | 0 | 1 | 0 |  1  |   1   |
   * | 0 | 0 | 1 |  0  |   1   |
   * | 0 | 0 | 0 |  0  |   0   |
   */
  TEST_ASSERT_EQUAL_UINT32(
			   0b10010110,
			   parity32(
				0b11110000,
				0b11001100,
				0b10101010
				)
			   );
}


TEST(sha1, maj32_and_maj64)
{
  /* | x | y | z | x&y | x&z | y&z | (x&y)^(x&z) | (x&y)^(x&z)^(y&z) |
   * |---+---+---+-----+-----+-----+-------------+-------------------|
   * | 1 | 1 | 1 |   1 |   1 |   1 |           0 | 1                 |
   * | 1 | 1 | 0 |   1 |   0 |   0 |           1 | 1                 |
   * | 1 | 0 | 1 |   0 |   1 |   0 |           1 | 1                 |
   * | 1 | 0 | 0 |   0 |   0 |   0 |           0 | 0                 |
   * | 0 | 1 | 1 |   0 |   0 |   1 |           0 | 1                 |
   * | 0 | 1 | 0 |   0 |   0 |   0 |           0 | 0                 |
   * | 0 | 0 | 1 |   0 |   0 |   0 |           0 | 0                 |
   * | 0 | 0 | 0 |   0 |   0 |   0 |           0 | 0                 |
   */
  TEST_ASSERT_EQUAL_UINT32(
			   0b11101000,
			   maj32(
				0b11110000,
				0b11001100,
				0b10101010
				)
			   );
  TEST_ASSERT_EQUAL_UINT64(
			   0b11101000,
			   maj64(
				0b11110000,
				0b11001100,
				0b10101010
				)
			   );
}

TEST(sha1, sha1_f)
{
  TEST_ASSERT_EQUAL_UINT32(0b11001010,sha1_f(10,0b11110000,0b11001100,0b10101010));
  TEST_ASSERT_EQUAL_UINT32(0b10010110,sha1_f(30,0b11110000,0b11001100,0b10101010));
  TEST_ASSERT_EQUAL_UINT32(0b11101000,sha1_f(50,0b11110000,0b11001100,0b10101010));
  TEST_ASSERT_EQUAL_UINT32(0b10010110,sha1_f(70,0b11110000,0b11001100,0b10101010));
}

TEST(sha1, pad512_single_block)
{
  const char* test_str = "abc";
  uint8_t padded[64] = {0,0};
  uint64_t padlen = 0;
  pad512(3,(uint8_t*)test_str,&padlen,padded);
  TEST_ASSERT_EQUAL_UINT8(0b01100001,padded[0]); // 'a'
  TEST_ASSERT_EQUAL_UINT8(0b01100010,padded[1]); // 'b'
  TEST_ASSERT_EQUAL_UINT8(0b01100011,padded[2]); // 'c'
  TEST_ASSERT_EQUAL_UINT8(0b10000000,padded[3]); // start of padding
  unsigned int i;
  for(i=4;i<63;++i){
    TEST_ASSERT_EQUAL_UINT8(0,padded[i]); // padding
  }
  TEST_ASSERT_EQUAL_UINT8(0b11000,padded[63]); // end of padding
}
