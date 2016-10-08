#include <stdio.h>
#include "../include/option.h"

Option<int> divide(int a, int b) {
  if (b == 0) {
    return Nothing();
  } else {
    return Some(a / b);
  }
}

int main() {
  auto a = divide(100, 0);

  if (a) {
    printf("%d\n", a.unwrap());
  } else {
    a.unwrap_or(0);
    printf("mow\n");
  }

  Option<int> foo({});

  foo.unwrap<LaxCheckingPolicy>();
  return 0;
}
