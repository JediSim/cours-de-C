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

Q2 :
Voir fichier mario-deduction_naturelle.v