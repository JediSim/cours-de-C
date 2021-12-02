#!/usr/bin/env python3
# encoding: UTF-8     (compatibilité python2)

##################################
## INFO502: TP2
## Rey, Pichenot, groupe L3-CMI

import sys
import re
import datetime

##################################### QUESTION 3 : ####################################
def is_comment(line):
    finSpaces=False
    comment=True
    for i in range(len(line)):
        #on avance jusqu'a ce qu'il y ait autre chose qu'un espace ou qu'une tabulation
        if line[i] != " " and  line[i]!="\t":
            finSpaces=True
        #si on a lu tout les premiers espaces/tabulations
        if finSpaces:
            #si il y a trois % d'affilé alors c'est un commentaire
            if ("%%%" in line[i:i+3]):
                comment=True
            else:
                comment=False
            #on sort de la boucle
            break
    return comment


##################################### QUESTION 6 : #####################################
def link(line):
    return re.sub("(?i)(https?://[^ (),]+)", r"""<a href="\1">\1</a>""", line, flags=re.DOTALL)

def img(line):
    return re.sub("(?i)\[((./|https?://)[^ ()]*)\]", r"""<img src="\1"/>""", line, flags=re.DOTALL)


##################################### QUESTION 7 : #####################################
def todo(r):
    return r.group(0).upper()

def title(r):
    n=str(len(r.group(1)))
    return "\n<h"+n+">"+r.group(3)+"</h"+n+">\n"


##################################### QUESTION 8 & 9 & 13: #####################################
def bold(r):
    return "<b>"+r.group(2)+"</b>"


def under_line(r):
    return "<u>"+r.group(2)+"</u>"

def italic(r):
    return "<i>"+r.group(2)+"</i>"

##################################### QUESTION 10 : #####################################

def link_named(line):
    return re.sub("\[([^ ]+) ([^ ]+)\]", r"""<a href="\2">\1</a>""", line, flags=re.DOTALL)


##################################### QUESTION 11 : #####################################
def rouge(r):
    valide = True
    #on regarde si a la date est valide et on la marque non valide si ce n'est pas le cas
    try:
        datetime.datetime(int(r.group(3)), int(r.group(2)), int(r.group(1)))
    except ValueError:
        valide = False

    #affichage en fonction de la validité de la date
    if not(valide):
        return r"""<font color="red">"""+r.group(0)+r"""</font> """
    else:
        return r.group(0)


#########################################
## fonction à compléter pendant le TP...
def process_line(line):
    ####QUESTION 2
    line = line.replace("<","%lt;")
    line = line.replace(">","%gt;")
    line = line.replace("&","%amp;") 
    #### QUESTION 10
    line = link_named(line)

    ####QUESTION 5
    line=re.sub("(?i)[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,}", "EMAIL", line, flags=re.DOTALL)

    ####QUESTION 6
    #line = link(line)
    line = img(line)

    # QUESTION 6 
    #4/ la modification ne se fait pas car nous modifions d'abord le lien en tant que lien et non en tant qu'image


    #### QUESTION 7.1
    # Todo
    line =re.sub("[ \t]*TODO:.*?[\n]", todo, line, flags=re.DOTALL)

    #### QUESTION 7.2 
    #  titre
    line =re.sub(r"""^((=){1,6})[^=](.*?)[^=]\1\n""", title, line, flags=re.DOTALL)

    #### QUESTION 8 & 9
    #bold
    line =re.sub(r"""(\*\*)([^ \*].*?[^ \*])\1""", bold, line, flags=re.DOTALL)
    
    # underline
    line =re.sub(r"""(__)([^ _].*?[^ _])\1""", under_line, line, flags=re.DOTALL)

    #### QUESTION 11
    # rouge
    line =re.sub(r"""([0-9][0-9])-([0-9][0-9])-(([0-9]){4})""", rouge, line, flags=re.DOTALL)

    #### QUESTION 13
    # italic
    line =re.sub(r"""(?<!http\:)(\/\/)([^ \/].*?[^ \/])\1""", italic, line, flags=re.DOTALL)
    #le regex remaque les // dans les liens. pour fixer le problème il faudrait soit ne pas écrire les liens sous la forme https:// car cette partie serait rajouté dans la fonction link
    #soit il faudrait modifier le regex qui détecte l'italic en précisant de ne pas détecter si les // sont précédé d'un https: ou d'un http:
    #nous avons fait une solution simple, il ne faut pas que les // soit précédé d'un http: (cela ne marche pas pour https)
    
    return line

def FinParagraphe(line):
    # test si on est a la fin d'un paragraphe.
    for char in line:
        # si un des caractères de la ligne est different de l'espace, d'une tabulation ou d'un retour chariot
        if char != ' ' and char != '\t' and char !='\n':
            return False
    return True

############################################################
## fonction principale, appelée depuis la ligne de commandes
def main():
    print("<!--", "-" * 70, "-->")
    p = ""
    for line in sys.stdin:
        ## suppressions des lignes "commentaires"
        ####### QUESTION 4 :    
        if not(re.match("^[ \t]*%%%.*$",line)): 
            p += line 
            if(FinParagraphe(line)):
                # Si on est a la fin du paragraphe
                p = process_line(p)
                if (p.strip("\n\t\r")!=""):
                    print("<p>",p.strip("\n\t\r"),"</p>")
                else:
                    print(p,end='')
                p = ""
                # line = line.strip("\n\r")

    #dernier paragraphe
    if not(re.match("^[ \t]*%%%.*$",line)): 
        p = process_line(p)
        # affichage du paragraphe traitée
        if (p.strip("\n\t\r")!=""):
            print("<p>",p.strip("\n\t\r"),"</p>")
        else:
            print(p,end='')

    print("<!--", "-" * 70, "-->")


if __name__ == "__main__":
    main()


