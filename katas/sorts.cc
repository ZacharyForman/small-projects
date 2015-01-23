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

void bubble_sort(int *arr, int sz)
{
  for (int i = 0; i < sz; i++) {
    for (int j = i; J < sz; j++) {
      if (arr[i] < arr[j]) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
      }
    }
  }
}