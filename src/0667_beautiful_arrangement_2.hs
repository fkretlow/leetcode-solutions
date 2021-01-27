{-------------------------------------------------------------------------------------------------
 -
 - 667. Beautiful Arrangement II
 -
 - Given two integers n and k, you need to construct a list which contains n different positive
 - ranging from 1 to n and obeys the following requirement:
 - Suppose this list is [a1,a2,a3,...,an], then the list [|a1-a2|,|a2-a3|,...,|an-1 - an|] has
 - exactly k distinct integers.
 -
 - Produce k distinct steps from k+1 successive integers by "zig-zagging" through them, pad the
 - solution with the rest of the integers in order. O(n).
 -
 ------------------------------------------------------------------------------------------------}

data Failable a = Ok a | Error String deriving (Show)

zigzag :: (Num a, Eq a, Ord a) => a -> a -> [a]
zigzag i j
    | i == j    = [i]
    | i < j     = i : j : zigzag (i+1) (j-1)
    | otherwise = []

beautiful :: Int -> Int -> Failable [Int]
beautiful n k
    | and [n > 0, k > 0, n > k] = Ok $ take (n-k-1) [1..] ++ zigzag (n-k) n
    | otherwise                 = Error "invalid arguments"
