import secrets, string

alphabet = string.digits
token = ''.join(secrets.choice(alphabet) for i in range(6))

alfa = string.ascii_letters + string.digits
tempPass = ''.join(secrets.choice(alfa) for i in range(15))
print (token)
print (tempPass)