import passlib as pl
from datetime import datetime

# Open a file named "demofile.txt" for reading
pw = open("Password.txt", "r")
# Open a file named "demofile.txt" for reading
wl = open("wordList.txt", "r")

pw_l= []

# put password data into datastructure for easy sorting and manipulation
for line in pw:
    pw_l.append(line.strip().split(','))

# sorted_login_list = sorted(pw_l, key=lambda x: int(x[-1]), reverse=True)
# print(sorted_login_list[:10])

sorted_time_list = sorted(pw_l, key=lambda x: datetime.strptime(x[-2], "%Y%m%dT%H%M%SZ"), reverse=True)
# print(sorted_time_list[:10])

print(sorted_time_list[-1][2],datetime.strptime(sorted_time_list[-1][-2], "%Y%m%dT%H%M%SZ"))
print(datetime.strptime(sorted_time_list[-2][-2], "%Y%m%dT%H%M%SZ"))
print(datetime.strptime(sorted_time_list[-3][-2], "%Y%m%dT%H%M%SZ"))
print(datetime.strptime(sorted_time_list[-4][-2], "%Y%m%dT%H%M%SZ"))
print(datetime.strptime(sorted_time_list[-5][-2], "%Y%m%dT%H%M%SZ"))

# print(datetime.strptime(sorted_time_list[1][-2], "%Y%m%dT%H%M%SZ"))
# print(datetime.strptime(sorted_time_list[2][-2], "%Y%m%dT%H%M%SZ"))
# print(datetime.strptime(sorted_time_list[3][-2], "%Y%m%dT%H%M%SZ"))
# print(datetime.strptime(sorted_time_list[4][-2], "%Y%m%dT%H%M%SZ"))
# print(datetime.strptime(sorted_time_list[5][-2], "%Y%m%dT%H%M%SZ"))


# # Open the file in write mode ('w')
# with open('upatedpw.txt', 'w') as file:
#     for line in pw_l:
#         file.write(line[2]+":"+line[4]+"\n")

# print(pw_l)
