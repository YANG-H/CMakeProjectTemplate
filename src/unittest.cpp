// the entry for unit tests
#include <gtest/gtest.h>

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  // testing::FLAGS_gtest_throw_on_failure = true;
  // testing::FLAGS_gtest_catch_exceptions = false;
  return RUN_ALL_TESTS();
}