REY PICHENOT

I/ Modélisation et import

A) NOEUDS

LOAD CSV WITH HEADERS FROM "https://www.dropbox.com/s/yho5i7kqocpkh9r/u.item.csv?dl=1"
AS row FIELDTERMINATOR '|' WITH row LIMIT 1000
CREATE (n:Film)
SET n = row,
    n.id=toInteger(row.id);

LOAD CSV WITH HEADERS FROM "https://www.dropbox.com/s/elx8mpelj2gzifx/u.genre.csv?dl=1"
AS row FIELDTERMINATOR '|' WITH row LIMIT 1000
CREATE (g:Genre)
SET g = row,
    g.id=toInteger(row.id);

LOAD CSV WITH HEADERS FROM "https://www.dropbox.com/s/wrn39wxggo8ozfl/u.user.csv?dl=1"
AS row FIELDTERMINATOR '|' WITH row LIMIT 1000
CREATE (u:User)
SET u = row,
    u.id=toInteger(row.id);

B) RATINGS

:auto USING PERIODIC COMMIT 100
LOAD CSV WITH HEADERS FROM "https://www.dropbox.com/s/vmtjxr22q4fflr1/u.data.csv?dl=1"
AS row FIELDTERMINATOR '|' WITH row
MATCH (f:Film) with f, row
MATCH  (u:User) with f,u,row 
WHERE f.id=toInteger(row.id_item) AND u.id=toInteger(row.id_user)
CREATE (u)-[d:RATING]->(f)
SET d.rating=row.rating
return f,u,d limit 25;

C) CATEGORIES

MATCH (f:Film) WITH f
MATCH (g:Genre) where f[g.type] = "1"
WITH f,g
CREATE (f)-[r:APPARTIENT]->(g);

II/ Système de recommendation

2.1) Similarité


MATCH (u1:User)--(f1:Film)--(u2:User) 
WITH u1, count(distinct f1) as commun, u2
WHERE commun>1                                       // Empecher les similarités de 100 %
MATCH (u1)--(f1:Film)
WITH u1,commun,count(distinct f1) as nbr1, u2
MATCH (u2)--(f2:Film)
WITH u1,commun,nbr1,count(distinct f2) as nbr2,u2
return u1,100*commun/(nbr1+nbr2-commun) as sim,u2
order by sim desc LIMIT 10


On a a rajouté le WHERE commun>1 pour enlever la similiratité de 100 % qui n'est pas interessante pour nous


On veux maintenant rajouter les notes afin d'affiner la recommendation.

MATCH (u1:User)-[r1:RATING]-(f1:Film)-[r2:RATING]-(u2:User) 
WITH u1, count(distinct f1) as commun, f1.name as filmscommuns,  u2, abs(toInteger(r1.rating)-toInteger(r2.rating)) as ecartnote
WHERE commun>10 AND ecartnote<=2
MATCH (u1)--(f1:Film)
WITH u1,commun,count(distinct f1) as nbr1, u2,filmscommuns
MATCH (u2)--(f2:Film)
WITH u1,commun,nbr1,count(distinct f2) as nbr2,u2,filmscommuns
MATCH (u2)-[r1:RATING]-(suggestion:Film)
WITH  u1,100*commun/(nbr1+nbr2-commun) as sim,u2,r1,commun,suggestion,filmscommuns
WHERE sim >15 AND NOT suggestion.name in filmscommuns
return suggestion,filmscommuns

