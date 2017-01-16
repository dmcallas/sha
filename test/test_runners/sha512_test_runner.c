#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(sha512)
{
  RUN_TEST_CASE(sha512, sha512_with_short_input);
  RUN_TEST_CASE(sha512, sha512_with_long_input);
  RUN_TEST_CASE(sha512, sha512_string);
}
