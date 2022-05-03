#!/usr/bin/env python3

class Chaine:
    """
    Chaine -> notre type abstait pour les chaines
    String -> les caractères de la chaine

    Sorte : Chaine
    Utilise : String, Bool
    Operations : 
        - __eq__ : Chaine -> Bool
        - __add__ : Chaine -> String
        - __len__ : Chaine -> Int
        - __getitem__ : Int -> String
        - __contains__ : Chaine -> Bool
        - __str__ : Chaine -> String
        - __repr__ : Chaine -> String
        - split : Chaine -> Liste de String
        - annonce : Chaine -> Bool
    """

    def __init__(self, string):
        self.string = string

    def __str__(self) -> str:
        return self.string

    def __repr__(self) -> str:
        return self.string

    def __add__(self, other):
        """
        Ajoutez deux objets String ensemble et renvoyez un nouvel objet String

        :param other: L'autre objet String que vous souhaitez ajouter
        :return: Un nouvel objet String avec la chaîne concaténée.
        """
        if isinstance(other, Chaine):
            return Chaine(self.string + other.string)
        elif isinstance(other, str):
            return Chaine(self.string + other)
        else:
            raise Exception("Cannot add a string and a non-string object")

    def __eq__(self, other):
        """
        "Renvoie True si self.string est égal à other.string."

        :param other: L'autre objet à comparer
        :return: La chaîne de l'objet.
        """
        return self.string == other.string

    def __len__(self):
        """
        Renvoie la longueur de la chaîne
        :return: La longueur de la chaîne.
        """
        return len(self.string)

    def __getitem__(self, index):
        """
        La fonction __getitem__ permet d'utiliser l'opérateur [] sur la classe

        :param index: Index de la chaîne à renvoyer
        :return: Le hachage de la chaîne
        """
        return self.string[index]

    def __setitem__(self, index, string):
        """
        La méthode __setitem__ est appelée lorsqu'un élément est affecté à une tranche d'un itérable.

        :param index: Index de la chaîne à remplacer
        :param string: Chaîne à ajouter à la liste
        """
        raise Exception("Cannot modify a string")

    def __contains__(self, other):
        """
        Renvoie True si l'objet donné est dans l'itérable donné

        :param other: L'objet dont l'appartenance à self est vérifiée
        """
        return other in self.string

    def __hash__(self) -> int:
        """
        Renvoie une valeur de hachage pour l'objet
        """
        return hash(self.string)

    def split(self, sep):
        """
        Cette méthode permet de diviser une chaîne de caractères en un tableau de chaînes de caractères.
        La chaîne de caractères est divisée en un tableau de chaînes de caractères en fonction du séparateur.
        """
        return self.string.split(sep)

    def annonce(self, other):
        """
        indique si une chaine de caractères C annonce une autre chaine B.
        Il faut établir que la chaine c se termine par une sous chaine non-vide a qui commence B
        example : VALEUR annonce EUROPE du fait de la chaine c = EUR
        """
        for shift in range(-1, -len(self.string), -1):
            if other.string.startswith(self.string[shift:]):
                return self.string[shift:]
        return ""


class Pile:
    """
    Operations :
        - empiler : Pile -> Pile
        - depiler : Pile -> element
        - est_vide : Pile -> Bool
        - taille_pile : Pile -> Int
        - affiche : Pile -> String

    p: Pile
    e: element

    Preconditions:
        depiler(p) -> e ssi p non vide (est_vide(p) == False)

    Axiomes :
        est_vide(creer_pile()) == True
        est_vide(empiler(p,e)) == False
        depiler(empiler(p,e)) == e ssi p n'est pas pleine
        empiler(pile_pleine(p),e) == pile_pleine(p)
    """

    def __init__(self, nb_max):
        self.pile = []
        self.taille = nb_max

    def empiler(self, valeur):
        if len(self.pile) == self.taille:
            raise Exception("Pile pleine")
        self.pile.append(valeur)

    def depiler(self):
        if self.est_vide():
            raise Exception("Pile vide")
        return self.pile.pop()

    def est_vide(self):
        return len(self.pile) == 0

    def taille_pile(self):
        return len(self.pile)

    def capa_pile(self):
        return self.taille

    def affiche(self):
        for val in self.pile[::-1]:
            print('|', val, '|')


