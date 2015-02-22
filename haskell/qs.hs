qs :: Ord xs => [xs] -> [xs]
qs xs
  | length xs <= 1 = xs
  | otherwise = 
    qs (filter (< head xs) xs) 
    ++ filter (== head xs) xs 
    ++ qs (filter (> head xs) xs)