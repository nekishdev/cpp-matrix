#include "gtest/gtest.h"

#include <stdexcept>

static void throwing_func() {
  throw std::logic_error("some exception");
}

TEST(something, test_abi) {
  EXPECT_THROW(throwing_func(), std::logic_error);
}
