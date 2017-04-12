#!/usr/bin/env python3
from random import shuffle

def Arrays(n):
  """ Returns two distinct sorted arrays of size n and n+1."""
  arr = [x for x in range(2 * n +1)]
  shuffle(arr)
  return sorted(arr[:n]), sorted(arr[n:])

def FindMedian(a1, a2):
  """ Finds the median of two distinct sorted arrays, a1 and a2."""
  m = BinarySearchForMedian(a1, a2)
  if m is not None: return a1[m]
  m = BinarySearchForMedian(a2, a1)
  if m is not None: return a2[m]

def BinarySearchForMedian(a1, a2):
  """ Assuming the median of (a1 U a2) is in a1, find it by binary searching.
  Returns None when the median is not in a1. """
  low = 0
  high = len(a1) - 1
  total_less = (len(a1)+len(a2))//2
  while low <= high:
    mid = (low+high)//2
    needed_from_a2 = total_less - mid
    # Too many elements from a1 -> drop the upper half.
    if needed_from_a2 < 0: high = mid - 1
    # a1 strictly less than a2, and is the larger of the two.
    elif needed_from_a2 == 0 and a1[mid] < a2[0]: return mid
    # we need all of a2, and it works.
    elif needed_from_a2 == len(a2) and a2[-1] < a1[mid]: return mid
    # we need all of a2, and it doesn't -> drop the lower half.
    elif needed_from_a2 == len(a2) and a2[-1] > a1[mid]: low = mid + 1
    # we need too much from a2 -> drop the lower half.
    elif needed_from_a2 > len(a2): low = mid + 1
    # We're the median.
    elif a2[needed_from_a2 - 1] < a1[mid] < a2[needed_from_a2]: return mid
    # We're too high, drop the upper half.
    elif a2[needed_from_a2] < a1[mid]: high = mid - 1
    # We're too low, drop the lower half.
    elif a2[needed_from_a2 - 1] > a1[mid]: low = mid + 1

for i in range(1, 1000):
  if FindMedian(*Arrays(i)) != i: print("Failed at ", i)
print("Otherwise successful")
