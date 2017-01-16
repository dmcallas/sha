#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(sha256)
{
  RUN_TEST_CASE(sha256, sha256_with_short_input);
  RUN_TEST_CASE(sha256, sha256_with_long_input);
  RUN_TEST_CASE(sha256, sha256_string);
}
