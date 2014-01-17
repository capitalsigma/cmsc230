from sys import argv
from random import randrange

MAX_VAL = 1000

def main(n_verticies):
    print(n_verticies)
    for i in range(0, n_verticies):
        for j in range(0, n_verticies):
            print(randrange(MAX_VAL) if i != j else 0, ' ', end='')
        print("")

main(int(argv[1]))
            
