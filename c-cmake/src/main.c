#include <stdio.h>

int main() {
  int x = 5;
  {
    int x = 6;
    printf("x = %d\n", x);
  }
  printf("x = %d\n", x);
  return 0;
}
