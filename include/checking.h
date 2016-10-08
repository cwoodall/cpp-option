#ifndef CJW_CHECKING_H_
#define CJW_CHECKING_H_
#include <cassert>

#ifdef __EXCEPTIONS
#include <exception>
#endif  // __EXCEPTIONS

struct CheckingPolicy {
  static constexpr bool check(bool value) { return false; };
};

struct LaxCheckingPolicy : CheckingPolicy {
  static constexpr bool check(bool value) { return true; }
};

struct AssertCheckingPolicy : CheckingPolicy {
  static bool check(bool value) noexcept {
    assert(value);
    return true;
  }
};

#ifdef __EXCEPTIONS
class OptionInvalidAccessException : std::exception {
  virtual const char* what() const throw() {
    return "Invalid access to Option with Nothing in it";
  }
};

struct ThrowCheckingPolicy : CheckingPolicy {
  static bool check(bool value) {
    if (!value) {
      OptionInvalidAccessException ex;
      throw ex;
    }
    return value;
  }
};

#endif  // __EXCEPTIONS

#endif  // CJW_CHECKING_H_
