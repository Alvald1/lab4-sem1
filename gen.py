from random import choice
a='qwertyuiopasdfghjklzxcvbnm '
b=''
for i in range(1,11):
    with open('datasets/'+str(i*10000)+'.txt', 'w') as file:
        file.write(''.join([choice(a) for j in range(i*10000)]))
        file.write('\n')
