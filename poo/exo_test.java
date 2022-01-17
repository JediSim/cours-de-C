class Jeu {
    private Grille grille;

    public Jeu(){
        grille = new Grille();

    }

    public void afficheJeu(){
        this.grille.afficheGrille();
    }
}

class Grille {
    private int HAUTEUR;
    private int LARGEUR;
    private Tab plateau;

    public Grille(int hauteur, int largeur){
        this.HAUTEUR = hauteur;
        this.LARGEUR = largeur;
        this.plateau = [[]*hauteur]*largeur;
    }

    public afficheCellule(int i, int j){
        if estProtege(i,j){
            if estGuerrier(i,j){
                plateau[i][j].affiche_guerrier_cellule_protégée();
            }else{
                plateau[i][j].affiche_maison_cellule_protégée();
            }
        }else{
            if estGuerrier(i,j){
                plateau[i][j].affiche_guerrier_cellule_non_protégée();
            }else{
                plateau[i][j].affiche_maison_cellule_non_protégée();

            }
        }
    }

    public void afficheGrille(){
        for( int i = 0; i < grille.getHauteur){
            for( int j = 0; j < grille.getLargeur){
                grille.afficheCellule(i, j);
            }
        }
    }
}
