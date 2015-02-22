#include <utility>

template<typename T>
void siftdown(T *arr, int p, int sz)
{
  for (;;) {
    int max = p;
    if (2*p+1 < sz && arr[2*p+1] > arr[max]) {
      max = 2*p+1;
    }
    if (2*p+2 < sz && arr[2*p+2] > arr[max]) {
      max = 2*p+2;
    }
    if (max == p) {
      return;
    }
    swap(arr[max], arr[p]);
    p = max;
  }
}

template<typename T>
void heapsort(T *arr, int sz)
{
  // Heapify
  for (int i = sz/2; i >= 0; i--) {
    siftdown(arr, i, sz);
  }
  // Selection sort
  for (int i = sz-1; i > 0; i--) {
    swap(arr[0], arr[i]);
    siftdown(arr, 0, i);
  }
}