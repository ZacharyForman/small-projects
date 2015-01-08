fib'' :: Int -> Int
fib'' n
  | n == 0 = 1
  | n == 1 = 1
  | otherwise = (fib'' (n - 1)) + (fib'' (n - 2))

_fib' :: Int -> Int -> Int -> Int
_fib' t n n1
  | t == 0 = n + n1
  | otherwise = _fib' (t-1) (n+n1) (n)

fib' :: Int -> Int
fib' t = _fib' t 0 1

_fib :: Integer -> Integer -> Integer -> Integer
_fib t n n1
  | t == 0 = n + n1
  | otherwise = _fib (t-1) (n+n1) (n)

fib :: Integer -> Integer
fib t = _fib t 0 1