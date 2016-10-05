#ifndef CJW_CHECKING_H_
#define CJW_CHECKING_H_
#include <cassert>

struct CheckingPolicy {
  constexpr bool check(bool value) { return false; };
};

struct LaxCheckingPolicy : CheckingPolicy {
  static constexpr bool check(bool value) { return true; }
};

struct AssertCheckingPolicy : CheckingPolicy {
  static bool check(bool value) {
    assert(value);
    return true;
  }
};

#endif  // CJW_CHECKING_H_
