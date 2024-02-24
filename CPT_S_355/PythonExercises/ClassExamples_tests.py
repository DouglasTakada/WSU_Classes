import unittest
from ClassExamples import *

class ClassExamples_Tests(unittest.TestCase):
    def setUp(self):
        self.wsu_games = {
            2018: { "WYO":(41,19), "SJSU":(31,0),  "EWU":(59,24), "USC":(36,39), "UTAH":(28,24), 
                   "ORST":(56,37), "ORE":(34,20), "STAN":(41,38), "CAL":(19,13), "COLO":(31,7), 
                   "ARIZ":(69,28), "WASH":(15,28), "ISU":(28,26)},
            2019: {"NMSU":(58,7), "UNCO":(59,17), "HOU":(31,24), "UCLA":(63,67), "UTAH":(13,38), 
                    "ASU":(34,38), "COLO":(41,10), "ORE":(35,37), "CAL":(20,33), "STAN":(49,22), 
                   "ORST":(54,53), "WASH":(13,31), "AFA":(21,31) },
            2020: {"ORST":(38,28), "ORE":(29,43), "USC":(13,38), "UTAH":(28,45)},
            2021: { "USU":(23,26), "PORT ST.":(44,24), "USC":(14,45), "UTAH":(13,24), "CAL":(21,6),
                   "ORST":(31,24), "STAN":(34,31), "BYU":(19,21), "ASU":(34,21), "ORE":(24,38), 
                   "ARIZ":(44,18), "WASH":(40,13), "CMU":(21,24)} }

    def test_histo_test1 (self):
        self.assertEqual(histo("implemented"),[('e', 3), ('m', 2), ('d', 1), ('i', 1), ('l', 1), ('n', 1), ('p', 1), ('t', 1)])
        
    def test_histo_test2 (self):
        self.assertEqual(histo("ABBCCCDDDDEEEEEFFFFFFGGGGGGG"),[('G', 7), ('F', 6), ('E', 5), ('D', 4), ('C', 3), ('B', 2), ('A', 1)])
    
    def test_game_scores1(self):
        output = [(36, 39), (13, 38), (14, 45)]
        self.assertListEqual(game_scores(self.wsu_games, "USC"),output )

    def test_game_scores2(self):
        output = [(56, 37), (54, 53), (38, 28), (31, 24)]
        self.assertListEqual(game_scores(self.wsu_games, "ORST"),output )

    def test_wins_by_year(self):
        output = [(2018, 11), (2019, 6), (2020, 1), (2021, 7)]
        self.assertListEqual(wins_by_year(self.wsu_games),output )

if __name__ == '__main__':
    unittest.main(verbosity=2)

