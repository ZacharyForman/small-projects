#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_sub_array(int *arr, int sz) {
  int i;
  int max = INT_MIN;
  int val = 0;
  for (i = 0; i < sz; i++) {
    int tval = val + arr[i];
    if (tval > max) {
      max = tval;
    }
    if (tval > 0) {
      val = val + arr[i];
    } else {
      val = 0;
    }
  }
  return max;
}

int main(int argc, char **argv)
{
  int i;
  int x[argc-1];
  for (i = 1; i < argc; i++) {
    x[i-1] = atoi(argv[i]);
  }

  printf("%d\n", max_sub_array(x, argc-1));
}