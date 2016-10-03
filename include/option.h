/* Copyright (c) 2016 Christopher Woodall under the MIT LICENSE */
/**
 * @file option.h
 *
 * Implements an Option type for C++, this is inspired by Rust and similar
 * implementations by simonask, cbiffle, boost and c++17.
 *
 * @author Chris Woodall <chris@cwoodall.com>
 */

/**
 * @brief a tag type to represent creating a nothing Option.
 *
 * This makes the following code possible.
 *
 * @code
 * Option<int> always_nothing() { return Nothing(); }
 * @endcode
 */
struct Nothing {};

/**
 * @brief an Option type similar to std::optional, boost::optional, the Haskell
 *        Maybe monad and the Rust Option type.
 *
 * @code
 * Option<int> divide(int a, int b) {
 *   if (b == 0) {
 *     return Nothing();
 *   } else {
 *     return Some(a / b);
 *   }
 * }
 * @endcode
 */
template <typename T>
class Option final {
 public:
  Option() : isSomething_(false) {}

  Option(Nothing nothing) : isSomething_(false) {}

  Option(T something) : isSomething_(true), something_(something) {}

  Option(const Option<T> &other)
      : isSomething_(other.isSomething_), something_(other.something_) {}

  Option<T> &operator=(const Option<T> &other) const {
    something_ = other.something_;
    isSomething_ = other.isSomething_;

    return *this;
  }

  Option(Option &&other)
      : something_(other.something_), isSomething_(other.isSomething_) {}

  /**
   * An explicit conversion to bool, which makes boolean comparisons of the
   * Option type possible
   *
   * @return isSomething_ (true if it is something, false otherwise)
   */
  inline constexpr explicit operator bool(void) const { return isSomething_; }

  /**
   * Get the value stored inside of the Option<T> type
   *
   * @return something_;
   */
  inline constexpr T unwrap(void) const { return something_; }

  /**
   * Get the value stored inside of the Option<T> type or if it is Nothing()
   * then return
   *
   * @return something_;
   */
  inline constexpr T unwrap_or(T or_val) const {
    return (isSomething_) ? something_ : or_val;
  }

 private:
  bool isSomething_;  ///< @brief stores whether Some(T) or Nothing is stored
  T something_;       ///< @brief temporary storage for the something object
};

/**
 * Some() is a little bit of sugar. In C++ you can just return your variable
 * T and it will be sent to the Option<T> constructor, for example:
 *
 * @code
 * Option<int> foo(int bar) {
 *  return bar; // No need to create an Option<int>. Option<int>(a) will be
 *              // constructed on return.
 * }
 * @endcode
 *
 * The Some() function allows for the following to work:
 *
 * @code
 * Option<int> foo(int bar) {
 *   return Some(bar);
 * }
 * @endcode
 *
 * This can be useful for creating an Option<T> inside of a function early
 * and using it with in the function. Both forms should have similar
 * performance, but an analysis of this has not been carried out.
 *
 * @param something to wrap in an Option type
 * @return a wrapped verion of something.
 */
template <typename T>
constexpr Option<T> Some(T something) {
  return Option<T>(something);
}
