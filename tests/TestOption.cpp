#include "CppUTest/TestHarness.h"
#include "option.h"

// clang-format off

TEST_GROUP(TestOption){
};

TEST(TestOption, TestOptionWithNothing) {
  Option<int> uut = Nothing();
  CHECK(!uut.is_something());

  Option<int> uut1 = {};
  CHECK(!uut1.is_something());

  Option<int> uut2;
  CHECK(!uut2.is_something());
}

TEST(TestOption, TestOptionWithSomeValue) {
  Option<int> uut = 1;
  CHECK(uut.is_something());

  Option<int> uut1(2);
  CHECK(uut1.is_something());
}

TEST(TestOption, TestOptionUnwrapWithValue) {
  Option<int> uut = 1;
  CHECK(uut.is_something());

  Option<int> uut1(2);
  CHECK(uut.is_something());
}

// clang-format on
