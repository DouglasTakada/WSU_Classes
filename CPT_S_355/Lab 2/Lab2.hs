-- CptS 355 - Lab 2 (Haskell) - Spring 2023
-- Name: Douglas Takada
-- Collaborated with: Chandler Juego

module Lab2
     where


-- 1
{- (a) merge2 -}

merge2 :: [a] -> [a] -> [a]
merge2 x [] = x
merge2 [] x = x
merge2 (x:xs) (y:ys) = x:y:merge2 xs ys
                      

{- (b) merge2Tail -}

merge2Tail :: [a] -> [a] -> [a]
merge2Tail l1 l2 = merge2TailHelper l1 l2 []
     where
          merge2TailHelper [] [] acc = reverse acc
          merge2TailHelper (x:xs) [] acc = merge2TailHelper xs [] (x:acc)
          merge2TailHelper [] (y:ys) acc = merge2TailHelper [] ys (y:acc)
          merge2TailHelper (x:xs) (y:ys) acc = merge2TailHelper xs ys (y:x:acc)

{- (c) mergeN -}

mergeN:: [[a]] -> [a]
mergeN xs = foldl merge2 [] xs

-- 2
{- (a) count -}

count :: Eq a => a -> [a] -> Int
count _ [] = 0
count value xs = foldl (\acc x -> if x == value then acc + 1 else acc) 0 xs

{- (b) histogram  -}

histogram :: Eq a => [a] -> [(a, Int)] 
histogram xs = map  (\x -> (x, count x  xs)) $ eliminateDuplicates2 xs
     where
          eliminateDuplicates2 xs = foldr helper [] xs
               where
                    helper x base | (elem x base) = base
                                  | otherwise = x : base

-- 3                
{- (a) concatAll -}

concatAll ::  [[String]] -> String 
concatAll lst = concatAllHelper (map concatAllHelper lst)
     where concatAllHelper lst = foldr (++) [] lst

{- (b) concat2Either -}               
data AnEither  = AString String | AnInt Int
                deriving (Show, Read, Eq)

concat2Either:: [[AnEither]] -> AnEither
concat2Either lst = concatEitherList (map concatEitherList lst)
     where
          concatEitherList xs = foldr eitherConcat (AString "") xs

          eitherConcat (AString x) (AString y) = AString (x ++ y)
          eitherConcat (AnInt x) (AnInt y) = AString (show(x) ++ show(y))
          eitherConcat (AString x) (AnInt y) = AString (x ++ show(y))
          eitherConcat (AnInt x ) (AString y) = AString (show(x) ++ y)

-- 4      
{-  concat2Str -}



-- concat2Str:: [[AnEither]] -> String
-- concat2Str lst = foldr (++) "" (map concat2StrList lst)
--      where
          
--           concat2StrList xs = foldr (++) "" (map strConcat xs)

          

data Op = Add | Sub | Mul | Pow
          deriving (Show, Read, Eq)

evaluate:: Op -> Int -> Int -> Int
evaluate Add x y =  x+y
evaluate Sub   x y =  x-y
evaluate Mul x y =  x*y
evaluate Pow x y = x^y

data ExprTree a = ELEAF a | ENODE Op (ExprTree a) (ExprTree a)
                  deriving (Show, Read, Eq)

-- 5 
{- evaluateTree -}

evaluateTree (ELEAF xs) = xs
evaluateTree (ENODE op x y) = evaluate op (evaluateTree x) (evaluateTree y)

-- 6
{- printInfix -}

printInfix :: Show a => ExprTree a -> String
printInfix (ELEAF x) = show x
printInfix (ENODE op x y) = "(" ++ (printInfix x) ++ " `" ++ show op ++ "` " ++ (printInfix y) ++ ")"

--7
{- createRTree -}
-- data ResultTree a  = RLEAF a | RNODE a (ResultTree a) (ResultTree a)
--                      deriving (Show, Read, Eq)
