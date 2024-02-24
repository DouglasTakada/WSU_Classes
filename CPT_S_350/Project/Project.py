from pyeda.inter import *

#Step 3.1
#Finds the pair of nodes that have a relationship and pairs them together.
#Converts them into 5 digit binary and saves them in list named pair
#The set of edges in G
R = []
count = 0
for i in range(32):
    for j in range(32):
        if (i+3)%32 == j%32 or (i+8)%32 ==j%32 :
            R.append((bin(i)[2:].zfill(5),bin(j)[2:].zfill(5)))
            count += 1
print(count)

print(f"number of paths in G: {len(R)}")

#The xx variables are going to be used in the RR BDD and the PRIME BDD
xx0 = bddvar('xx0') 
xx1 = bddvar('xx1') 
xx2 = bddvar('xx2')
xx3 = bddvar('xx3') 
xx4 = bddvar('xx4')

#The yy variables are going to be used in the RR BDD and the EVEN BDD
yy0 = bddvar('yy0')
yy1 = bddvar('yy1') 
yy2 = bddvar('yy2') 
yy3 = bddvar('yy3') 
yy4 = bddvar('yy4')

#The xx variables are going to be used in the RR BDD and the PRIME BDD
zz0 = bddvar('zz0') 
zz1 = bddvar('zz1') 
zz2 = bddvar('zz2') 
zz3 = bddvar('zz3') 
zz4 = bddvar('zz4')

##################################### This didn't work :(
# xx = bddvars('xx',5)
# yy = bddvars('yy',5)
# zz = bddvars('zz',5)

# # Making truth table of even set
# # converting truth table to expression to bdd
# f = truthtable(xx, "10101010101010101010101010101010")
# exp =truthtable2expr(f)
# even_ = expr2bdd(exp)

# f = truthtable(yy,"00010101000101000101000100000101")
# exp =truthtable2expr(f)
# PRIME = expr2bdd((exp))  # The BDD of Prime set
#####################################

#For each element in list pair, look at each character in each element
# if it is a 0 convert it to an equivilent expression of a 0 in an expression EX. ~xx
# join them with an and gate and
exp = ""
for i , j in R:# grabs each tuple
    for num in range(len(i)):
        if not int(i[num]):# This automatically returns a 0 or 1
            exp+= " ~"
            
        exp+= f"xx{num} & " # & to represent the expression has additional elements
    for num in range(len(j)):
        if not int(j[num]):# This automatically returns a 0 or 1
            exp+= " ~"
            
        exp+= f"yy{num} & "
    exp = exp[:-2] + " |" #deletes the & and replaces it with | to represent the start of a new element
exp = exp[:-2]
#boolean expression of all pairs of relationship j ==(i+3) %32 or j == (i+8)%32
exp = expr(exp) #initalize it as a expression to convert to a BDD
RR = expr2bdd(exp) # The BDD of all edges in G

# with open("RR.txt", 'w') as f:
#     f.write(RR.to_dot())

print(f"Number of satisfying input points in BDD RR: {len(list(RR.satisfy_all()))}")
#------------------------------------------------------------
#EVEN

exp = ""
#Creating list of 5 digit binary expression of even nubmers ranging from 0 to 31
even = [bin(i)[2:].zfill(5) for i in range(0,32,2)]
#Building boolean expression for EVEN set
for i in even:
    for j in range(len(i)):
        if not int(i[j]):# This automatically returns a 0 or 1
                exp+= " ~"

        exp+= f"yy{j} &"
    exp = exp[:-2] + " |"
exp = exp[:-2] # deletes the & and replaces it with | to represent the start of a new element

exp = expr(exp)
EVEN = expr2bdd((exp))  # The BDD of even set

# with open("EVEN.txt", 'w') as f:
#     f.write(EVEN.to_dot())

print(f"Number of satisfying input points in BDD EVEN: {len(list(EVEN.satisfy_all()))}")
#------------------------------------------------------------
#PRIME
#Creates list of of prime nubmers from 0 to 31
prime = [3,5,7,11,13,17,19,23,29,31]

#converts list of pime numbers to list of 5 digit binary prime numbers
#Building boolean expression for PRIME set
bi_prime =[]
for i in prime:
    bi_prime.append(bin(i)[2:].zfill(5))
exp = ""

for i in bi_prime:
    for j in range(len(i)):
        if not int(i[j]):# This automatically returns a 0 or 1
                exp+= " ~"

        exp+= f"xx{j} & "
    exp = exp[:-2] + " |"
exp = exp[:-2]

#convert string to expression to BDD
exp = expr(exp)
PRIME = expr2bdd(exp) # The BDD of EVEN set



# with open("PRIME.txt", 'w') as f:
#     f.write(PRIME.to_dot())

print(f"Number of satisfying input points in BDD PRIME: {len(list(PRIME.satisfy_all()))}")
#------------------------------------------------------------
#Step 3.2 - Fixed Point Algorithm

#subsituting the xx variables with another boolean function zz
BDD1 = RR.compose({xx0:zz0, xx1:zz1, xx2:zz2, xx3:zz3, xx4:zz4})
#subsituting the yy variables with another boolean function zz
BDD2 = RR.compose({yy0:zz0, yy1:zz1, yy2:zz2, yy3:zz3, yy4:zz4})

#Applying the existential quantifier on the combination of the two bdds to obtain RR2
RR2 = (BDD1 & BDD2).smoothing((zz0,zz1,zz2,zz3,zz4))

# with open("RR2.txt", 'w') as f:
#     f.write(RR2.to_dot())

print(f"Number of satisfying input points in BDD RR2: {len(list(RR2.satisfy_all()))}")
#------------------------------------------------------------
#Step 3.3 - Modified Fixed Point Algorithm
H = RR2 # creating a second RR2 BDD 
while True:
    H_prime = H # creating a third RR2 BDD
    #calcualting H_prime - the next BDD for next iteration of the number of paths
    t1 = H_prime.compose({yy0:zz0, yy1:zz1, yy2:zz2, yy3:zz3, yy4:zz4})
    t2 = RR2.compose({xx0:zz0, xx1:zz1, xx2:zz2, xx3:zz3, xx4:zz4})
    ans = (t1 & t2).smoothing((zz0,zz1,zz2,zz3,zz4))

    # H is equal to the union of H_prime and the next calcualted iteration of (H_prime o R)
    H = H_prime | ans

    if (H.equivalent(H_prime)):#Found transitive closure and assign result
        break
RR2STAR = H
# with open("RR2STAR.txt", 'w') as f:
#     f.write(RR2STAR.to_dot())

print(f"Number of satisfying input points in BDD RR2STAR: {len(list(RR2STAR.satisfy_all()))}")
#------------------------------------------------------------
#Step 3.4

#Building the conclusion of statement A
FINAL = EVEN & RR2STAR

#Since statement A = A-> B == ~A or B
FINAL = ~PRIME | FINAL.smoothing((yy0,yy1,yy2,yy3,yy4))#Smoothing to apply existential qunatifier on variables yy
#Return truth value for statement A
print(f"Statement A is: {FINAL.equivalent(True)}")

print("Based on the bdd satisfy_one method, ")
if str(FINAL.satisfy_one()) == "{}":
    print("Statement A is a tautology!")
else:
    print("Statement A is a contradiction!")

# with open("FINAL.txt", 'w') as f:
#     f.write(FINAL.to_dot())
