from random import *

template = '{test}\n'

with open('test', 'w') as f:
    for i in range(1, 10000000):
        if i == 1:
            f.write(template.format(**{'test': ''.join(choice('abcdefghijklmnopqrstuvwxyz') for _ in range(1000))}))
        else:
            f.write(template.format(
                **{'test': ''.join(choice('abcdefghijklmnopqrstuvwxyz') for _ in range(randint(1, 10)))}))
