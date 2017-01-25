#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(sha1)
{
  RUN_TEST_CASE(sha1, sha1_with_short_input);
  RUN_TEST_CASE(sha1, sha1_with_long_input);
  RUN_TEST_CASE(sha1, sha1_string);
}
