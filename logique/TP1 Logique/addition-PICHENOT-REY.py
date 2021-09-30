#!/usr/bin/env python3


def xor3(s, a, b, c):
    print(f"-{a} -{b} -{c} {s}")
    print(f"-{a} -{b} {c} -{s}")
    print(f"-{a} {b} -{c} -{s}")
    print(f"{a} -{b} -{c} -{s}")
    print(f"{a} {b} {c} -{s}")
    print(f"{a} {b} -{c} {s}")
    print(f"{a} -{b} {c} {s}")
    print(f"-{a} {b} {c} {s}")


def carry3(cc, a, b, c):
    print(f"{a} {b} {c} -{cc}")
    print(f"{a} {b} -{c} -{cc}")
    print(f"{a} -{b} {c} -{cc}")
    print(f"-{a} {b} {c} -{cc}")
    print(f"-{a} -{b} {c} {cc}")
    print(f"-{a} {b} -{c} {cc}")
    print(f"{a} -{b} -{c} {cc}")
    print(f"-{a} -{b} -{c} {cc}")


if __name__ == "__main__":
    from sys import argv, exit, stderr

    try:
        n = int(argv[1])
    except (ValueError, IndexError):
        print("expect one (or two) number(s) as argument", file=stderr)
        exit(1)

    try:
        s = int(argv[2])
    except IndexError:
        from random import randrange
        s = randrange(0, randrange(0, 2**n))
        print(f"no 's' number given, using {s}", file=stderr)
    except ValueError:
        print(f"invalid 's' number: {s}", file=stderr)
        exit(1)

    # les contraintes sur les bits du résultat
    # TODO
    bnr=bin(s).replace('0b','')
    x=bnr[::-1]
    while len(x)<n:
        x+='0'
    bnr = x[::]
    for i in range(len(bnr)):
        if bnr[i] == '1':
            print(f"s{i}")
        else:
            print(f"-s{i}")
    
    print("-c0")

    # appels aux fonction xor3 et carry3 sur tous les bits
    # TODO
    for i in range(n):
        xor3(f"s{i}",f"a{i}",f"b{i}",f"c{i}")
        carry3(f"c{i+1}",f"a{i}",f"b{i}",f"c{i}")
