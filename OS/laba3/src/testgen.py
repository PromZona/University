import random

file = open("test1.txt", "w")

for i in range(0, 1055976):
    a = random.randint(0,1)
    file.write(str(a))


file.close()
