fact :: Integer -> Integer
fact n 
  | n == 0 = 1
  | n < 0 = - fact (- n)
  | otherwise = n * (fact (n - 1))