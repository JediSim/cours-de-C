REY-PICHENOT

Q1 :
a. 1 subgoal (ID 24)
  
    f, g : nat -> nat
    S : forall y : nat, exists x : nat, comp f g x = y
    y, x : nat
    H : comp f g x = y
    ============================
    exists x0 : nat, f x0 = y

b. Le programme plante (Error : Attempt to save an incomplete proof).
c. En ajoutant "assumption." avant la commande "Qed" la preuve se fini.

Q2 - Q8 :
Voir fichier PICHENOT-REY-deduction_naturelle.v

Q10 :
La preuve ne fonctionne pas car on ne peut pas prouver un raisonnement recursif sans preuve recusrsive.

Q13 :
On ne peut pas effectuer une preuve par recursivité sur deux fonction en même temps.