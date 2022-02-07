# TD

## question 1 :

On va forcément retomber sur l'etat passé en parametre. Donc le calcul se refait de la même manière et on a le même résultat.

## Question 2 :

$a = 6, c = 1, m = 24, x_0 = 4$
$6 \times 4 + 6 mod(24) = 1$
$x_0 = 4 \\
x_1 = 1\\
x_2 = 7\\
x_3 = 19\\
x_4 = 19$

## Question 3 :

La vieille libc utilisait $m = 2^{31}$ car le calcul est plus simple. Avec ca on recupère juste les 31 premiers bite. C'est juste une opération bit à bit qui ne prend pas en compte les nombres signé.



## Question 4 :

Avec $m=2$ on aura une périodicité pas trés interessante. Soit on alterne 01 avec le  en premier ou en deuxième, soit que des 0, soit que des 1.

## Question 5 :

Avec les vieilles implémentations le bit de point faible avait une periodicité de $2^i$ i étant ca place en partant du point faible.

## exo 2 : registre à décalage

## Question 1 et 2 :

- avec 1111 : 

    11110001001101011110 periode : 15
- avec 0000 :

    00000 periode : 1

## Question 3 :

```c
// On peut factoriser le calcul de b avec & 1
b = (e & 1)^((e >> 3) & 1)^((e >> 5) & 1)^((e >> 29) & 1)
uint32_t e = (e << 1) | b;
```
## Question 4 :
TODO in home

# Partie 2 : quelques programmes aléatoires

## Question 1 :

Ce processus n'est pad équitable car on a plus de chance d'obtenir 1.

0 : 5
1 : 1,6
2 : 2
3 : 3
4 : 4

Si on tire 1 ou 6 on obtient 1.

Non cela sera équiprobable.

## Question 2 : 

$2^{31}$ n'est pas un multiple de 5 donc on ne peut pas le répartir en 5 groupes de taille égal. Donc théoriquement le resultat n'est pas équiprobable.

En pratique on ne vois pas de grande différence. Les chances entre 2 nombres n'est pas assez grande pour influer grandement.

## Question 3 : 
TODO in home

## Question 4 : 

$00 : 81 \% \\
01 : 9 \% \\
10 : 9 \% \\
11 : 1 \%$

On relance le tirage si les deux bits sont égaux. Sinon on renvoie le premier bit.

## exo 1 : sélection

## Question 1 : 

## Question 2 : 

Si le premier élément est affiché :

$A(n-1,k-1)$

Sinon :

$A(n-1,k)$

```c
void affiche(T, n, k)
{
    for( int i = 0; i < n; i++ )
    {
        if(rand() % (n-i) < k)
        {
            printf("%d\n", T[i]);
            k-=1;
        }
    }
}
```

## Question 3 : (et on parle pas du flo roux, si vous voulez son num envoyez un mail)

flot de taille n :
apres avoir tracé l'arbre des proba
- $s = 1^{er} élément\ 1/2 \times 2/3 = 1/3$
- $s = 2^{ème} élément 1/2 \times 2/3 = 1/3$
- $s = 3^{ème} élément 1/2 \times 1/3 + 1/2 \times 1/3= 1/3$

flot de taille 17 :
proba de tirer le 10ème élément :

$1/10 \times 10/11 \times 11/12 \times ...\times 16/17$

## Question 4 :


```python
S = []
for _ in range(k):
    S.append(flot.next())
nb_element = k
for x in flot:
    nb_element += 1
    if (randint(0,nb_element-1) < k):
        S[randint(0,k)] = x 
        # On peut ne pas tirer de nouveau en stockant le premier 
        # tirage qi sera forcément entre 0 et k si il passe le if
```

# Exo 2 :

## Question 3 :

possibilitée 1 :
on permute i = 0 avec n-1 puis on ne permute jamais i > 0 avec 0.

possibilitée 2 : 
on ne permute jamais i < n-1 avec 0 puis on permute i = n-1 avec 0.