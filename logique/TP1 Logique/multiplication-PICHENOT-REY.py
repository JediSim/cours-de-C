#!/usr/bin/env python3

# global variable
last_aux = 0

VERBOSE = False


def log(*args, **kwargs):
    if VERBOSE:
        print(*args, **kwargs)


def new_aux():
    global last_aux
    last_aux += 1
    return f"x_{last_aux}"      # I could hide that variable


def equal(x, y):
    log(f"# >>> {x} := {y}")
    print(f"-{x} {y}")
    print(f"-{y} {x}")
    log()


def xor2(r, x, y):
    log(f"# >>> {r} := {x} ⊕ {y}")
    print(f"-{x} {y} {r}")
    print(f"{x} -{y} {r}")
    print(f"{x} {y} -{r}")
    print(f"-{x} -{y} -{r}")
    log()


def carry2(r, x, y):
    log(f"# >>> {r} := {x} ∧ {y}")
    print(f"{x} -{r}")
    print(f"{y} -{r}")
    print(f"-{x} -{y} {r}")
    log()


and2 = carry2


def xor3(r, x, y, z):
    log(f"# >>> {r} := {x} ⊕ {y} ⊕ {z}")
    print(f"-{x} {y} {z} {r}")
    print(f"{x} -{y} {z} {r}")
    print(f"{x} {y} -{z} {r}")
    print(f"{x} {y} {z} -{r}")
    print(f"-{x} -{y} -{z} {r}")
    print(f"-{x} -{y} {z} -{r}")
    print(f"-{x} {y} -{z} -{r}")
    print(f"{x} -{y} -{z} -{r}")
    log()


def carry3(r, x, y, z):
    log(f"# >>> {r} := ⟨{x} {y} {z}⟩")
    print(f"{x} {y} {z} -{r}")
    print(f"{x} {y} -{z} -{r}")
    print(f"{x} -{y} {z} -{r}")
    print(f"-{x} {y} {z} -{r}")
    print(f"-{x} -{y} {z} {r}")
    print(f"-{x} {y} -{z} {r}")
    print(f"{x} -{y} -{z} {r}")
    print(f"-{x} -{y} -{z} {r}")
    log()


def multiplier(n1, n2):
    n = n1 + n2

    Bin = [[] for _ in range(n+1)]

    for i in range(n1):
        for j in range(n2):
            q = f"q_{i}_{j}"                # I could hide that variable
            and2(q, f"a_{i}", f"b_{j}")
            Bin[i+j].append(q)

    for k in range(n):
        assert Bin[k]

        log(f"# >>>>>> Bin[{k}] = {Bin[k]}")
        while Bin[k]:
            if len(Bin[k]) == 1:
                equal(f"p_{k}", Bin[k].pop())        # I could hide that variable
                assert not Bin[k]
                break

            if len(Bin[k]) == 2:
                a = Bin[k].pop()
                b = Bin[k].pop()
                xor2(f"p_{k}", a, b)        # I could hide that variable
                c = new_aux()
                carry2(c, a, b)
                Bin[k+1].append(c)
                assert not Bin[k]
                break

            r = new_aux()
            x = new_aux()
            a = Bin[k].pop()
            b = Bin[k].pop()
            c = Bin[k].pop()
            xor3(r, a, b, c)
            carry3(x, a, b, c)
            Bin[k].append(r)
            Bin[k+1].append(x)


def help(exe):
    print(f"utilisation: {exe} n1 n2 [p]")
    print("""
  - n1 est le nombre de bits pour a
  - n2 est le nombre de bits pour b
  - p est le produit, qui doit tenir sur n1+n2 bits""")


if __name__ == "__main__":
    from sys import argv, exit, stderr

    try:
        n1 = int(argv[1])
        n2 = int(argv[2])
    except (ValueError, IndexError):
        help(argv[0])
        exit(1)

    n = n1 + n2

    try:
        p = int(argv[3])
    except IndexError:
        from random import randrange
        p = randrange(0, randrange(0, 2**n))
        print(f">>> no 'p' number given, using {p}", file=stderr)
    except ValueError:
        print(f"invalid 'p' number: {p}", file=stderr)
        exit(1)

    # entêtes
    print(f"# n1 = {n1}, n2 = {n2}, n = {n}, p = {p}")
    print(f"# les bits de a et b (facteurs de p) sont contenus dans les bits a_0 a_1 ... a_n1 et b_0 b_1 ... b_n2")

    # NOTE:
    #   les nombres a et b sont contenus dans les bits a_0 ... a_n1 et b_0 ... b_n2
    #   le produit p est contenu dans les bits p_0 ... p_n
    #   les autres variables (x_1, ...) sont des variables auxiliaires pour les résultats intermédiaires

    # clauses correspondant au circuit multiplicateur
    multiplier(n1, n2)

    # les bits p_0 ... p_n sont bien les bits de p
    # TODO
    bnr=bin(p).replace('0b','')
    x=bnr[::-1]
    while len(x)<n:
        x+='0'
    bnr = x[::]
    for i in range(len(bnr)):
        if bnr[i] == '1':
            print(f"p_{i}")
        else:
            print(f"-p_{i}")
