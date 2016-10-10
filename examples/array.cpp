#include <stdio.h>
#include <memory>
#include "../include/option.h"

template <typename T, size_t S>
struct Array {
  T buf[S];

  Option<T> operator[](size_t i) {
    if (i < S) {
      return Some(buf[i]);
    } else {
      return {};
    }
  }
};

int main() {
  Array<int, 4> foo = {1, 2, 3, 4};

  for (int i = 0; i < 10; i++) {
    auto bar = foo[i];
    if (bar) {
      auto baz = bar.unwrap();
      printf("%d: %d\n", i, baz);
    } else {
      printf("%d: out of range\n", i);
    }
  }
  return 0;
}
