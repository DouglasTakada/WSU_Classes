module ClassexercisesTests
    where

import Test.HUnit
import Classexercises


f1_test1 = TestCase (assertEqual "getSeconds - test1" "HASKELL" (getSeconds [(1,'H'),(2,'A'),(3,'S'),(4,'K'),(5,'E'),(6,'L'),(7,'L')]) ) 


f2_test1 = TestCase (assertEqual "numbers2Sum-test1" [1,2,3,4,5]  (numbers2Sum [1,2,3,4,5,6,7]  15) ) 
f2_test2 = TestCase (assertEqual "numbers2Sum-test2" [1,2,3,4]  (numbers2Sum [1,2,3,4,5,6,7]  14) ) 
f2_test3 = TestCase (assertEqual "numbers2Sum-test3" [1,2,3]  (numbers2Sum [1,2,3,4,5,6,7]  7) ) 

f3_test1 = TestCase (assertEqual "groupby3-test1" [[1,2,3],[4,5,6],[7,8,9],[10]]  (groupby3 [1,2,3,4,5,6,7,8,9,10]) ) 
f3_test2 = TestCase (assertEqual "groupby3-test2" [[1,2,3],[4,5,6],[7,8,9],[10,11]]  (groupby3 [1,2,3,4,5,6,7,8,9,10,11]) ) 
f3_test3 = TestCase (assertEqual "groupby3-test3" [[1,2,3],[4,5,6],[7,8,9],[10,11,12]]  (groupby3 [1,2,3,4,5,6,7,8,9,10,11,12]) ) 
f3_test4 = TestCase (assertEqual "groupby3-test4" ([]::[[Int]])  (groupby3 []) ) 
f3_test5 = TestCase (assertEqual "groupby3-test5" ["355","322","321","36"]  (groupby3 "35532232136") ) 

f4_test1 = TestCase (assertEqual "myelem-test1" [4,6]  (myelem [2,4,6] [10,6,4,3,4,5,7]) ) 
f4_test2 = TestCase (assertEqual "myelem-test2" []  (myelem [2,4,6] [8,9,10]) )

f5_test1 = TestCase (assertEqual "longest_list-test1" [10,6,4,5,7]  (longest_list [[2,4,6],[],[10,6,4,5,7],[3],[1,2,3,4],[1,2,3,4,5],[]]) ) 

tests = TestList [ TestLabel "Function 1- test1 " f1_test1,
                   TestLabel "Function 2- test1 " f2_test1,
                   TestLabel "Function 2- test2 " f2_test2,
                   TestLabel "Function 2- test3 " f2_test3,
                   TestLabel "Function 3- test1 " f3_test1, 
                   TestLabel "Function 3- test2 " f3_test2,
                   TestLabel "Function 3- test3 " f3_test3,
                   TestLabel "Function 3- test4 " f3_test4,
                   TestLabel "Function 3- test5 " f3_test5,
                   TestLabel "Function 4- test1 " f4_test1,
                   TestLabel "Function 4- test1 " f4_test2,
                   TestLabel "Function 5- test1 " f5_test1
                 ] 
                  

-- shortcut to run the tests
run = runTestTT  tests