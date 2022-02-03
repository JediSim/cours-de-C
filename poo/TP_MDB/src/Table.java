import java.util.ArrayList;

public class Table {
    private ArrayList<Bloc> liste_sommets = new ArrayList<Bloc>();

    public void setSommet(Bloc cubeAPoser, Bloc cubeOuPoser) {
        int indice = liste_sommets.indexOf(cubeOuPoser);
        cubeOuPoser.setDessus(cubeAPoser);
        cubeAPoser.setDessous(cubeOuPoser);
        liste_sommets.set(indice, cubeAPoser);
    }

    private void retireSommet(Bloc bloc, int indice) {
        Bloc dessous = bloc.getDessous();
        if (dessous != null) {
            dessous.setDessus(null);
            bloc.setDessous(null);
            liste_sommets.set(indice, dessous);
        } else {
            liste_sommets.remove(indice);
        }

    }

    public Bloc getCubeBonneTailleCouleur(TailleCube taille, String couleur) {
        Bloc tmp = chercher(couleur, taille);
        if (tmp != null) {
            retireSommet(tmp, liste_sommets.indexOf(tmp));
        }
        return tmp;

    }

    public boolean recoitCubeDeBonneTaille(TailleCube taille, Bloc cubeAPoser) {

        return TailleCube.estPlusGrand(taille, cubeAPoser.getTaille());
    }

    public boolean empilerCube(TailleCube taille, String couleur, Bloc cubeAPoser) {
        if (recoitCubeDeBonneTaille(taille, cubeAPoser)) {
            Bloc tmp = chercher(couleur, taille);
            if (tmp != null) {
                setSommet(cubeAPoser, tmp);
                return true;
            } else {
                System.out.println("Il n'y a pas de bloc pour le poser");
                return false;
            }
        } else {
            System.out.println("Le cube ou poser n'est pas assez grand");
            return false;
        }

    }

    private Bloc chercher(String couleur, TailleCube taille) {
        for (Bloc bloc : liste_sommets) {
            if (bloc.estTu(taille, couleur)) {
                return bloc;
            }
        }
        return null;
    }

    public ArrayList<Bloc> getListe_sommets() {
        // Automatically generated method. Please delete this comment before entering
        // specific code.
        return this.liste_sommets;
    }

    public void setListe_sommets(ArrayList<Bloc> value) {
        // Automatically generated method. Please delete this comment before entering
        // specific code.
        this.liste_sommets = value;
    }

    public void afficherTable() {
        System.out.println("Sur la table il y a : ");
        for (Bloc bloc : liste_sommets) {
            System.out.println(bloc);
        }

    }

}
