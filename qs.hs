qs :: Ord arr => [arr] -> [arr]
qs arr
  | length arr <= 1 = arr
  | otherwise = qs (filter (< head arr) arr) ++ filter (== head arr) arr ++ qs (filter (> head arr) arr)