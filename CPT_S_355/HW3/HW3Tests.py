#------------------------------------------------------
#-- INCLUDE YOUR OWN TESTS IN THIS FILE
#------------------------------------------------------
import unittest
from HW3 import *

# ----- Helper classes ------
class Numbers():
    def __init__(self,init):
        self.current = init
    def __next__(self):
        result = self.current
        self.current += 1
        return result
    def __iter__(self):
        return self

class HW3SampleTests(unittest.TestCase):
    "Unittest setup file. Unittest framework will run this before every test."
    def setUp(self):
        pass
    
    #--- Problem 1(a)----------------------------------
    
    def test_aggregate_log0(self):
        log_input = {'Math':{'Mon':3,'Tue':2,'Wed':2, 'Thu':300,'Fri':10,'Sat':1,'Sun':33333},
                     'NotMath':{'Mon':3,'Tue':2,'Wed':2,'Fri':10},
                     'Reading':{'Tue':2,'Wed':2,'Thu':3},
                     'Eating':{'Tue':1,'Thu':5,'Sat':2}}
        output = {'Mon': 6, 'Tue': 7, 'Wed': 6, 'Thu': 308, 'Fri': 20, 'Sat': 3, 'Sun': 33333}
        self.assertDictEqual(aggregate_log(log_input),output)

    def test_aggregate_log1(self):
        log_input = {'hey':{'Monday':1}}
        output = {'Monday': 1}
        self.assertDictEqual(aggregate_log(log_input),output)

    #--- Problem 1(b)----------------------------------
    def test_combine_dict0(self):
        log1 = {'Heyo':11111,'Dougie':2222,'Sat':2}
        log2 = {'Dougie':3,'Heyo':2,'Sat':2,'Fri':10}
        output = {'Heyo': 11113, 'Dougie': 2225, 'Sat': 4, 'Fri': 10}
        self.assertDictEqual(combine_dict(log1,log2),output)
        #make sure input dictionaries are not changed. 
        self.assertDictEqual(log1, {'Heyo':11111,'Dougie':2222,'Sat':2})
        self.assertDictEqual(log2, {'Dougie':3,'Heyo':2,'Sat':2,'Fri':10})

    def test_combine_dict1(self):
        log1 = {}
        log2 = {'Dougie':3,'Heyo':2,'Sat':2,'Fri':10}
        output = {'Dougie':3,'Heyo':2,'Sat':2,'Fri':10}
        self.assertDictEqual(combine_dict(log1,log2),output)
        #make sure input dictionaries are not changed. 
        self.assertDictEqual(log1, {})
        self.assertDictEqual(log2, {'Dougie':3,'Heyo':2,'Sat':2,'Fri':10})
    
    def test_combine_dict2(self):
        log1 = {'Heyo':11111,'Dougie':2222,'Sat':2}
        log2 = {}
        output = {'Heyo':11111,'Dougie':2222,'Sat':2}
        self.assertDictEqual(combine_dict(log1,log2),output)
        #make sure input dictionaries are not changed. 
        self.assertDictEqual(log2, {})
        self.assertDictEqual(log1, {'Heyo':11111,'Dougie':2222,'Sat':2})

    #--- Problem 1(c) ----------------------------------
    def sort_values(self,d):
        return dict(map(lambda t: (t[0],list(sorted(t[1]))), d.items()))

    def test_merge_logs0(self):
        log_list_backup = [{'CptS355':{'Mon':3},'CptS360':{'Mon':3},'CptS321':{'Tue':2,},'CptS322':{'Tue':1}},
             {'CptS322':{'Mon':2},'CptS360':{'Thu':2},'CptS321':{'Mon':1}},
             {'CptS355':{'Mon':8},'CptS360':{'Sun':5},'CptS321':{'Sat':4},'CptS322':{'Sat':3}}]
        log_list = [{'CptS355':{'Mon':3},'CptS360':{'Mon':3},'CptS321':{'Tue':2,},'CptS322':{'Tue':1}},
             {'CptS322':{'Mon':2},'CptS360':{'Thu':2},'CptS321':{'Mon':1}},
             {'CptS355':{'Mon':8},'CptS360':{'Sun':5},'CptS321':{'Sat':4},'CptS322':{'Sat':3}}]
        output = {'CptS355': {'Mon': 11}, 'CptS360': {'Mon': 3, 'Thu': 2, 'Sun': 5}, 'CptS321': {'Tue': 2, 'Mon': 1, 'Sat': 4}, 'CptS322': {'Tue': 1, 'Mon': 2, 'Sat': 3}}
        self.assertDictEqual(self.sort_values(merge_logs(log_list)),self.sort_values(output))
        self.assertListEqual(log_list,log_list_backup)

    def test_merge_logs1(self):
        log_list_backup = [{'Class1':{'day1':3,'day2':2,'day3':1}},{'Class1':{'day1':3,'day2':2,'day3':1}},
            {'Class1':{'day1':3,'day2':2,'day3':1}},{'Class1':{'day1':3,'day2':2,'day3':1}}]

        log_list = [{'Class1':{'day1':3,'day2':2,'day3':1}},{'Class1':{'day1':3,'day2':2,'day3':1}},
            {'Class1':{'day1':3,'day2':2,'day3':1}},{'Class1':{'day1':3,'day2':2,'day3':1}}]

        output = {'Class1': {'day1': 12, 'day2': 8, 'day3': 4}}
        self.assertDictEqual(self.sort_values(merge_logs(log_list)),self.sort_values(output))
        self.assertListEqual(log_list,log_list_backup)

    #--- Problem 2(a)----------------------------------
    def test_most_hours0(self):

        log_input = {'CptS355': {'The': 3, 'Input': 2, 'does': 2, 'not': 8}, 
                          'CptS360': {'matter': 3, '!!': 2, 'helelo': 2, 'k': 20, 'j': 2}, 
                          'CptS321': {'f': 2, 'Wed': 2, 'h': 3, 'h': 5, 'j': 3}, 
                          'CptS322': {'c': 1, 'v': 5, 'b': 5, 'k': 2}}
        output = ('CptS360', 29)
        self.assertTupleEqual(most_hours(log_input),output)

    def test_most_hours1(self):
        input = {'class1': {}}
        output = ('class1',0)
        self.assertTupleEqual(most_hours(input),output)

            
    #--- Problem 2(b) ----------------------------------
    def test_filter_log0(self):
        input = {'class1': {'Gorrila': 3, 'Day': 2, '1212': 2, 'Sun': 8}, 
                          'class9': {'The': 3, 'days': 2, 'dont': 2, 'matter': 20, '!!!!': 2}, 
                          'class2': {'1': 2, '2': 2, '4': 3, '1212': 5, '19': 3}, 
                          'class4': {'T32424ue': 1, '1212': 5, '111': 5, '100': 2}}
        input_backup = {'class1': {'Gorrila': 3, 'Day': 2, '1212': 2, 'Sun': 8}, 
                          'class9': {'The': 3, 'days': 2, 'dont': 2, 'matter': 20, '!!!!': 2}, 
                          'class2': {'1': 2, '2': 2, '4': 3, '1212': 5, '19': 3}, 
                          'class4': {'T32424ue': 1, '1212': 5, '111': 5, '100': 2}}
        output = ['class1', 'class2', 'class4']
        self.assertListEqual(sorted(filter_log(input,'1212', 0)),output)
        self.assertDictEqual(input,input_backup)

    def test_filter_log1(self):
        input = {'class1': {'Gorrila': 3, 'Day': 2, '1212': 2, 'Sun': 8}, 
                          'class9': {'The': 3, 'days': 2, 'dont': 2, 'matter': 20, '!!!!': 2}, 
                          'class2': {'1': 2, '2': 2, '4': 3, '1212': 5, '19': 3}, 
                          'class4': {'T32424ue': 1, '1212': 5, '111': 5, '100': 2}}
        input_backup = {'class1': {'Gorrila': 3, 'Day': 2, '1212': 2, 'Sun': 8}, 
                          'class9': {'The': 3, 'days': 2, 'dont': 2, 'matter': 20, '!!!!': 2}, 
                          'class2': {'1': 2, '2': 2, '4': 3, '1212': 5, '19': 3}, 
                          'class4': {'T32424ue': 1, '1212': 5, '111': 5, '100': 2}}
        output = []
        self.assertListEqual(sorted(filter_log(input,'1212', 3000)),output)
        self.assertDictEqual(input,input_backup)

    #--- Problem 3----------------------------------
    def test_graph_cycle0(self):
        graph0 = {'A':('B',5),'B':('C',3),'C':('D',10),'D':('E',4),'E':('F',5),'F':('G',4),'G':('H',9),'H':('I',5),'I':('J',3)}
        self.assertEqual(graph_cycle(graph0,'A'),None)

    def test_graph_cycle1(self): 
        graph1 = {'A':('B',5),'B':('C',3),'C':('D',10),'D':('E',4),'E':('F',5),'F':('G',4),'G':('H',9),'H':('I',5),'I':('A',3)}
        self.assertListEqual(graph_cycle(graph1,'A'),['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'A'])

    #--- Problem 4----------------------------------
    def test_filter_iter0(self):
        it = iter([7,4,5,3,3,6,2]) 
        expected_output = [7,4,5,3,3,6,2]
        actual_output = list(filter_iter(it, lambda x: x>0))  #convert the iterator output to list
        self.assertListEqual(actual_output, expected_output)
    
    def test_filter_iter1(self):
        it = iter([7,4,5,3,3,6,2]) 
        expected_output = []
        actual_output = list(filter_iter(it, lambda x: x> 10))  #convert the iterator output to list
        self.assertListEqual(actual_output, expected_output)

    #--- Problem 5----------------------------------

    def test_merge0(self):
        it1 = iter([2,3,5,7,11,13,17,19,2222222])
        it2 = filter_iter(Numbers(1), lambda x: x%10==0)
        self.assertListEqual(merge(it1,it2, 5), [2, 3, 5, 7,10])
        self.assertListEqual(merge(it1,it2, 5), [13, 17, 19, 30, 40])

    def test_merge1(self):
        it1 = iter([1,2,3,4,5,6,7,8,9])
        it2 = iter([9,8,7,6,5,4,3,2,1])
        self.assertListEqual(merge(it1,it2, 5), [1, 2, 3, 4, 5])
        self.assertListEqual(merge(it1,it2,0), [])
        

if __name__ == '__main__':
    unittest.main()

