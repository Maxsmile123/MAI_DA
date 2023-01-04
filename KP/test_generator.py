import os
from random import *

tests_dir = "Tests"
template = 'test{}'
hm = '{test}'

list_of_N = [1000, 10000, 100000, 1000000, 10000000]
list_of_dim = [2, 10, 100, 200, 500, 1000]
list_of_Q = [1000, 10000, 100000, 1000000, 10000000]


def generate_queries(filename: str, q: int, dim: int):
    list_of_data = []
    list_of_data.append(q)
    with open(filename, 'a') as f:
        f.write(' ')
        for _ in range(q):
            for _ in range(dim):
                list_of_data.append(randint(1, 1000))
        for i, elem in enumerate(list_of_data):
            list_of_data[i] = str(elem)
        f.write(hm.format(test=' '.join(list_of_data)))


def generate_tree_data(filename: str, n: int, dim: int):
    list_of_data = []
    with open(filename, 'w') as f:
        list_of_data.append(n)
        list_of_data.append(dim)
        for _ in range(n):
            for _ in range(dim):
                list_of_data.append(randint(1, 1000))
        for i, elem in enumerate(list_of_data):
            list_of_data[i] = str(elem)
        f.write(hm.format(test=' '.join(list_of_data)))


def test():
    filename = os.path.join(tests_dir, 'test')
    list_of_data = [1, 2, 15, 16]
    for i, elem in enumerate(list_of_data):
        list_of_data[i] = str(elem)
    with open(filename, 'w') as f:
        f.write(hm.format(test=' '.join(list_of_data)))


def main():
    if not os.path.exists(tests_dir):
        os.mkdir(tests_dir)
    test()
    i = 0
    for n in list_of_N:  # generate tests with only n changing
        filename = os.path.join(tests_dir, template.format(i))
        generate_tree_data(filename, n, 2)
        generate_queries(filename, 10, 2)
        i += 1
    for d in list_of_dim:  # generate tests with only dim changing
        filename = os.path.join(tests_dir, template.format(i))
        generate_tree_data(filename, 1000, d)
        generate_queries(filename, 10, d)
        i += 1
    for q in list_of_Q:  # generate tests with only queries changing
        filename = os.path.join(tests_dir, template.format(i))
        generate_tree_data(filename, 1000, 2)
        generate_queries(filename, q, 2)
        i += 1


main()
