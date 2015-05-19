#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(bit_manip)
{
  RUN_TEST_CASE(bit_manip, rotl32);
  RUN_TEST_CASE(bit_manip, rotr32);
  RUN_TEST_CASE(bit_manip, rotl64);
  RUN_TEST_CASE(bit_manip, rotr64);
  RUN_TEST_CASE(bit_manip, bytes_to_uint32);
}
