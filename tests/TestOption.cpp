#include "CppUTest/TestHarness.h"
#include "checking.h"
#include "option.h"

template class Option<int>;

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

// clang-format off

TEST_GROUP(TestOption){
};

TEST(TestOption, TestOptionWithNothing) {
  Option<int> uut = Nothing();
  CHECK(uut.is_nothing());

  Option<int> uut1 = {};
  CHECK(uut1.is_nothing());

  Option<int> uut2;
  CHECK(uut2.is_nothing());
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

TEST(TestOption, TestOptionSomeInitialize) {
  Option<int> uut = Some(1002);

  CHECK(uut.is_something());
}

TEST(TestOption, TestCopyTrival) {
  Option<int> uut1 = 100;
  Option<int> uut2;

  uut2 = uut1;

  Option<int> uut3(uut1);

  CHECK(uut1.is_something())
  CHECK(uut2.is_something())
  CHECK(uut3.is_something())

  CHECK_EQUAL(uut1.unwrap_unsafe(), uut2.unwrap_unsafe())
  CHECK_EQUAL(uut1.unwrap_unsafe(), uut3.unwrap_unsafe())

}

TEST(TestOption, TestMove) {
  Option<int> uut1 = 100;
  Option<int> uut2(std::move(uut1));

  CHECK(uut1.is_nothing())
  CHECK(uut2.is_something())

  CHECK_THROWS(OptionInvalidAccessException, uut1.unwrap<ThrowCheckingPolicy>());
  CHECK_EQUAL(100, uut2.unwrap())
}

TEST(TestOption, TestMovePointer) {
  int foo = 100;
  Option<int *> uut1 = &foo;
  Option<int *> uut2(std::move(uut1));

  CHECK(uut1.is_nothing())
  CHECK(uut2.is_something())

  CHECK_THROWS(OptionInvalidAccessException, uut1.unwrap<ThrowCheckingPolicy>());
  CHECK_EQUAL(&foo, uut2.unwrap())
  CHECK_EQUAL(foo, *uut2.unwrap())
}

TEST(TestOption, TestMoveOperatorPointer) {
  int foo = 100;
  Option<int *> uut1 = &foo;
  Option<int *> uut2;

  uut2 = std::move(uut1);

  CHECK_THROWS(OptionInvalidAccessException, uut1.unwrap<ThrowCheckingPolicy>());

  CHECK_EQUAL(&foo, uut2.unwrap())
  CHECK_EQUAL(foo, *uut2.unwrap())
}
// clang-format on
