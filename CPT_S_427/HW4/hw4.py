import passlib as pl
from datetime import datetime

# Open a file named "Password.txt" for reading
pw = open("Password.txt", "r")
# Open a file named "wordList.txt" for reading
wl = open("wordList.txt", "r")

pw_l= [] 
# put password data into datastructure for easy sorting and manipulation
for line in pw:
    pw_l.append(line.strip().split(','))

# Problem #2
sorted_login_list = sorted(pw_l, key=lambda x: int(x[-1]), reverse=False)
for i in range(1,11):
    print(sorted_login_list[-i][2]+":"+sorted_login_list[-i][-1])

# Problem #3
sorted_time_list = sorted(pw_l, key=lambda x: datetime.strptime(x[-2], "%Y%m%dT%H%M%SZ"), reverse=True)
for i in range(1,11):
    print(sorted_time_list[-i][2]+":"+str(datetime.strptime(sorted_time_list[-i][-2], "%Y%m%dT%H%M%SZ")))

# # Open the file in write mode ('w')
# with open('upatedpw.txt', 'w') as file:
#     for line in pw_l:
#         file.write(line[2]+":"+line[4]+"\n")

# print(pw_l)
