#include "CppUTest/TestHarness.h"
#include "checking.h"
#include "option.h"

template class Option<int>;

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
  if (uut) {
    CHECK_EQUAL(uut.unwrap(), 1);
  }
}

TEST(TestOption, TestOptionUnsafeUnwrapWithValue) {
  Option<int> uut = 1;
  if (uut) {
    CHECK_EQUAL(uut.unwrap_unsafe(), 1);
  }
}

TEST(TestOption, TestOptionUnwrapOrWithValue) {
  Option<int> uut = 1;
  if (uut) {
    CHECK_EQUAL(uut.unwrap_or(-1), 1);
  } else {
    FAIL("INVALID");
  }

  Option<int> uut1 = Nothing();
  if (!uut1) {
    CHECK_EQUAL(uut.unwrap_or(-1), 1);
  } else {
    FAIL("INVALID");
  }
}

class SpyCheckingPolicy : CheckingPolicy {
public:
  static int times_failed;
  static bool check(bool a) {
    if (!a) {
      times_failed += 1;
    }
    return a;
  }
};

int SpyCheckingPolicy::times_failed = 0;

#include <exception>

class OptionInvalidAccessException : std::exception {
  virtual const char* what() const throw() {
    return "Invalid access to Option with Nothing in it";
  }
};

class ThrowCheckingPolicy : CheckingPolicy {
public:
  static bool check(bool a) {

    if (!a) {
      OptionInvalidAccessException ex;
      throw ex;
    }
    return a;
  }
};

TEST(TestOption, TestOptionUnwrapWithCustomCheckingPolicy) {
  Option<int> uut = Nothing();

  uut.unwrap<SpyCheckingPolicy>();
  CHECK_EQUAL(SpyCheckingPolicy::times_failed, 1);

  uut.unwrap<SpyCheckingPolicy>();
  CHECK_EQUAL(SpyCheckingPolicy::times_failed, 2);

}

TEST(TestOption, TestOptionUnwrapWithThrowCheckingPolicy) {
  Option<int> uut = Nothing();

  CHECK_THROWS(OptionInvalidAccessException, uut.unwrap<ThrowCheckingPolicy>());  
}

// clang-format on
