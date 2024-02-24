# CptS 355 - Spring 2023 - Lab 3
# Douglas Takada

debugging = False
def debug(*s): 
     if debugging: 
          print(*s)

## problem 1 getNumCases 

# CDCdata = {'King':{'Mar':2706,'Apr':3620,'May':1860,'Jun':2157,'July':5014,'Aug':4327,'Sep':2843},  
# 'Pierce':{'Mar':460,'Apr':965,'May':522,'Jun':647,'July':2470,'Aug':1776,'Sep':1266},  
# 'Snohomish':{'Mar':1301,'Apr':1145,'May':532,'Jun':568,'July':1540,'Aug':1134,'Sep':811},  
# 'Spokane':{'Mar':147,'Apr':222,'May':233,'Jun':794,'July':2412,'Aug':1530,'Sep':1751},  
# 'Whitman' : {'Apr':7,'May':5,'Jun':19,'July':51,'Aug':514,'Sep':732, 'Oct':278} } 
 

def getNumCases(data, countries, months):
     cases = 0
     for country in countries:
          if data.get(country) is not None:
               for month in months:
                    if data.get(country).get(month) is not None:
                         cases += data.get(country).get(month)
     return cases


## problem 2 getMonthlyCases

def getMonthlyCases(data):
    newdata ={}
    for country in data:
        print("country: "+country)
        for month in data[country]:
            print("month: "+month)
            if newdata.get(month) is None:
                newdata[month] = {}
            if newdata.get(month).get(country) is None:
                newdata[month][country] = data.get(country).get(month)
    return newdata



from functools import reduce
## problem 3 mostCases 

def mostCases(data):
     map_helper = lambda data : reduce(lambda x,y: x+y,data.values())
     monthy_cases = getMonthlyCases(data)
     return reduce(lambda t1, t2: t1 if t1[1] >= t2[1] else t2,
                   list(map(lambda t: (t[0],map_helper(t[1])),monthy_cases.items())))


## problem 4a) searchDicts(L,k)
L1 = [{"x":1,"y":True,"z":"found"},{"x":2},{"y":False}]

def searchDicts(L,K):
     for i in reversed(L):
          if i.get(K) is not None:
               return i.get(K)
## problem 4b) searchDicts2(L,k)

def searchDicts2(tL,k):
      def helper(tL,k,ind):
           if k in tL[ind][1]:
                return tL[ind][1][k]
           elif ind == 0:
                return None
           else:
                return helper(tL,k,tL[ind][0])
           
      return helper(tL,k,len(tL)-1)
     

## problem 5 - getLongest

def getLongest(L):
     getLonger = lambda x,y: y if len(x) <= len(y) else x
     longest = ""
     for item in L:
          if isinstance(item,list):
               longest = getLonger(getLongest(item), longest)
          else:
               longest = getLonger(item, longest)
     return longest

## problem 6 - apply2nextN

class apply2nextN(object):
     def __init__(self,op, n,it):
          self.input1 = it
          self.op = op
          self.n = n
          self.current = self._getNextInput()

     def _getNextInput(self):
          try:
               current = self.input1.__next__()
          except:
               current = None
          return current
     
     def __next__(self):
          if self.current is None:
               raise StopIteration
          
          temp_n = self.n
          total = self.current
          self.current = self._getNextInput()
          while (temp_n >1):

               if self.current is not None:
                    total = self.op(total, self.current)
               else:
                    break
               self.current = self._getNextInput()
               temp_n -= 1
          return total
     def __iter__(self):
          return self

