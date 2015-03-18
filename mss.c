int longest_increasing_sub_sequence(int *w, int n)
{
  int i,j;
  int best_len = 1;
  int lengths[n];
  for (i = 0; i < n; i++) {
    lengths[i] = 1;
  }
  for (i = 1; i < n; i++) {
    for (j = 0; j < i; j++) {
      if (w[i] > w[j] && lengths[i] <= lengths[j]) {
        lengths[i] = lengths[j] + 1;
      }
    }
    if (lengths[i] > best_len) {
      best_len = lengths[i];
    }
  }
  return best_len;
}
