import random, string

def randomString(stringLength):
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(stringLength))

file = open('test.txt', 'w')

d = dict()
tt = 10000

for i in range(tt):
	s = randomString(i % 254 + 1)
	n = str(random.randint(1, 12312312312))
	d[s] = n
	file.write('+ ')
	file.write(s)
	file.write(' ')
	file.write(n)
	file.write('\n')

for i in range(tt):
	s = randomString(i % 253 + 1)
	file.write('- ')
	file.write(s)
	file.write('\n')

for i in range(1):
	file.write('! Save f')
	file.write('\n')

for i in range(1):
	file.write('! Load f')
	file.write('\n')
	
for i in d:
	file.write('- ')
	file.write(i)
	file.write('\n')

file.close()