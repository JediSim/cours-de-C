# RC4 attaque FMS

RC4 est un generateur aleatoire cryptographique (qu'il ne faut plus utiliser).
Il a été utilisé comme système de chiffrement par flot en faisant un XOR.

### état :
- i : octet $0 \leq i < 255$
- j : octet $(.....j......)$
- P[256] une permutation des 256 octets.

### génération d'un octet :
$i = (i+1) \mod(256)$
$j = (j + P[i]) \mod (256)$
$P[i] \leftrightarrow P[j]$
return $P[(P[i] + P[j]) \mod (256)]$

### initialisation à partir d'une clé K de t octets $t < 256$ :

```c
// Question 1 du TP3
P = {0;1;2;.....;256}
j = 0;
for (int i = 0; i < 256; i++)
{
    j = (j + P[i] + K[i%t])%256;
    P[i] <-> P[j]; // On inverse les deux valeurs
}
i = 0
j = 0
```

# WEP
clé RC4 est constituée :
- de la clé WEP secrète (5 ou 8 octets).
- précédée d'un vecteur d'initialisation de 3 octets, envoyés en clair.

Les octets RC4 sont ajoutés aux octets du paquet (XOR).

### Attaque :
- On peut retrouver le premier octet généré par RC4.
- On connait le début de la clé RC4 (vecteur d'initialisation).
- On peut faire le début de l'initialisation de RC4.
- On peut faire une prediction sur l'octet suivant de la clé.
- On boucle sur les étapes 1 à 3.

Supposons qu'on connaisse $k$ octets de la clé (au début $k = 3$).
On fait les $k$ premières etapes de l'initialisation.
 `for(i = 0; i < k; i++)`
On note $j_0$ pour la denière valeur de j.
On test si :
- P[1] < k
- P[1] + P[P[1]])% 256 = k
Si non, on recommence avec un nouveau paquet.
Si oui, on dit que le vecteur d'initialisation est faible.
On peut faire predire que l'octet $k$ de la clé est $P^{-1}[0] - j_0 - P[k]$

<span style="color:red">Pb : </span>cette prediction est fausse dans 95% des cas.
juste dans 5% des cas. Ceset mieux qu'une prediction aleatoire (1/256).

On fait 1000 predictions 
La prediction la plus courrante est probablement la bonne.