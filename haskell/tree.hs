data BST a = Empty | Node (BST a) a (BST a)
  deriving (Show, Eq)

bstInsert :: (Ord a, Eq a) => (BST a) -> a -> (BST a)
bstInsert Empty a = Node (Empty) (a) (Empty)
bstInsert (Node l v r) n
  | n == v = Node l v r
  | n > v = Node l v (bstInsert r n)
  | n < v = Node (bstInsert l n) v r

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