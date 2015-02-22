#include <cstdio>
void fizzbuzz(int n)
{
  for (int i = 1; i <= n; i++ ) {
    if (i % 3 == 0) {
      printf("%s", "fizz");
    }
    if (i % 5 == 0) {
      printf("%s", "buzz");
    } else if (i % 3) {
      printf("%d", i);
    }
    printf("\n");
  }
}
//t = 2 minutes.

#include <cstdio>
void fizzbuzz(int n)
{
  for (int i = 1; i <= n; i++) {
    if (i%5==0 && i%3 == 0) {
      printf("fizzbuzz\n");
    } else if (i % 5 == 0) {
      printf("fizz\n");
    } else if (i% 3 == 0) {
      printf("buzz\n");
    } else {
      printf("%d\n", i);
    }
  }
}
// t = 1:30