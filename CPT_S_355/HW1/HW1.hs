-- CptS 355 - Spring 2023 -- Homework1 - Haskell
-- Name: Douglas Takada
-- Collaborators: 


{---Important Rules
     No use of importing libraries
     Generate atleast two test cases for each function
     idea for test cases: domain of input, maximum, minimum, inside/outside boundaries, typical values, error values
     With auxiliary functions, make them local functions (inside let..in or where block) LOSE POINTS if helper function not defined inside Local Scope 
     Proper indentation and good programming style for points
-}

module HW1
     where

{-
     Method: If at end of list return 0, otherwise keep going through list.
     If current value equal to value we are looking for add one to the value we are returning.
-}
-- P1(a) count ;  6%

count :: (Eq t1) => t1 -> [t1] -> Int
count _ [] = 0
count value (x:xs) | (value == x) = 1 + count value xs
                   | otherwise = count value xs

{-
     Method: If first list empty return empty list
     If second list empty return first list
     while not at end of list keep going throogh list
     If current value not inside first list inside second list add value to returning list
     otherwise go to next iteration of list until at the end.
-}
-- P1(b) diff ;  6%

diff ::(Eq t1) => [t1] -> [t1] -> [t1]
diff a b | (a == []) = []
         | (b == []) = a
diff [x] (y:ys) | (count x (y:ys) == 0) = x:[]
                | otherwise = []
diff (x:xs) (y:ys) | ((count x (y:ys)) == 0) = x : diff xs (y:ys)
                   | otherwise = diff xs (y:ys)
                   

{-
     Method: If first list empty return empty list
     If second list empty return first list
     while not at end of list keep going throogh list
     If the number of the current values in first list is more than second list, add value to returning list
     otherwise go to next iteration of list until at the end.
-}
-- P1(c) bag_diff ; 8%

bag_diff :: Eq t1 => [t1] -> [t1] -> [t1]
bag_diff a b | (a == []) = []
             | (b == []) = a
bag_diff [x] l2 | ((count x l2) == 0) = x:[]
                | otherwise = []
bag_diff (x:xs) l2 | ((1 + count x xs) > count x l2) = x : bag_diff xs l2
                   | otherwise = bag_diff xs l2

{-
     Method: calls helper function in local scope so we can keep track of original iteration
     if the indexing value is 0 or 1 return every element in list
     if indexing value is 0 include it in returning list and reset indexing value
     keep going until end of list
-}
-- P2  everyN ; 10%

--The instructions didn't specify what should happen if given the input 0 with a list.
--so I just made it so it will print out every element.

everyN :: (Eq t1, Num t1) => [t2]-> t1 -> [t2]
everyN iL n = everyNHelper iL n n
     where 
          everyNHelper [] y z = []
          everyNHelper (x:xs) y z | (z == 0) = (x:xs)
          everyNHelper (x:xs) y z | (y == 1) = x : everyNHelper xs z z
                                  | otherwise = everyNHelper xs (y-1) z

{-
     Method: calls helper function in local scope so we can keep track of current index
     if the indexing value equal to index value in current tuple add it to list
     otherwise add 0 to list and keep going through list and adding 1 to list index everytime

-}
-- P3(a) make_sparse ; 15%

make_sparse :: (Eq t1, Num t1)=> [(t1,t1)] -> [t1]
make_sparse [] = []
make_sparse l1 = make_sparse_helper l1 0
     where
          make_sparse_helper [] _ = []
          make_sparse_helper ((x,y):xs) n | (x == n) = y : make_sparse_helper xs (n+1)
                                          | otherwise = 0 : make_sparse_helper ((x,y):xs) (n+1)

{-
     Method: calls helper function in local scope so we can keep track of original iteration
     if value in list is not 0 then add a tuple to returning list with the value and the index it was at
     otherwise keep going until you get to end of list
-}
-- P3(b) compress ; 15%

compress :: (Eq t1, Num t1)=> [t1] -> [(t1,t1)]
compress [] = []
compress l1 = compress_helper l1 0
     where 
          compress_helper [] _ = []
          compress_helper [x] n    | (x /= 0) = (n, x) : []
          compress_helper (x:xs) n | (x /= 0) = (n, x) : compress_helper xs (n+1)
                                   | otherwise = compress_helper xs (n+1)

{-
     Method: calls helper function in local scope so we can keep track of the new sum
     at every index add the previous value to the current value and add that to new list
     until we are at end of list keep doing that
     keep going until end of list
-}
-- P4 added_sums ; 8%

added_sums  :: (Num t1) => [t1] -> [t1]
added_sums [] = []
added_sums l1 = added_sums_helper l1 0
     where 
          added_sums_helper [x] n = (x + n) : []
          added_sums_helper (x:xs) n = (x + n) : added_sums_helper xs (n + x)

{-
     Method: Checks if the element we are looking for is inside the second part of the tuple within the list
     If it is then add the first value of the tuple to the returning list
     Keep going until we get to the end of the list
-}
-- P5 find_routes ; 8%

find_routes :: (Eq t1) => t1 -> [(t1,[t1])] -> [t1]
find_routes _ [] = []
find_routes bus_stop ((x,(y:ys)):[]) | elem bus_stop (y:ys) = x : []
                                     | otherwise = []
find_routes bus_stop ((x,(y:ys)):xs) | elem bus_stop (y:ys) = x : find_routes bus_stop xs
                                     | otherwise = find_routes bus_stop xs

{-
     Method: calls helper function in local scope so we can keep track of the index and the sum.
     IF the current sum is less than the limit sum then add it to the nested list and go to the next element
     If the next element make the new sum greaer than the limit sum don't add it and end that list and
     create new list and reset sum to 0 and add index value. Keep going until at end of list
-}
-- P6 group_sum ; 15% 

group_sum :: (Ord t1, Num t1) => [t1] -> t1 -> [[t1]]
group_sum [] _ = []
group_sum [_] 0 = []
group_sum iL n = group_sum_helper iL [] n 0 0
     where
          group_sum_helper [] [] n k sum = []
          group_sum_helper [] sL n k sum = (reverse sL) : []
          group_sum_helper (x:xs) sL n k sum | (x + sum) > (n *2^k) = (reverse sL) : group_sum_helper (x:xs) [] n (k+1) 0
                                             | otherwise = group_sum_helper xs (x:sL) n k (sum + x)
-- Assignment rules ; 3%

-- Your own tests; please add your tests to the HW1Tests.hs file ; 6%



