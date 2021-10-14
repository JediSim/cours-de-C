(****
 ** INFO501 : logique et informatique
 ** TP2
 ** Mario Super, groupe 3
 ****)

(* chargement de la bibliothèque sur les listes *)
Require Import List.
Import ListNotations.

(* définition (récursive) de la fonction de concaténation *)
Fixpoint concat (l1 : list nat) (l2 : list nat) :=
  match l1 with
  | [] => l2
  | x::l1 => x :: (concat l1 l2)
  end.

(* quelques tests *)
Compute (concat [] []).
Compute (concat [1; 2; 3] []).
Compute (concat [] [65; 66; 67]).
Compute (concat [1; 2] [65; 66; 67; 68]).


Theorem concat_vide_gauche : forall l : list nat, concat [] l = l.
Proof.
  intro.
  simpl.
  trivial.
Qed.

Theorem concat_vide_droite : forall l : list nat, concat l [] = l.
Proof. 
  intro.
  induction l.
  simpl.
  trivial.
  simpl.
  rewrite IHl.
  trivial.
 Qed.
  
Theorem concat_associative : forall l1 l2 l3, concat (concat l1 l2) l3 = concat l1 (concat l2 l3).
Proof.
  intros.
  induction l1.
  induction l2.
  simpl.
  trivial.
  simpl.
  trivial.
  simpl.
  rewrite IHl1.
  trivial.
Qed.
  
(* définition naïve (quadratique) de la fonction qui renvoie une liste "à l'envers" *)
Fixpoint renverse (l : list nat) :=
  match l with
  | [] => []
  | x::l => concat (renverse l) [x]
  end.

Compute (renverse [1; 2; 3; 4]).

(* meilleure définition (linéaire) en utilisant un accumulateur *) 
Fixpoint renverse_concat (l1 : list nat) (l2 : list nat) :=
  match l1 with
  | [] => l2
  | x::l1 => renverse_concat l1 (x::l2)
  end.

Compute (renverse_concat [1; 2; 3; 4; 5] []).
  Compute (renverse_concat [] [65; 66; 67; 68]).
Compute (renverse_concat [1; 2; 3] [65; 66]).


Theorem thm_renverse_gen : forall l1 l2, renverse_concat l1 l2 = concat (renverse l1) l2.
Proof.
  intro.
  induction l1.
  simpl.
  trivial.
  simpl.
  intro.
  rewrite IHl1.
  rewrite concat_associative.
  simpl.
  trivial.
Qed.


Theorem thm_renverse : forall l, renverse l = renverse_concat l [].
Proof.
  intro.
  rewrite thm_renverse_gen.
  rewrite concat_vide_droite.
  trivial.
Qed.
