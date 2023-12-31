#!/usr/bin/python3

import sys

def factorize(n):

    factor = 2
    factors = []

    while factor * factor <= n:
        if n % factor == 0:
            factors.append(factor)
            n //= factor
        else:
            factor += 1

    if n > 1:
        factors.append(n)


    return factors

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: {} <file>".format(sys.argv[0]))
        sys.exit(1)

    input_file = sys.argv[1]

    try:
        with open(input_file, 'r') as file:
            for line in file:
                n = int(line.strip())
                factors_list = factorize(n)
                factors_str = '*'.join(map(str, factors_list))
                print("{}={}".format(n, factors_str))
    except FileNotFoundError:
        print("File not fount: {}".format(input_file))
        sys.exit(1)
