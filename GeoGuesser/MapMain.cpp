

int main() {
	/* Wir müssen ein Objekt der Klasse Map erstellen. Über dieses Objekt können wir dann das Dateiobjekt mit der Methode readPointsFromFile aufrufen. */
	/* Zu aller erst müssen wir ein Objekt von der Klasse TerminalManager erzeugen, um zum Beispiel an die Bildschirmdimensionen zu kommen.*/
	TerminalManager tm;
 	Map map;
	map.readPointsFromFile();
	BrailleTerminalManager btm;
	/* Jetzt haben wir einen Vektor, in dem alle Punkte gespeichert sind*/
	/* Jetzt kommt unsere BrailleTerminalManager Klasse ins Spiel, welche zum einen den Index des Braille Zeichen und die Position des Braille Pixel (zwischen 0 und 7) berechnet.
	Es wird ein neuer Vektor berechnet, diesmal aber speichert dieser die Braille Zeichen in Form eines Array der größe 8.*/
	
	/* Aufruf des allgemeinen Konstruktors. */
	
	

}
