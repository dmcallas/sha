#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(sha1)
{
  RUN_TEST_CASE(sha1, ch32_and_ch64);
  RUN_TEST_CASE(sha1, parity32);
  RUN_TEST_CASE(sha1, maj32_and_maj64);
  RUN_TEST_CASE(sha1, sha1_f);
  RUN_TEST_CASE(sha1, pad512_single_block);
}
