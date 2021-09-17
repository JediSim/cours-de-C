#!/usr/bin/env python3
# -*- coding: utf-8 -*-

###
# version naïve
def solve(F, sol, bcp=False):
    """recherche, récursivement, une solution pour un problème SAT
      ``F`` contient la formule considérée, en FNC (liste de liste de nombres)
      ``sol`` contient la solution partielle courante (liste de littéraux).
      L'argument bcp (que vous pouvez ignorer pendant toute la première partie
      du TP) permet d'activer l'optimisation de propagation des clauses
      unitaires.
      La fonction renvoie
        - soit None si la formule n'est pas satisfiable,
        - soit une solution (liste de littéraux) satisfaisant la formule.
    """

    # si F est vide, il n'y a aucune clause et la formule est satisfaite avec
    # la solution courante
    if not F: return sol

    # si F contient la clause vide, cette clause s'évalue à FAUX et la formule
    # n'est donc pas satisfaite avec la solution courante
    if [] in F: return None

    # on prend le premier littéral de la première clause
    lit = F[0][0]
    # on essaie les 2 valeurs possibles pour ce littéral
    return(solve(simplify_formula(F, lit), sol+[lit], bcp=bcp) or
           solve(simplify_formula(F, -lit), sol+[-lit], bcp=bcp))
    # REMARQUE : on utilise ici le fait que les listes non vides de Python
    # sont considérées comme VRAIES alors que la liste vide (ainsi que None)
    # est FAUSSE. On utilise aussi le fait que si le membre gauche d'un "or"
    # s'évalue à VRAI, Python ne calcule pas le membre droit...


def simplify_formula(F, lit):
    """renvoie la formule ``F`` simplifiée lorsqu'on suppose que le littéral
       ``lit`` est vrai :
      - supprime les clauses qui contiennent ``lit`` (elle sont vraies)
      - supprime les littéraux ``-lit`` dans les autres clauses (ce littéral
        est faux)
    """
    simplified_F = []
    for cl in F:
        if -lit in cl:
            tab_inter = []
            for e in cl:
                if (e!=-lit):
                    tab_inter.append(e)

            simplified_F.append(tab_inter)
        elif lit not in cl:
            simplified_F.append(cl)
    return simplified_F


###
# fonction de tests
def test(F, args):
    lit = int(args[0])
    print(f"simplification avec {lit}")
    print("avant :", F)
    Fs = simplify_formula(F, lit)
    print("après :", Fs)


###
# optimisation pour avoir un algo de style "DPLL
def BCP(F):
    """simplifie la formule avec la propagation des clauses unitaires
    La fonction renvoie une paire contenant la formule simplifiée et la liste
    des littéraux simplifiés.
    """
    sol = []
    # ...    # TODO
    return F, sol


##############################################################################
##############################################################################
# ************************************************************************** #
# * normalement, vous n'avez pas besoin de modifier la suite du fichier... * #
# ************************************************************************** #
##############################################################################
##############################################################################


#########################
# fonctions utilitaires
def message(*args, **kwargs):
    print(*args, **kwargs, file=stderr)


def parse_DIMACS(filename=""):
    """lit un fichier DIMACS dans un fichier (ou l'entrée standard) et renvoie
    une liste de liste de nombres
    Chaque nombre représente un littéral,
    chaque liste représente une clause,
    la liste externe représente la formule.

    Remarque : la ligne 'p cnf <nb_var> <nb_clauses>' est ignorée.
    """
    if filename and filename != "-":
        input_file = open(filename)
    else:
        from sys import stdin
        input_file = stdin

    F = []          # la formule finale
    for line in input_file:
        line = line.strip()
        if line.startswith("c"):    # commentaire
            continue
        if line.startswith("p"):    # paramètres du problème, ignorés
            continue
        if not line:
            continue
        cl = list(map(int, line.split()))
        last = cl.pop()
        assert last == 0
        assert 0 not in cl
        F.append(cl)
    return F


def save_DIMACS(F, filename="", header=""):
    """écrit la formule au format DIMACS (dans un fichier ou sur la sortie
    standard)"""
    if filename and filename != "-":
        output_file = open(filename, mode="w")
    else:
        from sys import stdout
        output_file = stdout

    if header:
        for l in header.split("\n"):
            output_file.write(f"c {l}\n")

    if TRANSLATION:
        output_file.write(f"c translation table for variable names: \n")
        for i in range(1, len(TRANSLATION)):
            output_file.write(f"c     {TRANSLATION[i]} -> {i}\n")

    nb_var, nb_clauses, _ = parameters(F)
    output_file.write(f"p cnf {nb_var} {nb_clauses}\n")

    for cl in F:
        for lit in cl:
            output_file.write(f"{lit} ")
        output_file.write("0\n")


