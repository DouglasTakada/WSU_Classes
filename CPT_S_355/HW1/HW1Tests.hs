{- Example of using the HUnit unit test framework.  See  http://hackage.haskell.org/package/HUnit for additional documentation.
To run the tests type "run" at the Haskell prompt.  -} 

module HW1Tests
    where

import Test.HUnit
import Data.Char
import Data.List (sort)
import HW1

--idea for test cases: domain of input, maximum, minimum, inside/outside boundaries, typical values, error values

-- P1(a) count tests  

p1a_test4 = TestCase (assertEqual "count-test4"
                                 0
                                 (count 1231 []) )
p1a_test5 = TestCase (assertEqual "count-test5"
                                 5
                                 (count True [True, True, False, False, True, True, True]) )
p1a_test6= TestCase (assertEqual "count-test6"
                                 2
                                 (count (1,2) [(1,2), (1,2), (2,1), (2,1)]) )
-- P1(b) diff tests

p1b_test4 = TestCase (assertEqual "diff-test4"
                                 [1,2,3,4,5,6,7,8]
                                 (diff [1,2,3,4,5,6,7,8] []) )
p1b_test5 = TestCase (assertEqual "diff-test5"
                                 []
                                 (diff [] [1,2,3,4,5,6,7,8]) )
p1b_test6 = TestCase (assertEqual "diff-test6"
                                 [True]
                                 (diff [True, False] [False]) )

-- P1(c) bag_diff tests

p1c_test5 = TestCase (assertEqual "bag_diff-test5"
                                 [1,2]
                                 (bag_diff [1,2] []) )
p1c_test6 = TestCase (assertEqual "bag_diff-test6"
                                 []
                                 (bag_diff [] [1,2]) )
p1c_test7 = TestCase (assertEqual "bag_diff-test7"
                                 [(1,2),(1,2)]
                                 (bag_diff [(1,2),(1,2),(1,2)] [(1,2)]) )

-- P2  everyN tests

p2_test5 = TestCase (assertEqual "everyN-test5"
                                 ""
                                 (everyN "Hello" 10) )
p2_test6 = TestCase (assertEqual "everyN-test6"
                                 [(5,6),(11,12)]
                                 (everyN [(1,2),(3,4),(5,6),(7,8),(9,10),(11,12)] 3) )
p2_test7 = TestCase (assertEqual "everyN-test7"
                                 [True,True,True]
                                 (everyN [True,False,True,False,False,True,False,True,True] 3) )

-- P3(a) make_sparse tests

p3a_test5 = TestCase (assertEqual "make_sparse-test5"
                                 [1]
                                 (make_sparse [(0,1)] ) )
p3a_test6 = TestCase (assertEqual "make_sparse-test6"
                                 [-1,0,0,0,0,-29]
                                 (make_sparse [(0,(-1)), (5,(-29))]) )
p3a_test7 = TestCase (assertEqual "make_sparse-test7"
                                [-1.2121,0.0,0.0,0.0,0.0,3.1415]
                                (make_sparse [(0,(-1.2121)), (5,(3.1415))]) )

-- P3(b) compress tests

p3b_test5 = TestCase (assertEqual "compress-test5"
                                 []
                                 (compress [0,0,0,0,0,0,0,0,0]) )
p3b_test6 = TestCase (assertEqual "compress-test6"
                                 [(8.0,-1.2312322)]
                                 (compress [0,0,0,0,0,0,0,0,-1.2312322]) )
p3b_test7 = TestCase (assertEqual "compress-test7"
                                 [(0.0,-1.2312322)]
                                 (compress [-1.2312322]) )

-- P4 added_sums tests

p4_test4 = TestCase (assertEqual "added_sums-test4"
                                 [1.0,3.0,6.0,10.0,15.0,21.0,28.0,36.0,45.0,55.0]
                                 (added_sums [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0]) )
p4_test5 = TestCase (assertEqual "added_sums-test5"
                                 [-1,-3,-6,-10,-15,-21,-28,-36,-45,-55]
                                 (added_sums [-1,-2,-3,-4,-5,-6,-7,-8,-9,-10]) )
p4_test6 = TestCase (assertEqual "added_sums-test6"
                                 [123456789]
                                 (added_sums [123456789]) )

-- P5 find_routes tests

routes_my_test0 = [("Lentil",["Home", "Orchard", "Valley", "Emerald","Providence", "Stadium", "Main", "Arbor", "Sunnyside", "Fountain", "Crestview", "Wheatland", "Walmart", "Bishop", "Derby", "Dilke"]), 
   ("Wheat",["Home", "Orchard", "Valley", "Maple","Aspen", "TerreView", "Clay", "Dismores", "Martin", "Bishop", "Walmart", "PorchLight", "Campus"]), 
   ("Silver",["Home", "PorchLight", "Stadium", "Bishop","Walmart", "Outlet", "RockeyWay","Main"]),
   ("Blue",["Home", "State", "Larry", "TerreView","Grand", "TacoBell", "Chinook", "Library"]),
   ("Gray",["Home", "Wawawai", "Main", "Sunnyside","Crestview", "CityHall", "Stadium", "Colorado"]),
   ("Coffee",["Home", "Grand", "Main", "Visitor","Stadium", "Spark", "CUB"])] 

