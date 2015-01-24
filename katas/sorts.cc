#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <utility>
#include <vector>

using std::swap;

int *make_list(int sz)
{
  int i = 0;
  int *ret = (int*)malloc(sz * sizeof(int));
  for(i = 0; i < sz; i++) {
    ret[i] = rand() % (sz+20);
  }
  return ret;
}

timespec diff(timespec start, timespec end)
{
  timespec temp;
  if ((end.tv_nsec-start.tv_nsec)<0) {
    temp.tv_sec = end.tv_sec-start.tv_sec-1;
    temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec-start.tv_sec;
    temp.tv_nsec = end.tv_nsec-start.tv_nsec;
  }
  return temp;
}

void std_sort(int *arr, int sz)
{
  std::sort(arr, arr+sz);
}

void quicksort(int *arr, int lb, int ub)
{
  if (ub - lb < 1) {
    return;
  }
  int last = lb;
  for (int i = lb+1; i < ub; i++) {
    if (arr[i] < arr[lb]) {
      last++;
      swap(arr[i], arr[last]);
    }
  }
  swap(arr[lb], arr[last]);
  quicksort(arr, lb, last);
  quicksort(arr, last+1, ub);
}

void quicksort(int *arr, int sz)
{
  quicksort(arr, 0, sz);
}

void selection_sort(int *arr, int sz)
{
  for (int i = 0; i < sz; i++) {
    int max = 0;
    for (int j = 0; j < sz-i; j++) {
      if (arr[j] > arr[max]) {
        max = j;
      }
    }
    swap(arr[max], arr[sz-1-i]);
  }
}

void insertion_sort(int *arr, int sz)
{
  for (int i = 1; i < sz; i++) {
    for (int j = i; j > 0 && arr[j] < arr[j-1]; j--) {
      swap(arr[j], arr[j-1]);
    }
  }
}

void bubble_sort(int *arr, int sz)
{
  for (int i = 0; i < sz; i++) {
    for (int j = i; j < sz; j++) {
      if (arr[i] > arr[j]) {
        swap(arr[i], arr[j]);
      }
    }
  }
}

void siftdown(int *arr, int sz, int i)
{
  for(;;) {
      int spos = i;
      if (2*i < sz && arr[spos] < arr[2*i]) {
        spos = 2*i;
      }
      if (2*i+1 < sz && arr[spos] < arr[2*i+1]) {
        spos = 2*i+1;
      }
      if (spos == i) {
        // Done heapifying
        break;
      }
      swap(arr[i], arr[spos]);
      i = spos;
    }
}

void heap_sort(int *arr, int sz)
{
  // Heapify the array
  for (int i = sz/2; i >= 0; i--) {
    siftdown(arr, sz, i);
  }
  // Perform selection sort
  for (int i = sz-1; i >= 0; i--) {
    // Extract the maximum
    swap(arr[0], arr[i]);
    siftdown(arr, i, 0);
  }
}

int main(int argc, char **argv)
{
  srand(time(NULL));

  void (*sorts[])(int*,int) = {bubble_sort,
                               selection_sort,
                               insertion_sort,
                               heap_sort,
                               quicksort,
                               std_sort};

  const char *names[] = {"bubble_sort",
                         "selection_sort",
                         "insertion_sort",
                         "heap_sort",
                         "quicksort",
                         "std_sort"};

  std::vector< std::vector<int> > sizes
               = {{1,2,5,10,50,100,500,1000,5000,10000,50000},
                  {1,2,5,10,50,100,500,1000,5000,10000,50000},
                  {1,2,5,10,50,100,500,1000,5000,10000,50000},
                  {1,2,5,10,50,100,500,1000,5000,10000,50000,
                   100000,500000,1000000,5000000,10000000},
                  {1,2,5,10,50,100,500,1000,5000,10000,50000,
                   100000,500000,1000000,5000000,10000000},
                  {1,2,5,10,50,100,500,1000,5000,10000,50000,
                   100000,500000,1000000,5000000,10000000}};
  

  auto test = [=](int i, int j) {
    int *arr = make_list(sizes[i][j]);
    timespec t0;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t0);
    sorts[i](arr, sizes[i][j]);
    timespec t1;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
    timespec dt = diff(t0, t1);
    if (!std::is_sorted(arr, arr+sizes[i][j])) {
      printf("%14s\t%8d\tUNSORTED ARRAY\n", names[i], sizes[i][j]);
    } else {
      printf("%14s\t%8d\t%.3ld%.9ld\n", names[i], sizes[i][j], dt.tv_sec, dt.tv_nsec);
    }
  };

  for (int i = 0; i < sizes.size(); i++) {
    for (int j = 0; j < sizes[i].size(); j++) {
      if (argc < 2 || !strcmp(argv[1], names[i])) {
        test(i,j);
      }
    }
  }

}