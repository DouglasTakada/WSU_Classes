from math import gcd as bltin_gcd
# ITG!AAEXEX IRRG!IGRXI OIXGEREAGO = 4739112828 4663943684 5483262135

def cifer_to_digit(input):
    txt = ""
    for i in input:
        if i == 'A':
            txt +='1'
        elif i == 'E':
            txt +='2'
        elif i == 'G':
            txt +='3'
        elif i == 'I':
            txt +='4'
        elif i == 'O':
            txt +='5'
        elif i == 'R':
            txt +='6'
        elif i == 'T':
            txt +='7'
        elif i == 'X':
            txt +='8'
        elif i == '!':
            txt +='9'
        elif i == '0':
            txt +='0'
        elif i == ' ':
            txt += ' '
        else:
            print("Invalid letter in cipher")
    return txt

def digit_to_text(digits):
    txt = ""
    str_digits = str(digits)
    for i in str_digits:
        if i == '1':
            txt +='A'
        elif i == '2':
            txt +='E'
        elif i == '3':
            txt +='G'
        elif i == '4':
            txt +='I'
        elif i == '5':
            txt +='O'
        elif i == '6':
            txt +='R'
        elif i == '7':
            txt +='T'
        elif i == '8':
            txt +='X'
        elif i == '9':
            txt +='!'
        elif i == '0':
            txt +='0'
        elif i == ' ':
            txt += ' '
        else:
            print("Invalid digit in input to convert to string")
    return txt

#Code from: https://stackoverflow.com/questions/39678984/efficiently-
#           check-if-two-numbers-are-co-primes-relatively-primes
def coprime2(a, b):
    return bltin_gcd(a, b) == 1

#now trying to find d
def find_d(p1, p2):#prime1 and prime2
    #function phi:
    phi = (p1-1)*(p2-1) # Number of Co-Primes
    for i in range(phi):
        if 49*i % phi == 1: #looking for potential d values
            print(i) # 3226366849
    
c0 = int(cifer_to_digit("ITG!AAEXEX"))
c1 = int(cifer_to_digit("IRRG!IGRXI"))
c2 = int(cifer_to_digit("OIXGEREAGO"))
print(digit_to_text(c0),digit_to_text(c1),digit_to_text(c2))
print(c0,c1,c2)
e = 49
n = 10539750919
PHI = (43481-1)*(242399-1)
#Found Prime numbers that multiply to this number: 43481 242399
#find_d(43481, 242399) # takes too long
d = 3226366849
res0 = pow(c0,d,n)
res1 = pow(c1,d,n)
res2 = pow(c2,d,n)
print(res0,res1,res2)
print(digit_to_text(res0),digit_to_text(res1),digit_to_text(res2))

#Double checking that the decipher value is correct
r0 = int(cifer_to_digit("GREAT"))
r1 = int(cifer_to_digit("!XIXG"))
r2 = int(cifer_to_digit("OTXIT"))

res3 = pow(r0,e,n)
res4 = pow(r1,e,n)
res5 = pow(r2,e,n)
print(digit_to_text(res3) == "ITG!AAEXEX")
print(digit_to_text(res4) == "IRRG!IGRXI")
print(digit_to_text(res5) == "OIXGEREAGO")


#brand new encoding with given ascii table: 

r3 = int(cifer_to_digit("XORGATE"))

encoded = pow(r3,e,n)
decoded = pow(encoded, d, n)
print(digit_to_text(decoded) == "XORGATE")
