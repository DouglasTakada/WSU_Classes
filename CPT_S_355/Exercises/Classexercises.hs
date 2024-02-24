module Classexercises 
   where 
--------------------------------------------------------------------------------------
{-Example 1:
  Write a function "getSeconds" that takes a list of tuples and returns a list that includes the second elements of each tuple. 
  Examples:
  getSeconds [(1,'H'),(2,'A'),(3,'S'),(4,'K'),(5,'E'),(6,'L'),(7,'L')]  --"HASKELL"
-}
-- pattern 
((x,y):xs) = [(1,'H'),(2,'A'),(3,'S'),(4,'K'),(5,'E'),(6,'L'),(7,'L')] 

getSeconds [] = []
getSeconds ((x,y):xs) = y : (getSeconds xs)


--------------------------------------------------------------------------------------
{- Example 2
   Write a function "numbers2Sum" that takes an Int list "iL" and a Int value "n", 
   and returns the ordered values from the input list that add up to less than or equal to  n.
-}

-- Examples:
l1 = numbers2Sum [1,2,3,4,5,6,7]  15   -- [1,2,3,4,5]
l2 = numbers2Sum [1,2,3,4,5,6,7]  14   --  [1,2,3,4]
l3 = numbers2Sum [1,2,3,4,5,6,7]  7   --  [1,2,3]

-- numbers2Sum [1,2,3,4,5,6,7]  7
-- 1 : (numbers2Sum [2,3,4,5,6,7]  (7-1) )
-- 1 : 2: (numbers2Sum [3,4,5,6,7]  (6-2) )
-- 1 : 2: 3:(numbers2Sum [4,5,6,7]  (4-3) )
-- 1 : 2: 3:([] )
-- [1,2,3]

numbers2Sum [] n = []
numbers2Sum  (x:xs) n | (n-x) < 0 = []
                      | otherwise = x: (numbers2Sum xs (n-x))


----------------------------------------------------------------------------------------
{- Example 3
   Write a function "groupby3" that takes a list as input and splits the list 
   into groups of "3" elements. The leftovers are included as the last group. 
-}

-- -- Examples 
-- g1 = groupby3 [1,2,3,4,5,6,7,8,9,10]     --  [ [1,2,3],[4,5,6],[7,8,9],[10]]

-- -- copylist2 [] buf = reverse buf
-- -- copylist2 (x:xs) buf = copylist2 xs (x:buf)
groupby3 list = group_helper list []
   where 
      group_helper [] [] = []
      group_helper [] buf = (reverse buf):[]
      group_helper (x:xs) buf | (length buf) == 3 = (reverse buf) : (group_helper xs (x:[]))
                              | otherwise = group_helper xs (x:buf)



-- group_helper [1,2,3,4,5,6,7,8] []
-- group_helper [2,3,4,5,6,7,8] [1]
-- group_helper [3,4,5,6,7,8] [2,1]
-- group_helper [4,5,6,7,8] [3,2,1]
-- [3,2,1]: (group_helper [5,6,7,8] [4])
-- [3,2,1]: (group_helper [5,6,7,8] [4])
-- [3,2,1]: (group_helper [6,7,8] [5,4])
-- [3,2,1]: (group_helper [7,8] [6,5,4])
-- [3,2,1]: [6,5,4] : (group_helper [7,8] [])
-- [3,2,1]: [6,5,4] : (group_helper [8] [7])
-- [3,2,1]: [6,5,4] :  (group_helper [] [8,7])
-- [3,2,1]: [6,5,4] : [8,7]:  ([])


----------------------------------------------------------------------------------------
{- Example 4
   Write a function called `myelem` that takes two lists and returns the elements from the list 
   which also appears in the second list. 
   Example:
   myelem [2,4,6] [10,6,4,3,4,5,7] returns [4,6]
-}

myelem [] ys = []
myelem (x:xs) ys | (x `elem` ys) = x:(myelem xs ys)
                 | otherwise = myelem xs ys

----------------------------------------------------------------------------------------
{- Example 5
   Write a function called `longest_list` that takes a nested list and returns the longest list in that nested list. 
   If there are more than one lists which have the longest length, return the leftmost one in the original list.  
   Example:
   longest_list [[2,4,6],[],[10,6,4,5,7],[3],[1,2,3,4],[1,2,3,4,5],[]]  returns [10,6,4,5,7]
-}
longest_list []     = error "List is empty"
longest_list [x]    = x 
longest_list (x:xs) = x `longer` (longest_list xs)
      where
           longer list1 list2 | (length list1) >= (length list2) = list1
                              | otherwise = list2





----------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------
-- How to keep track of the previous value in the list?

helper [] y = 0
helper (x:xs) y |  x == y  = 1 + (helper xs x)
                | otherwise = helper xs x
foo [] = 0
foo (x:xs) = helper xs  x

out_foo = foo [1,2,3,1,1,4,5,5,5,6,7,6,6,8,9,9]