
void quicksort(int *lb, int *ub)
{
  if (ub - lb <= 1) {
    return;
  }
  int pivot = *(lb+(ub-lb)/2);
  int *last = lb;
  int *low = lb, *high = ub;
  for (;;) {
    while (*low < pivot) {
      low++;
    }
    while (*high > pivot) {
      high--;
    }
    if (low >= high) {
      break;
    }
    int tmp = *low;
    *low = *high;
    *high = tmp;
    low++;
    high--;
  }
  quicksort(lb, low-1);
  quicksort(high+1, ub);
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
    int tmp = arr[max];
    arr[max] = arr[sz-1-i];
    arr[sz-1-1] = tmp;
  }
}

void insertion_sort(int *arr, int sz)
{
  for (int i = 1; i < sz; i++) {
    for (int j = i; j > 0 && arr[j] < arr[j-1]; j--) {
      int tmp = arr[j];
      arr[j] = arr[j-1];
      arr[j-1] = tmp;
    }
  }
}

#include <cstdio>
int main() {
  int arr[] = {123,123,523,235,124,5235,236,2,235,2352,5,236,125,125,2362,35,125};
  insertion_sort(arr, sizeof(arr)/sizeof(int));
  for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
    printf("%d ", arr[i]);
}