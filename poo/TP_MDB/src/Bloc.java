
public class Bloc {
    private TailleCube taille;

    public Bloc(TailleCube taille, String couleur) {
        this.couleur = couleur;
        this.taille = taille;
    }

    public TailleCube getTaille() {
        // Automatically generated method. Please do not modify this code.
        return this.taille;
    }

    private void setTaille(TailleCube value) {
        // Automatically generated method. Please do not modify this code.
        this.taille = value;
    }

    private String couleur;

    private String getCouleur() {
        // Automatically generated method. Please do not modify this code.
        return this.couleur;
    }

    private void setCouleur(String value) {
        // Automatically generated method. Please do not modify this code.
        this.couleur = value;
    }

    private Bloc dessus;

    public Bloc getDessus() {
        // Automatically generated method. Please do not modify this code.
        return this.dessus;
    }

    public void setDessus(Bloc value) {
        // Automatically generated method. Please do not modify this code.
        this.dessus = value;
    }

    private Bloc dessous;

    public Bloc getDessous() {
        // Automatically generated method. Please do not modify this code.
        return this.dessous;
    }

    public void setDessous(Bloc value) {
        // Automatically generated method. Please do not modify this code.
        this.dessous = value;
    }

    public boolean estTu(TailleCube taille, String couleur) {
        return ((taille == getTaille()) & (couleur.equals(getCouleur())));
    }

    public String toString() {
        return "taille : " + getTaille() + " couleur : " + getCouleur();
    }

}