def parse_SAT(filename=""):
    """lit un fichier au format 'sat' dans un fichier (ou l'entrée standard)
    et renvoie une liste de liste de nombres représentant la formule, ainsi
    que :
      - un dictionnaire qui donne, pour chaque variable textuelle, son numéro
      - une liste qui donne, pour chaque indice de variable, son texte
    """
    import re

    if filename and filename != "-":
        input_file = open(filename)
    else:
        from sys import stdin
        input_file = stdin

    index = {"": 0}     # dictionnary: for each textual variable, gives its index
    text = [""]         # list: for each index, give the corresponding textual variable

    F = []          # la formule finale
    i = 0
    for line in input_file:
        i += 1
        # if (i % 1000000 == 0):
        #     message(f" {i} clauses read")
        # elif (i % 10000 == 0):
        #     message(".", flush=True, end="")

        line = line.strip()
        if line.startswith("#"):    # commentaire
            continue
        if not line:                # ligne vide
            continue
        variables = line.split()
        cl = []
        for v in variables:
            sign = 1
            if v.startswith("-"):
                sign = -1
                v = v[1:]
            if not re.fullmatch(r"[A-Za-z0-9_@]+", v):
                message(f"*** invalid variable name: '{v}' on line {i}")
                exit(3)

            x = index.get(v)
            if x is None:
                x = len(index)
                index[v] = x
                text.append(v)
            cl.append(sign * x)
        F.append(cl)
    return F, index, text


def print_sol(sol):
    """affiche une solution"""
    if TRANSLATION is None:
        sol = sorted(sol, key=abs)  # on trie les littéraux par ordre croissant
        for i in range(len(sol)):
            print(sol[i], end=" ")
        print(0)
    else:
        for i in range(len(sol)):
            if sol[i] < 0 and EXCLUDE_NEGATIVE_LIT:
                continue
            x = abs(sol[i])
            s = "" if sol[i] > 0 else "-"
            v = TRANSLATION[x]
            if not v.startswith("_"):   # do not show literals starting with _
                print(f"{s}{v}", end=" ")
        print()


def parameters(F):
    """renvoie le nombre de variables, le nombre de clauses et le nombre de
    littéraux d'une formule en FNC"""
    nb_clauses = len(F)
    last_var = 0
    nb_lit = 0
    for cl in F:
        last_var = max(last_var, max(map(abs, cl)))
        nb_lit += len(cl)

    return last_var, nb_clauses, nb_lit


def randomize_formula(F):
    """mélange les clauses d'une formule et les littéraux de chaque clause"""
    from random import shuffle
    shuffle(F)
    for cl in F:
        shuffle(cl)


###
# les fonctions principales
def main_naive(F):
    """fonction principale pour la résolution naïve"""
    solution = solve(F, [], bcp=False)
    if solution is not None:
        print("SATISFIABLE")
        print_sol(solution)
        exit(0)

    else:
        print("UNSATISFIABLE")
        exit(1)


def main_all(F):
    """fonction principale pour le calcul naïf de toutes les solutions"""
    n = 0
    while True:
        S = solve(F, [])
        if S is None:
            break
        n += 1
        print_sol(S)
        F.append([-l for l in S])

    if n is None:
        exit(1)
    elif n == 0:
        print("UNSATISFIABLE")
        exit(1)
    else:
        print(f"SATISFIABLE: {n} solution(s) found")
        exit(0)


def main_DPLL(F):
    """fonction principale pour la résolution récurvise DPLL"""
    solution = solve(F, [], bcp=True)
    if solution is not None:
        print("SATISFIABLE")
        print_sol(solution)
        exit(0)
    else:
        print("UNSATISFIABLE")
        exit(1)


###


def help(exe):
    print(f"utilisation {exe} [options] [FICHIER_ENTREE [FICHIER_SORTIE]] ")
    print("""
Si FICHIER_ENTREE n'est pas donné, la formule sera lue sur l'entrée standard.
Si FICHIER_SORTIE n'est pas donné, le résultat sera affiché sur la sortie standard.

Si le format d'entrée n'est pas précisé, la formule est lue :
  - au format 'SAT' si le fichier a l'extension '.sat'
  - au format 'DIMACS' si le fichier a l'extension '.cnf'
Dans les autres cas, (par exemple, lorsque la formule est lue sur l'entrée
standard), le format 'SAT' est utilisé.

options disponibles :
  -N  /  --naive                    utilise la variante récursive naive de l'algorithme
  -A  /  --all                      utilise la variante qui affiche toutes les solutions
  -D  /  --DPLL                     utilise la variante récursive de l'algorithme DPLL
  -O  /  --output                   affiche seulement la formule au format DIMACS, sans recherche de solution
  -T  /  --test                     lance la fonction de tests
  -r  /  --randomize                mélange la formule avant de lancer l'algorithme
  -v  /  --verbose                  affiche quelques informations supplémentaires sur la formule
  -s  /  --sat                      force le format 'sat' pour lire la formule
  -d  /  --dimacs                   force le format 'DIMACS' pour lire la formule
  -X  /  --exclude-negative-lit     n'affiche pas les littéraux négatifs dans les solutions
""")