routes_my_test1 = [("HomeRoute",["Home", "Orchard", "Valley", "Emerald","Providence", "Stadium", "Main", "Arbor", "Sunnyside", "Fountain", "Crestview", "Wheatland", "Walmart", "Bishop", "Derby", "Dilke"])]

routes_my_test2 = [("NotHomeRoute",["NotHome"])]

routes_my_test3 = [("Lentil",["Home", "Home", "Home", "Home","Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home"]), 
   ("Wheat",["Home", "Home", "Home", "Home","Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home"]), 
   ("Silver",["Home", "Home", "Home", "Home","Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home"]),
   ("Blue",["Home", "Home", "Home", "Home","Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home"]),
   ("Gray",["Home", "Home", "Home", "Home","Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home"]),
   ("Coffee",["Home", "Home", "Home", "Home","Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home", "Home"]),
   ("NotHome",["NotHome","NotHome","NotHome","NotHome","NotHome","NotHome","NotHome","NotHome","NotHome","NotHome","NotHome","NotHome"])] 

p5_test4 = TestCase (assertEqual "find_routes-test4"
                                 ["Lentil","Wheat","Silver","Blue","Gray","Coffee"]
                                 (find_routes "Home" routes_my_test0) )
p5_test5 = TestCase (assertEqual "find_routes-test5"
                                 ["HomeRoute"]
                                 (find_routes "Home" routes_my_test1) )
p5_test6 = TestCase (assertEqual "find_routes-test6"
                                 []
                                 (find_routes "Home" routes_my_test2) )
p5_test7 = TestCase (assertEqual "find_routes-test7"
                                 ["Lentil","Wheat","Silver","Blue","Gray","Coffee"]
                                 (find_routes "Home" routes_my_test3))


-- P6 group_sum tests

p6_test4 = TestCase (assertEqual "group_sum-test4"
                                 [[1,2,3,4,5,6,7,8,9,10]]
                                 (group_sum [1,2,3,4,5,6,7,8,9,10] 60) )
p6_test5 = TestCase (assertEqual "group_sum-test5"
                                 [[1]]
                                 (group_sum [1] 20) )
p6_test6 = TestCase (assertEqual "group_sum-test6"
                                 [[-1,-2,-3,-4,-5,-6,-7,-8,-9,-10]]
                                 (group_sum [-1,-2,-3,-4,-5,-6,-7,-8,-9,-10] 0) )

-- add the test cases you created to the below list. 
tests = TestList [ TestLabel "Problem 1a- test4 " p1a_test4,
                   TestLabel "Problem 1a- test5 " p1a_test5,
                   TestLabel "Problem 1a- test6 " p1a_test6,

                   TestLabel "Problem 1b- test4 " p1b_test4,
                   TestLabel "Problem 1b- test5 " p1b_test5,
                   TestLabel "Problem 1b- test6 " p1b_test6,

                   TestLabel "Problem 1c- test5 " p1c_test5,
                   TestLabel "Problem 1c- test6 " p1c_test6,
                   TestLabel "Problem 1c- test7 " p1c_test7,

                   TestLabel "Problem 2- test5 " p2_test5,
                   TestLabel "Problem 2- test6 " p2_test6,
                   TestLabel "Problem 2- test7 " p2_test7,
                   
                   TestLabel "Problem 3a- test5 " p3a_test5,
                   TestLabel "Problem 3a- test6 " p3a_test6,
                   TestLabel "Problem 3a- test7 " p3a_test7,


                   TestLabel "Problem 3b- test5 " p3b_test5,
                   TestLabel "Problem 3b- test6 " p3b_test6,
                   TestLabel "Problem 3b- test7 " p3b_test7,

                   TestLabel "Problem 4- test4 " p4_test4,
                   TestLabel "Problem 5- test5 " p4_test5,
                   TestLabel "Problem 6- test6 " p4_test6,

                   TestLabel "Problem 5- test4 " p5_test4,
                   TestLabel "Problem 5- test5 " p5_test5,
                   TestLabel "Problem 5- test6 " p5_test6,
                   TestLabel "Problem 5- test7 " p5_test7,

                   TestLabel "Problem 6- test4 " p6_test4,
                   TestLabel "Problem 6- test5 " p6_test5,
                   TestLabel "Problem 6- test6 " p6_test6
                 ]

-- shortcut to run the tests
run = runTestTT  tests