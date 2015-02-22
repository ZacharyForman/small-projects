maxSubArray' :: (Num a, Ord a) => [a] -> a -> a -> a
maxSubArray' [] v m = m
maxSubArray' (x:y) v m
  | (x + v) <= 0 = maxSubArray' y 0 m
  | (x + v) > 0 = maxSubArray' y (x + v) (max (x + v) m)


maxSubArray :: (Num a, Ord a) => [a] -> a
maxSubArray (x:y) = maxSubArray' y 0 x
