(* définition de fonction __surjective__ *)
Definition surjective (f : nat -> nat) := forall y:nat, exists x:nat, f x = y.

(* définition de composition de fonctions *)
Definition comp (f : nat -> nat) (g : nat -> nat) := fun n => f (g n).

Theorem prop_surjection : forall f g,
    surjective (comp f g) -> surjective f.
Proof.
  intros f g.           (* règle ∀c, deux fois *)
  intro S.              (* règle ⇒c *)
  unfold surjective.    (* on remplace "surjective" par sa définition *)
  intro y.              (* règle ∀c *)
  unfold surjective in S.

  (* on ajoute une formule dans les hypothèses *)
  assert (exists x, (comp f g) x = y).

  (* il y a maintenant 2 buts à prouver *)
  - apply S.            (* conséquence directe de S *)

  - destruct H.         (* règle d'utilisation du ∃ en hypothèse *)
    (* QUEL EST LE BUT COURANT ICI ? *)
    exists (g x).       (* règle ∃c *)
    unfold comp in H.
    (* ... *)
    assumption.
Qed.
