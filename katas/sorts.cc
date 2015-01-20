
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