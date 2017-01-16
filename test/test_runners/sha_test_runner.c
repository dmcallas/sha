#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(sha)
{
  RUN_TEST_CASE(sha, ch32_and_ch64);
  RUN_TEST_CASE(sha, parity32);
  RUN_TEST_CASE(sha, maj32_and_maj64);
  RUN_TEST_CASE(sha, pad512_single_block);
}
