#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(bit_manip)
{
  RUN_TEST_CASE(bit_manip, rotl32);
  RUN_TEST_CASE(bit_manip, rotr32);
}
