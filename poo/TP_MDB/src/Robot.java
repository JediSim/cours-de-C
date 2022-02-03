
public class Robot {
	private String nom;

	public Robot(String nom, Table table) {
		setNom(nom);
		setTable(table);
		setBlocTenu(null);
	}

	private String getNom() {
		// Automatically generated method. Please do not modify this code.
		return this.nom;
	}

	private void setNom(String value) {
		// Automatically generated method. Please do not modify this code.
		this.nom = value;
	}

	private Bloc blocTenu;

	private Bloc getBlocTenu() {
		// Automatically generated method. Please do not modify this code.
		return this.blocTenu;
	}

	private void setBlocTenu(Bloc value) {
		// Automatically generated method. Please do not modify this code.
		this.blocTenu = value;
	}

	private Table table;

	private Table getTable() {
		// Automatically generated method. Please do not modify this code.
		return this.table;
	}

	private void setTable(Table value) {
		// Automatically generated method. Please do not modify this code.
		this.table = value;
	}

	public void creerCube(TailleCube taille, String couleur) {
		if (mainVide()) {
			setBlocTenu(new Bloc(taille, couleur));

		} else {
			System.out.println("il y a déjà un bloc dans la main");
		}
	}

	public boolean mainVide() {
		if (getBlocTenu() == null) {
			return true;
		} else {
			return false;
		}
	}

	public void prendreBloc(TailleCube taille, String couleur) {
		// erreur null pointeur exception apres detruire tout vide
		Bloc tmp;
		if (mainVide()) {
			tmp = getTable().getCubeBonneTailleCouleur(taille, couleur);
			if (tmp != null) {
				setBlocTenu(tmp);
			} else {
				System.out.println("Il n'y a pas de bloc de cette taille et cette couleur");
			}

		} else {
			System.out.println("Le robot tient d�j� un bloc");
		}
	}

	public void detruireBloc(TailleCube taille, String couleur) {

		if (!mainVide()) {
			if (getBlocTenu().estTu(taille, couleur)) {
				libererMain();
				System.out.println("Cube d�truit");
			} else {
				System.out.println("Le Robot ne tient pas le bon cube");
			}
		} else {
			prendreBloc(taille, couleur);
			libererMain();
			System.out.println("Cube d�truit");
		}
	}

	public void poserCubeSurCube(TailleCube taille, String couleur) {
		if (!mainVide()) {
			if (getTable().empilerCube(taille, couleur, getBlocTenu())) {
				libererMain();
			}
		} else {
			System.out.println("la main est vide");
		}
	}

	public void poserCubeSurTable() {
		if (!mainVide()) {
			getTable().getListe_sommets().add(getBlocTenu());
			libererMain();
			System.out.println("Le cube a été posé sur la table");
		} else {
			System.out.println("La main du robot est vide");
		}
	}

	public void libererMain() {
		setBlocTenu(null);
	}

	public void afficherRobot() {
		if (mainVide()) {
			System.out.println("Le robot " + getNom() + " � la main vide");
		} else {
			System.out.println("Le robot " + getNom() + " tient le bloc " + getBlocTenu());
		}
	}

}
