#include <stdio.h>
#include "option.h"

Option<int> divide(int a, int b) {
  if (b == 0) {
    return Nothing();
  } else {
    return Some(a / b);
  }
}

int main() {
  auto a = divide(100, 2);

  if (a) {
    printf("%d\n", a.unwrap());
  } else {
    printf("mow\n");
  }

  return 0;
}
