
import java.io.*;

public enum TailleCube {
	grand, moyen, petit;

	public static TailleCube getTaille(String taille) {
		for (TailleCube t : TailleCube.values())
			if (t.name().equalsIgnoreCase(taille))
				return t;
		return TailleCube.grand;
	}

	public static boolean estPlusGrand(TailleCube taille1, TailleCube taille2) {
		return taille1.ordinal() <= taille2.ordinal();
	}
}
