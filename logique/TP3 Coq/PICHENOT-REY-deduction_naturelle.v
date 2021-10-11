(*PICHENOT REY*)

(****
 ** INFO501 : logique et informatique
 ** TP2
 ** Mario Super, groupe 3
 ****)


(* pour avoir le raisonnement par l'absurde
   (à n'utiliser que lorsque c'est vraiment nécessaire) *)
Require Import Classical_Prop.


Section question2.
  Variable A B : Prop.

  Theorem utilisation_et_1 : A /\ B -> A.
  Proof.
    intro H.
    destruct H.
    assumption.
  Qed.

  Theorem utilisation_et_2 : A /\ B -> B.
  Proof.
    intro H.
    destruct H.
    assumption.
  Qed.

End question2.

Section question3.
  Variable A B C : Prop.

  Theorem et_com : A /\ B -> B /\ A.
  Proof.
    intro H.
    destruct H.
    split.
    assumption.
    assumption.
  Qed.


  Theorem ou_com : A \/ B <-> B \/ A.
  Proof.
    split.
    intro H.
    destruct H.
    right.
    assumption.
    left.
    assumption.
    intro H.
    destruct H.
    right.
    assumption.
    left.
    assumption.
Qed.

  Theorem contraposition : (A -> B) -> (~B -> ~A).
  Proof.
    intros H.
    intro.
    intro.
    apply NNPP; intro.
    apply H0.
    apply H.
    assumption. 
  Qed.

  Theorem distribution : (A \/ (B /\ C) -> (A \/ B) /\ (A \/ C)).
  Proof.
   intros.
   split.
   destruct H.
   left.
   assumption.
   destruct H.
   right.
   assumption.
   destruct H.
   left.
   assumption.
   destruct H.
   right.
   assumption.
  Qed.
   
End question3.


Section question4.
  (* première loi de de Morgan :  ¬(A ∨ B) ⇔ ¬A ∧ ¬B *)
  (* ... *)
  Variable A B : Prop.
  
  Theorem Morgan_1 : ~(A \/ B) <-> ~A /\ ~B.
  Proof.
    split.
    intro.
    split.
    intro.
    apply H.
    left.
    assumption.

    intro.
    apply H.
    right.
    assumption.

    intro.
    destruct H.
    intro.
    destruct H1.
    apply H.
    assumption.
    apply H0.
    assumption.
  Qed.
  
End question4.

Section question5.
  (* BONUS *)
  (* deuxième loi de de Morgan :  A ∨ B ⇔ ¬(¬A ∧ ¬B) *)
  (* ... *)

End question5.


Section question6.
  Variable X : Set.
  Variable P Q : X -> Prop.

  Theorem pourtout_et : (forall x:X, (P x /\ Q x)) <-> (forall x : X, P x) /\ (forall x : X, Q x).
  Proof.
    split.
    intro.
    split.
    intro.
    apply H.
    intro.
    apply H.

    intro.
    split.
    apply H.
    apply H.
   Qed.
    
  Theorem existe_ou : (exists x:X, (P x \/ Q x)) <-> (exists x:X, P x) \/ (exists x:X, Q x).
  Proof.
    split.
    intro.
    destruct H.
    destruct H.
    left.
    exists (x).
    assumption.
    right.
    exists (x).
    assumption.

    intro.
    destruct H.
    destruct H.
    exists (x).
    left.
    assumption.
    destruct H.
    exists (x).
    right.
    assumption.
  Qed.  
 
End question6.


Section question7.
  (* troisième loi de de Morgan :  ¬∃ x:X, P(x) ⇔ ∀ x:X, ¬ P(x) *)
  (* ... *)
  Variable X : Set.
  Variable P : X -> Prop.
  
  Theorem deMorgan_la_plus_dur: ~(exists x:X, (P x)) <-> forall x:X, ~(P x).
  Proof.
    split.
    intro.
    intro.
    intro.
    destruct H.
    exists (x).
    assumption.

    intro.
    intro.
    destruct H0.
    apply (H x).
    assumption.
  Qed.
  

End question7.


Section question8.
  (* BONUS *)
  (* quatrième loi de de Morgan :  ∃ x:X, P(x) ⇔ ¬(∀ x:X, ¬P(x)) *)
  (* ... *)

End question8.
