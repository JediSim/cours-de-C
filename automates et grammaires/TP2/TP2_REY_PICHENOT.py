#!/usr/bin/env python3
# encoding: UTF-8     (compatibilité python2)

##################################
## INFO502: TP2
## Charlie Brown, groupe L3-info-a

import sys
import re
import datetime

##################################### QUESTION 3 : ####################################
def is_comment(line):
    finSpaces=False
    comment=True
    for i in range(len(line)):
        if line[i] != " " and  line[i]!="\t":
            finSpaces=True
        if finSpaces:
            if ("%%%" in line[i:i+3]):
                comment=True
            else:
                comment=False
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
    return "<h"+n+">"+r.group(3)+"</h"+n+">"


##################################### QUESTION 8 & 9: #####################################
def bold(r):
    return "<b>"+r.group(2)+"</b>"


def under_line(r):
    return "<u>"+r.group(2)+"</u>"

##################################### QUESTION 10 : #####################################

def link_named(line):
    return re.sub("\[([^ ]+) ([^ ]+)\]", r"""<a href="\2">\1</a>""", line, flags=re.DOTALL)


##################################### QUESTION 11 : #####################################
def rouge(r):
    valide = True
    try:
        datetime.datetime(int(r.group(3)), int(r.group(2)), int(r.group(1)))
    except ValueError:
        valide = False

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
    line =re.sub("[ \t]*TODO:.*?[\n]", todo, line, flags=re.DOTALL)

    #### QUESTION 7.2
    line =re.sub(r"""(=+)([^=]*)\\1[\n]""", title, line, flags=re.DOTALL)

    #### QUESTION 8 & 9
    #bold
    line =re.sub(r"""(\*\*)([^ \*].*?[^ \*])\1""", bold, line, flags=re.DOTALL)
    
    # underline
    line =re.sub(r"""(__)([^ _].*?[^ _])\1""", under_line, line, flags=re.DOTALL)

    #### QUESTION 11
    # rouge
    line =re.sub(r"""([0-9][0-9])-([0-9][0-9])-(([0-9]){4})""", rouge, line, flags=re.DOTALL)

    return line

def FinParagraphe(line):
    for char in line:
        if char != ' ' and char != '\t':
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
                print(p, end='')
                p = ""

    #dernier paragraphe
    if not(re.match("^[ \t]*%%%.*$",line)): 
        p = process_line(p)
        # affichage du paragraphe traitée
        print(p)

    print("<!--", "-" * 70, "-->")


if __name__ == "__main__":
    main()