Cette requête ne marche pas, nous ne comprennons pas pourquoi :(

Nous souhaitons donc faire un algorithme qui recommande des films.


[*]==[*]==[*]==[*]==[*]==[*]==[*]==[*]==[*]==[*]
||		ALGORITHME DE RECOMMENDATION 		  ||
[*]==[*]==[*]==[*]==[*]==[*]==[*]==[*]==[*]==[*]

*********
*INITIAL*
*********

A cette étape, l'algo renvoie une suggestion de films basé sur les films bien noté de tout les utilisateurs qui on vu les mêmes films que l'utilisateur d'id 1, on appelera cet utilisateur u1. Les recommendations sont faites pour u1.
Pour des raisons de simplicité et de développement on renvoie la quantité de films proposé pour le moment afin de voir rappidement si les ajouts à l'algorithme effectué plus tard sont pertinents.

MATCH (u1:User)-[r1:RATING]-(f1:Film)-[r2:RATING]-(u2:User)
WITH u1,u2,f1
WHERE u1.id = 1 and abs(toInteger(r1.rating)-toInteger(r2.rating))<=1
MATCH (u2)-[r3:RATING]-(f2:Film)
WITH r3,f2,f1
WHERE f2.id<>f1.id AND toInteger(r3.rating)>4
return count(DISTINCT f2);

*************
*GENRE & AGE*
*************
On veut maintenant mieux prendre en compte la similarité entre u1 et les utilisateurs qui on vu les mêmes films. On vas donca ajouter le genre et l'age. Ici, on prend en compte uniquements les utilisateurs qui on +-2 ans de différence avec u1 et qui ont le même genre.
Bien évidement le genre n'est pas forcément pertinant mais ici il à pour but d'affiner les recommendation en diminuant la quantité.

MATCH (u1:User)-[r1:RATING]-(f1:Film)-[r2:RATING]-(u2:User)
WITH u1,u2,f1
WHERE u1.id = 1 AND u1.gender = u2.gender AND abs(toInteger(u1.age)-toInteger(u2.age))<=2 AND abs(toInteger(r1.rating)-toInteger(r2.rating))<=1
MATCH (u2)-[r3:RATING]-(f2:Film)
WITH r3,f2,f1
WHERE f2.id<>f1.id AND toInteger(r3.rating)>4
return count(DISTINCT f2);


************
*NOTE DE U1*
************
On veux mieux prendre en compte les préférence du u1 donc on vas recommencer uniquement sur la base des films qu'il a bien noté (note minimale de 4/5)

MATCH (u1:User)-[r1:RATING]-(f1:Film)-[r2:RATING]-(u2:User)
WITH u1,u2,f1
WHERE u1.id = 1 AND u1.gender = u2.gender AND abs(toInteger(u1.age)-toInteger(u2.age))<=2 AND abs(toInteger(r1.rating)-toInteger(r2.rating))<=1 AND toInteger(r1.rating)>=4
MATCH (u2)-[r3:RATING]-(f2:Film)
WITH r3,f2,f1
WHERE f2.id<>f1.id AND toInteger(r3.rating)>4
return count(DISTINCT f2);

***************
*GENRE DU FILM*
***************
On veux maintenant prendre en compte les genres du film. On vas donc proposer uniquement des films qui on un genre en commun avec les films aimés de u1

MATCH (u1:User)-[r1:RATING]-(f1:Film)-[r2:RATING]-(u2:User)
WITH u1,u2,f1
WHERE u1.id = 1 AND u1.gender = u2.gender AND abs(toInteger(u1.age)-toInteger(u2.age))<=2 AND abs(toInteger(r1.rating)-toInteger(r2.rating))<=1 AND toInteger(r1.rating)>=4
MATCH (u2)-[r3:RATING]-(f2:Film)
WITH r3,f2,f1
WHERE f2.id<>f1.id AND toInteger(r3.rating)>4
MATCH (f1)-[:APPARTIENT]-(g1:Genre)-[:APPARTIENT]-(f2)
return count(DISTINCT f2);

**********************
*AFFINAGE DES VALEURS*
**********************
On affine les valeurs afin d'avoir moins de suggestions. On passe la note minimale de u1 à 5

MATCH (u1:User)-[r1:RATING]-(f1:Film)-[r2:RATING]-(u2:User)
WITH u1,u2,f1
WHERE u1.id = 1 AND u1.gender = u2.gender AND abs(toInteger(u1.age)-toInteger(u2.age))<=2 AND abs(toInteger(r1.rating)-toInteger(r2.rating))<=1 AND toInteger(r1.rating)>=5
MATCH (u2)-[r3:RATING]-(f2:Film)
WITH r3,f2,f1
WHERE f2.id<>f1.id AND toInteger(r3.rating)>4
MATCH (f1)-[:APPARTIENT]-(g1:Genre)-[:APPARTIENT]-(f2)
return DISTINCT f2.title;


