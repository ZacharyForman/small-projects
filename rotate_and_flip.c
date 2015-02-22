#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void solve(int *const arr, const int s, int c) {
  int v;
  for (;c&&(s-c);) {
    v = rand()%s;
    c += arr[v];
    arr[v] = !arr[v];
    c -= arr[v];
  }
}

int main(int argc, char **argv)
{
  int i;
  int c = 0;
  int n = 0;
  c = 0;
  if (argc < 2) {
    printf("Usage: %s sidelength\n", argv[0]);
    return 0;
  }
  n = atoi(argv[1]);
  srand(time(NULL));

  int *arr = (int*)calloc(n*n, sizeof(int));
  for (i = 0; i < n*n; i++) {
    arr[i] = rand()%2;
    c += !arr[i];
  }


  solve(arr, n*n, c);


  for (i = 0; i < n*n; i++) {
    printf("%d", arr[i]);
  }
}