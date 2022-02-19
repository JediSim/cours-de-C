# Maths pour l'info

## générateurs aléatoires

## Cryptographie

livre : l'histoire des codes secrets S. Singh

### 1) Vagebqhpgvda

La cryto graphie sert à limiter la confiance necessaire aux communications.


# 7) crypto clé publique / clé privée

RSA (Rivest Shamir Adleman c'est pas l'aide financiaire)

système de chiffrement à deux clés :
- une cle publique, connue de tous, qui sert à chiffrer.
- une cle privée, serète, pour déchiffrer.

Avantage principal : 
- plus besoin d'echanger une clé de manière sécurisée.
- pour communiquer, N personnes n'ont besoin que de N paires de clé.

<span style="color:green">Rq :</span> Alice utilise la clé publique de Bob pour lui envoyer des messages et Bob utilise la clé publique de Alice pour lui répondre.

<span style="color:red">ex : RSA</span>
Alice choisit 2 nb premiers (grands) p et q et un nb d premier avec $(p-1)(q-1)$
Alice calcul e, l'inverse de d modulo $(p-1)(q-1)$

clé publique : $n = p \times q\ et\ e$
clé privée : $n = p \times q\ et\ d$

chiffrer un message pour Alice et

message $\rightarrow$ m nb plus petit que n
        $\rightarrow m^e(mod\ m) = M$

pour dechiffrer : $M \rightarrow M^d (mod\ m)$

### Théorème :

$M^d(mod\ m) = m$

<span style="color:blue">Fait experimental</span>

On ne sait pas calculer d à partir de n et e (on ne sait pas retrouver p et q à partir de $n = p \times q$)

<span style="color:green">Rq :</span> 
- on utilise jamais RSA tout seul.
- RSA (et les autres systèmes à clé publique) est très lents.

$\rightarrow$ On utilise la crypto à clé publique pour chiffrer une clé AES.


