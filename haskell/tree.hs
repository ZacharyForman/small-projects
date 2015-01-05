data BST a = Empty | Node (BST a) a (BST a)
  deriving (Show, Eq)

bstInsert :: (Ord a, Eq a) => (BST a) -> a -> (BST a)
bstInsert Empty a = Node (Empty) (a) (Empty)
bstInsert (Node l v r) n
  | n == v = Node l v r
  | n > v = Node l v (bstInsert r n)
  | n < v = Node (bstInsert l n) v r

getMin :: (Ord a, Eq a) => (BST a) -> (a, BST a)
getMin Empty = error "no tree"
getMin (Node Empty v r) = (v, r)
getMin (Node l v r) = (vv, Node ll v r)
    where (vv, ll) = getMin l

bstDelete :: (Ord a, Eq a) => (BST a) -> a -> (BST a)
bstDelete Empty a = Empty
bstDelete (Node Empty v r) x
  | x == v = r
  | x > v = Node Empty v (bstDelete r x)
  | otherwise = Node Empty v r
bstDelete (Node l v Empty) x
  | x == v = l
  | x < v = Node (bstDelete l x) v Empty
  | otherwise = Node l v Empty
bstDelete (Node l v r) x
  | x > v = Node l v (bstDelete r x)
  | x < v = Node (bstDelete l x) v r
  | x == v = Node l vv rr
    where (vv, rr) = getMin r

preOrder :: (Ord a, Eq a) => (a -> b) -> (BST a) -> [b]
preOrder f Empty = []
preOrder f (Node l n r) = [f n] ++ preOrder f l ++ preOrder f r

inOrder :: (Ord a, Eq a) => (a -> b) -> (BST a) -> [b]
inOrder f Empty = []
inOrder f (Node l n r) = inOrder f l ++ [f n] ++ inOrder f r

postOrder :: (Ord a, Eq a) => (a -> b) -> (BST a) -> [b]
postOrder f Empty = []
postOrder f (Node l n r) = postOrder f l ++ postOrder f r ++ [f n]

constructTree :: (Ord a, Eq a) => [a] -> (BST a)
constructTree [] = Empty
constructTree (p:r) = Node (constructTree (filter (< p) r)) p (constructTree (filter (> p) r))