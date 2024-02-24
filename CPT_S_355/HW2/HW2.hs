-- CptS 355 - Spring 2023 -- Homework2 - Haskell
-- Name:
-- Collaborators: 

module HW2
     where

{- P1 - remove_every, remove_every_tail  -}

-- (a) remove_every – 7%

remove_every n []  = [] 
remove_every n lst = remove_helper n lst n 
  where
     remove_helper _ [] _ = []
     remove_helper 0 [x] k = []
     remove_helper n [x] k = [x]

     remove_helper 0 (x:xs) k = (remove_helper k xs k) 
     remove_helper n (x:xs) k = x:(remove_helper (n-1) xs k)

{-
1. Both the recrusive calls to remove_helper was missing the last argument k
2. The there were missing cases that did not write about when there is one element left
     and what to do if the counter is either 0 or not zero
-}

-- (b) remove_every_tail –  10%

remove_every_tail 0 _  = [] 
remove_every_tail n lst = remove_every_tail_helper n lst n []
  where
     remove_every_tail_helper _ [] k acc = acc
     remove_every_tail_helper 0 [x] k acc = acc
     remove_every_tail_helper n [x] k acc = (remove_every_tail_helper (n-1) [] k (acc++[x]))

     remove_every_tail_helper 0 (x:xs) k acc = (remove_every_tail_helper k xs k acc) 
     remove_every_tail_helper n (x:xs) k acc = (remove_every_tail_helper (n-1) xs k (acc++[x]))

------------------------------------------------------
{- P2  get_outof_range and count_outof_range  -}

-- (a) get_outof_range – 6%

get_outof_range _ _ [] = []
get_outof_range v1 v2 xs = foldr (\value acc-> if value >= v1 && value <= v2 then acc else value : acc) [] xs

-- (b) count_outof_range – 10%

count_outof_range _ _ [] = 0
count_outof_range v1 v2 xs = foldr (\x acc -> if x < v1 || x > v2 then acc + 1 else acc) 0 (foldr (++) [] xs)


------------------------------------------------------
{- P3  find_routes - 10% -}

-- routes = [ 
--     ("Lentil", ["Chinook", "Orchard", "Valley", "Emerald","Providence", "Stadium",  
--       "Main", "Arbor", "Sunnyside", "Fountain", "Crestview", "Wheatland", "Walmart",  
--       "Bishop", "Derby", "Dilke"]),  
--     ("Wheat",["Chinook", "Orchard", "Valley", "Maple","Aspen", "TerreView", "Clay",  
--      "Dismores", "Martin", "Bishop", "Walmart", "PorchLight", "Campus"]),  
--     ("Silver",["TransferStation", "PorchLight", "Stadium", "Bishop","Walmart",  
--      "Outlet", "RockeyWay","Main"]), 
--     ("Blue",["TransferStation", "State", "Larry", "TerreView","Grand", "TacoBell",  
--      "Chinook", "Library"]), 
--     ("Gray",["TransferStation", "Wawawai", "Main", "Sunnyside","Crestview",  
--      "CityHall", "Stadium", "Colorado"]), 
--     ("Coffee",["TransferStation", "Grand", "Main", "Visitor","Stadium", "Spark",  
--      "CUB"]) 
--    ] 

find_routes _ [] = []
find_routes stop xs = foldr (\(x, xs) acc -> if elem stop xs then x : acc else acc) [] xs

------------------------------------------------------
{- P4  add_lengths and add_nested_lengths -}

-- (a) add_lengths - 6%

data LengthUnit =  INCH  Int | FOOT  Int | YARD  Int 
                   deriving (Show, Read, Eq)


add_lengths (INCH x) (INCH y) = INCH (x + y)
add_lengths (FOOT x) (INCH y) = INCH (12*x + y)
add_lengths (INCH x) (FOOT y) = INCH (x + 12*y)
add_lengths (YARD x) (INCH y) = INCH (36*x + y)
add_lengths (INCH x) (YARD y) = INCH (x + 36*y)

add_lengths (FOOT x) (FOOT y) = INCH (12*x + 12*y)
add_lengths (FOOT x) (YARD y) = INCH (12*x + 36*y)
add_lengths (YARD x) (FOOT y) = INCH (36*x + 12*y)

add_lengths (YARD x) (YARD y) = INCH (36*x + 36*y)

-- (b) add_nested_lengths - 10%

add_nested_lengths [] = (INCH 0)
add_nested_lengths xs = foldr (add_lengths) (INCH 0) (foldr (++) [] xs)

------------------------------------------------------
{- P5 sum_tree and create_sumtree -}

-- (a) sum_tree - 8%

data Tree a = NULL | LEAF a | NODE a  (Tree a)  (Tree a)  
              deriving (Show, Read, Eq)

sum_tree (NULL) = 0
sum_tree (LEAF x) = x
sum_tree (NODE x left right) = x + sum_tree left + sum_tree right

-- (b) create_sumtree - 10%

create_sumtree (NULL) = (NULL)
create_sumtree (LEAF x) = LEAF x
create_sumtree (NODE x left right) = NODE (x + sum_tree left + sum_tree right) (create_sumtree left) (create_sumtree right)
  where
     sum_tree (NULL) = 0
     sum_tree (LEAF x) = x
     sum_tree (NODE x left right) = (x + (sum_tree left) + (sum_tree right))

------------------------------------------------------
{- P6 list_tree - 16% -}

data ListTree a = LEAFs [a] | NODEs [(ListTree a)] 
                  deriving (Show, Read, Eq)

list_tree f base (NODEs []) = base
list_tree f base (LEAFs []) = base
list_tree f base (LEAFs xs) = foldl (f) base xs
list_tree f base (NODEs [x]) = list_tree f base x
list_tree f base (NODEs (x:xs)) = list_tree f (list_tree f base x) (NODEs xs)

-- Tree examples - 4%
-- INCLUDE YOUR TREE EXAMPLES HERE

--myTree1 = (NODE 1 (NODE 2 (NODE 3 (NODE 4 (NODE 5 (LEAF 6) (LEAF 7)) NULL ) NULL) (LEAF 4)) (NODE 5 (LEAF 6) (LEAF 7)))
--myTree2 = (NODE 7 NULL (NODE 2 (NODE 3 (NODE 4 (NODE 5 (LEAF 6) (LEAF 7)) NULL ) NULL) (LEAF 4)))

-- Assignment rules 3%