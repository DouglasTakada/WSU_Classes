import rsa
 
publicKey, privateKey = rsa.newkeys(512)

resData = "Resident Data"

encMessage = rsa.encrypt(resData.encode(), publicKey)
 
print("original string: ", resData)
print("encrypted string: ", encMessage)
 
decMessage = rsa.decrypt(encMessage, privateKey).decode()
 
print("decrypted string: ", decMessage)
