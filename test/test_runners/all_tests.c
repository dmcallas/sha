#include "unity_fixture.h"

static void RunAllTests(void)
{
  RUN_TEST_GROUP(bit_manip);
  RUN_TEST_GROUP(sha);
  RUN_TEST_GROUP(sha1);
  RUN_TEST_GROUP(sha256);
}

int main(int argc, const char * argv[])
{
  return UnityMain(argc, argv, RunAllTests);
}
