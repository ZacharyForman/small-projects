head' :: [a] -> a
head' (a:_) = a
head' [] = error "empty list"

map' :: (a -> b) -> [a] -> [b]
map' f [] = []
map' f (a:b) = [f a] ++ map f b

reduce' :: (b -> a -> b) -> [a] -> b -> b
reduce' f (l:r) b
  | length r == 0 = f b l
  | otherwise = reduce' (f) (r) (f b l)
reduce' _ [] _ = error "empty list"