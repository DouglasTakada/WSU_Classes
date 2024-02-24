-- CptS 355 - Lab 1 (Haskell) - Spring 2023
-- Name: 


module Lab1
     where


-- 1.insert

isNegative n | n < 0     = True
             | otherwise = False


insert :: (Ord t1, Num t1) => t1 -> t2 -> [t2] -> [t2]
insert 0 item [] = [item]
insert n item [] = []
insert n item (x:xs) | isNegative n = error "index cannot be negetive"
                     | (n==0) =  item : x :xs
                     | otherwise = x: (insert (n-1) item xs)
-- 
-- 2. insertEvery

insertEveryHelper :: (Eq t, Num t) => t -> a -> [a] -> t-> [a] 
insertEveryHelper 0 item [] k = [item]
insertEveryHelper n item [] k = []
insertEveryHelper n item (x:xs) k
                     | (k == 0) = item : (insertEveryHelper k item xs k)
                     | (n == 1) = x :item : (insertEveryHelper k item xs k)
                     |otherwise = x : (insertEveryHelper (n-1) item xs k)


insertEvery :: (Eq t, Num t) => t -> a -> [a] -> [a] 
insertEvery n item iL = insertEveryHelper n item iL n

-- 3. getSales

--storelog = [("Mon",50),("Fri",20), ("Tue",20),("Fri",10),("Wed",25),("Fri",30)]

getSales :: (Num p, Eq t) => t -> [(t, p)] -> p 
getSales day [] = 0
getSales day ((listDay,amount):xs) | (listDay == day) = amount + (getSales day xs)
                                   | otherwise = (getSales day xs)
                                                  
-- 4. sumSales

-- sales = [("Amazon",[("Mon",30),("Wed",100),("Sat",200)]), 
--          ("Etsy",[("Mon",50),("Tue",20),("Wed",25),("Fri",30)]), 
--          ("Ebay",[("Tue",60),("Wed",100),("Thu",30)]), 
--          ("Etsy",[("Tue",100),("Thu",50),("Sat",20),("Tue",10)])] 

sumSales:: (Num p)=> String -> String -> [(String,[(String,p)])] -> p
sumSales store day [] = 0
sumSales store day ((listStore, log):xs) | (store == listStore) = (getSales day log) + (sumSales store day xs)
                              | otherwise = (sumSales store day xs)

-- 5. split




split :: Eq a => a -> [a] -> [[a]]
split c [] = []
split c iL = splitHelper c iL []
     where
     splitHelper c [] buf | (buf == []) = []
                          | otherwise = (reverse buf):[]
     splitHelper c (x:xs) buf | (c == x) = (reverse buf) : (splitHelper c xs [])
                         |otherwise = splitHelper c xs (x:buf)

-- 6. nSplit

-- nSplit :: (Ord a1, Num a1, Eq a2) => a2 -> a1 -> [a2] -> [[a2]]
-- nSplit c n [] = []
-- nSplit c n iL = nSplitHelper c n iL []
--      where
--      nSplitHelper c n [] buf     | (buf == []) = []
--                                  | otherwise = (reverse buf) : []
--      nSplitHelper c n (x:xs) buf | (c == x) && (n >0) = (reverse buf) : (nSplitHelper c n-1 xs [])
--                                  | (c /= x) && (n >0) = nSplitHelper c n xs (x:buf)
--                                  | otherwise = (xs):[]

nSplit :: (Ord a1, Num a1, Eq a2) => a2 -> a1 -> [a2] -> [[a2]]
nSplit c n [] = []
nSplit c n iL = nSplitHelper c n iL []
     where
     nSplitHelper c 0 [] buf     | (buf == []) = []
                                 | otherwise = (reverse buf) : []
     nSplitHelper c n [] buf     | (buf == []) = []
                                 | otherwise = (reverse buf) : []
     nSplitHelper c n (x:xs) buf | (c == x) && (n > 0) = (reverse buf) : (nSplitHelper c (n-1) xs [])
                                 | (c /= x) && (n > 0)= nSplitHelper c n xs (x:buf)
                                 | otherwise = (x:xs):[]
