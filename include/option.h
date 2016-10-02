struct Nothing {};
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

  inline constexpr operator bool(void) const { return isSomething_; }
  inline constexpr T unwrap(void) const { return something_; }
  inline constexpr T unwrap_or(T or_val) const {
    return (isSomething_) ? something_ : or_val;
  }

 private:
  bool isSomething_;
  T something_;
};

template <typename T>
Option<T> Some(T something) {
  return Option<T>(something);
}

template <typename T>
Option<T> None() {
  return Nothing();
}