if __name__ == "__main__":
    from getopt import gnu_getopt, GetoptError
    from sys import argv, exit, stderr
    import sys

    short_options = "NADOTsdrvhX"
    long_options = ["naive", "all", "DPLL", "output", "test", "sat", "dimacs", "randomize", "verbose", "help", "exclude-negative-lit"]

    try:
        opts, args = gnu_getopt(argv[1:], short_options, long_options)
    except GetoptError as err:
        message(err)
        help(argv[0])
        exit(2)

    algorithm = "naive"
    randomize = False
    verbose = 0
    input_filename = "-"        # stdin
    file_format = None
    TRANSLATION = None
    EXCLUDE_NEGATIVE_LIT = False
    output_filename = "-"       # stdout

    for o, a in opts:
        if o in ["-h", "--help"]:
            help(argv[0])
            exit(0)
        elif o in ["-N", "--naive"]:
            algorithm = "naive"
        elif o in ["-A", "--all"]:
            algorithm = "all"
        elif o in ["-D", "--DPLL"]:
            algorithm = "DPLL"
        elif o in ["-O", "--output"]:
            algorithm = "output_formula"
        elif o in ["-T", "--test"]:
            algorithm = "test"
        elif o in ["-r", "--randomize"]:
            randomize = True
        elif o in ["-v", "--verbose"]:
            verbose += 1
        elif o in ["-s", "--sat"]:
            file_format = "SAT"
        elif o in ["-d", "--dimacs"]:
            file_format = "DIMACS"
        elif o in ["-X", "--exclude-negative-lit"]:
            EXCLUDE_NEGATIVE_LIT = True
        else:
            message("You shouldn't see this!")
            exit(3)

    if len(args) == 0:
        message(">>> no filename: read SAT formula from stdin and write result on stdout")
        message(f">>> use  {argv[0]} --help  for help")

    if len(args) > 2 and algorithm != "test":
        message("too many arguments")
        exit(1)

    if len(args) >= 1:
        input_filename = args.pop(0)
    if len(args) >= 1 and algorithm != "test":
        output_filename = args[0]

    if file_format is None:
        if not input_filename:
            file_format = "SAT"
        else:
            if input_filename.lower().endswith(".sat"):
                file_format = "SAT"
            elif input_filename.lower().endswith(".cnf") or input_filename.lower().endswith(".dimacs"):
                file_format = "DIMACS"
            else:
                file_format = "SAT"

    # ???
    # if output_filename and output_filename != "-":
    #     sys.stdout = open(output_filename, mode="w")

    if verbose > 1:
        message(f">>> formula is read from {input_filename if input_filename else 'stdin'}, in {file_format} format")
        if algorithm == "naive":
            message(">>> the naive algorithm will be used, ")
        elif algorithm == "all":
            message(">>> the naive algorithm computing all solutions will be used, ")
        elif algorithm == "DPLL":
            message(">>> the recursive DPLL algorithm will be used, ")
        message(f">>> the result will be output to {output_filename if output_filename else 'stdout'}")

    if file_format == "DIMACS":
        F = parse_DIMACS(input_filename)
    elif file_format == "SAT":
        F, _, TRANSLATION = parse_SAT(input_filename)

    if verbose > 0:
        nb_var, nb_clauses, nb_lit = parameters(F)
        message(f">>> the formula contains {nb_var} variables and {nb_clauses} clauses, "
                f"for a total of {nb_lit} literals")

    if randomize:
        verbose > 1 and message(">>> randomizing the formula...")
        randomize_formula(F)

    if algorithm == "naive":
        main_naive(F)
    elif algorithm == "all":
        main_all(F)
    elif algorithm == "DPLL":
        main_DPLL(F)
    elif algorithm == "output_formula":
        save_DIMACS(F)
    elif algorithm == "test":
        test(F, args)
    else:
        message("You shouldn't see this!")
        exit(3)