class PirePile:

    def __init__(self, nb_max):
        self.string = Chaine("")
        self.taille = nb_max

    def _as_array(self):
        ret = self.string.split("\0")[:-1]
        return ret

    def empiler(self, valeur):
        if len(self._as_array()) == self.taille:
            raise Exception("Pile pleine")
        self.string += valeur + "\0"

    def depiler(self):
        if self.est_vide():
            raise Exception("Pile vide")
        ret = self._as_array()[-1]
        reste = self._as_array()[:-1]
        self.string = Chaine("\0".join(reste) + "\0")
        return Chaine(ret)

    def est_vide(self):
        return len(self.string) == 0

    def taille_pile(self):
        return self.string.count("\0")

    def capa_pile(self):
        return self.taille

    def affiche(self):
        for val in self._as_array()[::-1]:
            print('|', val, '|')


def testString():
    T1 = ("", "CATION", "SALON")
    T2 = ("EUROPE", "IONISATION", "NOUVEAU")
    T1 = (Chaine(x) for x in T1)
    T2 = (Chaine(x) for x in T2)

    for s1, s2 in zip(T1, T2):
        print(f"{s1} annonce {s2} : {s1.annonce(s2)}")

    print("================================\n")


def testPile():

    print("empiler ================================\n")

    P1 = Pile(3)
    P1.empiler(Chaine("VALEUR"))
    P1.empiler(Chaine("CATION"))
    P1.empiler(Chaine("SALON"))
    # P1.empiler(Chaine("EUROPE"))
    P1.affiche()

    print("depiler ================================\n")

    P1.depiler()
    P1.depiler()
    P1.depiler()
    # P1.depiler()
    P1.affiche()

    print("empiler pire pile ================================\n")

    P2 = PirePile(3)

    P2.empiler(Chaine("VALEUR"))

    P2.empiler(Chaine("CATION"))
    P2.empiler(Chaine("SALON"))
    # P2.empiler(Chaine("EUROPE"))
    # P2.empiler(Chaine("EUROPE"))

    P2.affiche()

    print("depiler pire pile ================================\n")

    P2.depiler()

    P2.depiler()
    P2.depiler()
    # P2.depiler()
    # P2.depiler()

    P2.affiche()


def promptPile():
    print(">>> ", end="")
    cmd = input().split()
    return [elem for elem in cmd if elem.strip() != ""]


def printPileHelp():
    print("""
pile de Chaine :
    - new capa : Pile
    - empiler elem : Pile -> Pile
    - depiler : Pile -> element
    - est_vide : Pile -> Bool
    - taille : Pile -> Int
    - capa : Pile -> Int
    - affiche : Pile -> String
    - help
    - exit
    """)


if __name__ == "__main__":
    # Menu
    try:

        while True:

            print("""\n1 - Tester annonce\n2 - Tester pile """)

            choix = input("Votre choix : ")

            if choix == "1":
                mot1 = input("Mot 1 : ")
                mot2 = input("Mot 2 : ")
                isAnnoncing = Chaine(mot1).annonce(Chaine(mot2))
                if isAnnoncing:
                    print(f"{mot1} annonce {mot2} avec {isAnnoncing}")
                else:
                    print(f"{mot1} n'annonce pas {mot2}")
            elif choix == "2":
                printPileHelp()
                P1 = Pile(0)
                while True:
                    cmd = promptPile()

                    if cmd[0] not in ("new", "help") and P1.capa_pile() == 0:
                        print("Initialisez la pile")
                        continue

                    if cmd[0] == "empiler":
                        try:
                            P1.empiler(Chaine(cmd[1]))
                        except Exception as e:
                            print(e)
                    elif cmd[0] == "depiler":
                        try:
                            print(P1.depiler())
                        except Exception as e:
                            print(e)
                    elif cmd[0] == "est_vide":
                        print(P1.est_vide())
                    elif cmd[0] == "taille":
                        print(P1.taille_pile())
                    elif cmd[0] == "capa":
                        print(P1.capa_pile())
                    elif cmd[0] == "affiche":
                        P1.affiche()
                    elif cmd[0] == "new":
                        P1 = Pile(int(cmd[1]))
                    elif cmd[0] == "exit":
                        break
                    elif cmd[0] == "help":
                        printPileHelp()
                    else:
                        print("Commande inconnue")

    except KeyboardInterrupt:
        print("\n\nAu revoir")
