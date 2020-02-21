#include <iostream>
#include "CAbase.h"
using namespace std;

// Funktion Zeichnen des aktuellen Status von CA.
void Draw(CAbase ca)
{
	for (unsigned int j = 0; j < ca.GetNx() + 2; j++) {
		for (unsigned int i = 0; i < ca.GetNy() + 2; i++) {
			if (ca.IsAlive(i, j) == 0) cout << "  ";
			if (ca.IsAlive(i, j) == 1) cout << "* ";
			if (ca.IsAlive(i, j) == -1) cout << ". ";
		}
		cout << "\n";
	}
}

int main() {

	CAbase newCA(20, 20);			//  Erstellen CA-Objekt mit Konstruktor
	newCA.ResetWorldSize(30, 30);		// Ändern die Größen des Universums
	cout << " Nh: " << newCA.GetNy() << ";   Nw: " << newCA.GetNx() << "\n";
	// Varianten von den Zellen
	newCA.SetAlive(2, 3, 1);
	newCA.SetAlive(2, 4, 1);
	newCA.SetAlive(2, 5, 1);
	newCA.SetAlive(3, 4, 1);
	newCA.SetAlive(3, 5, 1);
	newCA.SetAlive(4, 4, 1);
	newCA.SetAlive(5, 4, 1);
	newCA.SetAlive(6, 4, 1);
	newCA.SetAlive(7, 4, 1);
	newCA.SetAlive(7, 7, 1);
	newCA.SetAlive(7, 8, 1);
	newCA.SetAlive(8, 8, 1);
	newCA.SetAlive(9, 8, 1);
	newCA.SetAlive(10, 8, 1);
	newCA.SetAlive(6, 8, 1);
	newCA.SetAlive(7, 6, 1);
	newCA.SetAlive(7, 5, 1);
	newCA.SetAlive(5, 5, 1);

	newCA.SetAlive(20, 5, 1);
	newCA.SetAlive(20, 6, 1);
	newCA.SetAlive(20, 7, 1);
	newCA.SetAlive(19, 7, 1);
	newCA.SetAlive(18, 6, 1);
	// ---
	int input = 1;
	do {
		Draw(newCA);
		bool do_menu(true);
		do {
			// Initialisierung des Konsolenmenüs
			cout << " 0. Beenden\n 1. Evolution\n 2. Zelle als lebendig markieren\n 3. Neu drucken\n 4. Die Groesse aendern\n";
			cin >> input;
			switch (input) {			// Überprüfen Input
			case 0:
				do_menu = false;		// 0: Programm beenden
				break;
			case 1:
				newCA.WorldEvolutionLife();	// 1: Evolution starten
				do_menu = false;		// Verlassen Menü-Schleife und erstellen neues Universum
				break;
			case 2:
				int x, y;			// 2. Die Koordinaten eingeben
				cout << " X= "; cin >> x;
				cout << " Y= "; cin >> y;
				newCA.SetAlive(x, y, 1);	// Zelle als lebendig markieren
				break;			// zum Menü zurückkehren
			case 3:
				do_menu = false;		// 3. Verlassen Menü-Schleife und erstellen neues Universum
				break;
			case 4:
				int nx, ny;			// 4. Die Größen des neuen Universums eingeben
				cout << " Nx= "; cin >> nx;
				cout << " Ny= "; cin >> ny;
				newCA.ResetWorldSize(nx, ny);	// Das Universum mit den neuen Größen erstellen
				do_menu = false;		// Verlassen Menü-Schleife und erstellen neues Universum
				break;
			default:
				cout << "Falsche Option. Versuchen Sie nochmal.\n";
			}
		} while (do_menu);
	} while (input != 0);

	return 0;
}