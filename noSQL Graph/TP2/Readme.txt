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

