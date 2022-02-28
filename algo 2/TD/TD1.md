# TD1

## Exo 1 :

1. est vrai car $\Theta(n^2) + n\Theta(\log n) \\
= n(\Theta(n) + \Theta(\log n)) \\
= n(\Theta(n)) = \Theta(n^2) = \Omicron(n^2)$

2. $2^n = \Omicron(n^2) \\
2^n = \Omega(n^10) \\
et\ \Theta(n^{10}) \neq \Omicron(n^2)$
Donc faux

3. $n + 3n\log n = \Omicron(n \log n)\\
= \Theta(n) + \Theta(n)\Theta(\log n) \\
= \Theta(n) (\Theta(1) + \Theta(\log n))\\
= \Theta(n)(1 + \log n)\\
= \Theta(n \log n)$
Donc vrai

4. 

## Exo 2 :

$\begin{bmatrix}
\Omicron & \Omicron & \Omicron & \Omicron \\
\Omicron & \Theta & \Omega & \Omega \\
\Omicron & \Omicron & \Theta & \Omicron \\
\Omega & \Omega & \Omega & \Omega \\
\end{bmatrix}$

## Exo 3 :

## Exo 5 :

en fct des parametres : $\Theta(j - (i))$
en pire cas : $\Theta(n)$

## Exo 7 :

complexité : $\Theta(n^2)$