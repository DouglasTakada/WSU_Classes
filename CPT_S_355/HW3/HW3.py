# CptS 355 - Spring 2023 - Assignment 3 - Python

# Please include your name and the names of the students with whom you discussed any of the problems in this homework
# Name: Douglas Takada
# Collaborators: 

debugging = False
def debug(*s): 
     if debugging: 
          print(*s)

from functools import reduce

## problem 1(a) - aggregate_log  - 5%

def aggregate_log(input):
     new_dict = {}
     for dicts in input:
          # print(input.get(dicts))
          if input.get(dicts) is not None:
               for days in input.get(dicts):
                    if new_dict.get(days) is None:
                         new_dict[days] = 0
                    new_dict[days] += input.get(dicts).get(days)
     return new_dict

## problem 1(b) - combine_dict– 6%

def combine_dict(dict1, dict2):
     new_dict = {}
     for key in dict1:
          if new_dict.get(key) is None:
               new_dict[key] = 0
          new_dict[key] += dict1.get(key)
     for key in dict2:
          if new_dict.get(key) is None:
               new_dict[key] = 0
          new_dict[key] += dict2.get(key)
     return new_dict

## problem 1(c) - merge_logs– 12%

def merge_logs(lst):
     new_dict = {}
     for dicts in lst:
          for key in dicts.keys():
               if new_dict.get(key) is None:
                    new_dict[key] = {}
               new_dict[key] = combine_dict(new_dict[key], dicts.get(key))

     return new_dict

log_list = [{'CptS355':{'Mon':3},'CptS360':{'Mon':3},'CptS321':{'Tue':2,},'CptS322':{'Tue':1}},
             {'CptS322':{'Mon':2},'CptS360':{'Thu':2},'CptS321':{'Mon':1}},
             {'CptS355':{'Mon':8},'CptS360':{'Sun':5},'CptS321':{'Sat':4},'CptS322':{'Sat':3}}]
print(merge_logs(log_list))

## problem 2(a) - most_hours – 15%

from functools import reduce

def most_hours(data):
    temp = reduce(lambda x, y: x if sum(x[1].values()) > sum(y[1].values()) else y, data.items())
    return (temp[0],sum(temp[1].values()))

input = {'class1': {}}

print(most_hours(input))

## problem 2(b) - filter_log – 15%

def filter_log(data,day, hours):
     temp = list(filter(lambda x: x[0] if (x[1].get(day) is not None and x[1].get(day) >= hours) else None, data.items()))
     return list(map(lambda x : x[0], temp))

## problem 3 - graph_cycle – 12% 

def graph_cycle(graph, start):
     def helper(graph, start,acc):
          if graph.get(start) is None:
               return None
          elif start not in new_list:
               acc.append(start)
               return helper(graph, graph.get(start)[0],acc)
          else:
               acc.append(start)
               return acc
     
     new_list = []
     temp = helper(graph, start,new_list)
     #Cutting out extra letters not in loop
     if temp is None:
          return None
     else:
          return temp[temp.index(temp[-1],0,-1):]

## problem 4 - filter_iter – 15% 

class filter_iter(object):
     def __init__(self,it,op):
          self.input = iter(it)
          self.op = op
     
     def __next__(self):
          if self.input is None:
               raise StopIteration
          temp = next(self.input)
          while not self.op(temp):
               temp = next(self.input)
          return temp
     def __iter__(self):
          return self

## problem 5 - merge – 10% 

def merge(it1, it2, n):
     newList = []
     temp1 = next(it1, None)
     temp2 = next(it2,None)
     if temp1 == None:
          return newList
     if temp2 == None:
          return newList
     for x in range(0,n):
          if temp1 <= temp2:
               newList.append(temp1)
               temp1 = next(it1,None)
               if temp1 is None:
                    break
          else:
               newList.append(temp2)
               temp2 = next(it2,None)
               if temp2 is None:
                    break
     return newList

class Numbers():
    def __init__(self,init):
        self.current = init
    def __next__(self):
        result = self.current
        self.current += 1
        return result
    def __iter__(self):
        return self
