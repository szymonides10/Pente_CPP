#include "everything.h"

class gracz {
	int kolor;
	int x;
	int y;
	int zbite;
	int ilosc_ruchow;

public:
	gracz() {
		kolor = 1;
		x = 1;
		y = 1;
		zbite = 0;
		ilosc_ruchow = 0;
	}
	//set and get
	void setKolor(int n) {
		kolor = n;
	}
	int getKolor() {
		return kolor;
	}
	virtual void setX(int a) {
		x = a;
	}
	int getX() {
		return x;
	}
	virtual void setY(int a) {
		y = a;
	}
	int getY() {
		return y;
	}
	void addZbite(int n) {
		zbite += n;
	}
	int getZbite() {
		return zbite;
	}
	
	virtual void ruch() {
		printf("Gdzie chcesz postawić pionek?\n");

		printf("X=");
		x = scan_int(1, 19) - 1;
		setX(x);

		printf("Y=");
		y = scan_int(1, 19) - 1;
		setY(y);

		++ilosc_ruchow;
	}
};



class komputer : public gracz {
public:
	komputer() : gracz() {}

	int losuj_ruch() {
		int x = rand() % 19;
		return x;
	}

	void ruch() {
		setX(losuj_ruch());
		setY(losuj_ruch());
	}
};



class pente {
private:
	int plansza[19][19] = { 0 };

public:
	//postawienie pionka
	int jesli_mozna_ustaw_pionek(int x, int y, int kolor) {
		if (plansza[y][x] != 0) return 0;
		else {
			plansza[y][x] = kolor;
			return 1;
		}
	}
	//druk planszy
	void print(gracz a, gracz b) {
		int i, j;
		printf("\n *");
		for (i = 0; i < 19; ++i)	printf(" %02d ", i + 1);
		for (i = 0; i < 19; ++i) {
			printf("\n%02d  ", i + 1);
			for (j = 0; j < 19; ++j) {
				printf("%d   ", plansza[i][j]);
			}
		}
		printf("\n\n");
		printf("Zbite pionki:\nGracz 1: %d\tGracz 2: %d\n\n", a.getZbite(), b.getZbite());
	}
	//czy pionki sa bite
	int ile_zbitych_po_ruchu(int x, int y, int kolor) {
		int i, j, licznik = 0;
		int ile_aby_zbic = 2;
		int check = 0;

		//ustawienie przeciwnego koloru
		int antykolor;
		kolor == 1 ? antykolor = 2 : antykolor = 1;

		//kierunki bicia:
		//dol	y+, x
		if (y < 18 - ile_aby_zbic && plansza[y][x] == kolor && plansza[y + (ile_aby_zbic + 1)][x] == kolor) {
			for (i = 1; i <= ile_aby_zbic; ++i) {
				if (plansza[y + i][x] != antykolor)	break;
				if (i == ile_aby_zbic) {
					licznik += ile_aby_zbic;
					for (j = 1; j <= ile_aby_zbic; ++j) {
						plansza[y + j][x] = 0;
					}
				}
			}
		}
		//gora	y-, x
		if (y > 0 + ile_aby_zbic && plansza[y][x] == kolor && plansza[y - (ile_aby_zbic + 1)][x] == kolor) {
			for (i = 1; i <= ile_aby_zbic; ++i) {
				if (plansza[y - i][x] != antykolor)	break;
				if (i == ile_aby_zbic) {
					licznik += ile_aby_zbic;
					for (j = 1; j <= ile_aby_zbic; ++j) {
						plansza[y - j][x] = 0;
					}
				}
			}
		}
		//lewo	y, x-
		if (x > 0 + ile_aby_zbic && plansza[y][x] == kolor && plansza[y][x - (ile_aby_zbic + 1)] == kolor) {
			for (i = 1; i <= ile_aby_zbic; ++i) {
				if (plansza[y][x-i] != antykolor)	break;
				if (i == ile_aby_zbic) {
					licznik += ile_aby_zbic;
					for (j = 1; j <= ile_aby_zbic; ++j) {
						plansza[y][x-j] = 0;
					}
				}
			}
		}
		//prawo	y, x+
		if (x < 18 - ile_aby_zbic && plansza[y][x] == kolor && plansza[y][x + (ile_aby_zbic + 1)] == kolor) {
			for (i = 1; i <= ile_aby_zbic; ++i) {
				if (plansza[y][x + i] != antykolor)	break;
				if (i == ile_aby_zbic) {
					licznik += ile_aby_zbic;
					for (j = 1; j <= ile_aby_zbic; ++j) {
						plansza[y][x + j] = 0;
					}
				}
			}
		}
		//gora prawo	y-, x+
		if (x < 18 - ile_aby_zbic && y > 0 + ile_aby_zbic && plansza[y][x] == kolor && plansza[y - (ile_aby_zbic + 1)][x + (ile_aby_zbic + 1)] == kolor) {
			for (i = 1; i <= ile_aby_zbic; ++i) {
				if (plansza[y - i][x + i] != antykolor)	break;
				if (i == ile_aby_zbic) {
					licznik += ile_aby_zbic;
					for (j = 1; j <= ile_aby_zbic; ++j) {
						plansza[y - j][x + j] = 0;
					}
				}
			}
		}

		//gora lewo		y-, x-
		if (x > 0 + ile_aby_zbic && y > 0 + ile_aby_zbic && plansza[y][x] == kolor && plansza[y - (ile_aby_zbic + 1)][x - (ile_aby_zbic + 1)] == kolor) {
			for (i = 1; i <= ile_aby_zbic; ++i) {
				if (plansza[y - i][x - i] != antykolor)	break;
				if (i == ile_aby_zbic) {
					licznik += ile_aby_zbic;
					for (j = 1; j <= ile_aby_zbic; ++j) {
						plansza[y - j][x - j] = 0;
					}
				}
			}
		}

		//dol prawo		y+, x+
		if (x < 18 - ile_aby_zbic && y < 18 - ile_aby_zbic && plansza[y][x] == kolor && plansza[y + (ile_aby_zbic + 1)][x + (ile_aby_zbic + 1)] == kolor) {
			for (i = 1; i <= ile_aby_zbic; ++i) {
				if (plansza[y + i][x + i] != antykolor)	break;
				if (i == ile_aby_zbic) {
					licznik += ile_aby_zbic;
					for (j = 1; j <= ile_aby_zbic; ++j) {
						plansza[y + j][x + j] = 0;
					}
				}
			}
		}

		//dol lewo		y+, x-
		if (x > 0 + ile_aby_zbic && y < 18 - ile_aby_zbic && plansza[y][x] == kolor && plansza[y + (ile_aby_zbic + 1)][x - (ile_aby_zbic + 1)] == kolor) {
			for (i = 1; i <= ile_aby_zbic; ++i) {
				if (plansza[y + i][x - i] != antykolor)	break;
				if (i == ile_aby_zbic) {
					licznik += ile_aby_zbic;
					for (j = 1; j <= ile_aby_zbic; ++j) {
						plansza[y + j][x - j] = 0;
					}
				}
			}
		}

		return licznik;
	}

	//warunki wygranej
	int sprawdzenie_wygranej_przez_ulozenie_po_ruchu(int x, int y, int kolor) {
		int i, check = 0, licznik;

		//gora
		licznik = 0;
		if (y>=4) {
			for (i = 0; i < 5; ++i) {
				if (plansza[y - i][x] == kolor) {
					++licznik;
				}
			}
		}
		if (licznik == 5)	return 1;

		//dol
		licznik = 0;
		if (y <= 14) {
			for (i = 0; i < 5; ++i) {
				if (plansza[y + i][x] == kolor) {
					++licznik;
				}
			}
		}
		if (licznik == 5)	return 1;

		//lewo
		licznik = 0;
		if (x >= 4) {
			for (i = 0; i < 5; ++i) {
				if (plansza[y][x-i] == kolor) {
					++licznik;
				}
			}
		}
		if (licznik == 5)	return 1;

		//prawo
		licznik = 0;
		if (x <= 14) {
			for (i = 0; i < 5; ++i) {
				if (plansza[y][x + i] == kolor) {
					++licznik;
				}
			}
		}
		if (licznik == 5)	return 1;
		
		return 0;
	}
};

int main() {
	info();

	//menu
	printf("1. Zagraj w nową grę.\n");
	printf("2. Wyświetl historię gier.\n");
	printf("3. Wyjdź z gry.\n");
	int choice = scan_int(1, 3);
	srand(time(NULL));

	pente gra;

	//przygotowanie do gry
	if (choice == 1) {
		//wybor gracza lub komputera
		printf("1. Gracz vs Komputer.\n2. Gracz vs Gracz.\n");
		choice = scan_int(1, 2);

		//gracz vs komputer
		if (choice == 1) {		
			gracz gospodarz;
			komputer ai;

			//wybor koloru
			printf("Jaki kolor wybiera gracz?\n");
			printf("1. Biały.\n2. Czarny.\n3. Losowy.\n");
			choice = scan_int(1, 3);

			//bialy
			if (choice == 1) {
				gospodarz.setKolor(1);
				ai.setKolor(2);
			}
			//czarny
			else if (choice == 2) {
				gospodarz.setKolor(2);
				ai.setKolor(1);
			}
			//losowy
			else {
				//losowanie koloru pierwszego gracza
				gospodarz.setKolor(rand() % 2 + 1);

				//bialy
				if (gospodarz.getKolor() == 1) {
					printf("Wylosowano kolor biały.\n\n");
					ai.setKolor(2);
				}
				//czarny
				else {
					printf("Wylosowano kolor czarny.\n\n");
					ai.setKolor(1);
				}

			}

			//start rozgrywki
			printf("\nZaczynamy grę!\n\n");
			while (1) {
				int check, licznik1 = 0, licznik2 = 0;

				//druk planszy dla gracza 1
				gra.print(gospodarz, ai);

				//ruch pierwszego gracza
				printf("Ruch gracza.\n");
				gospodarz.ruch();

				//sprawdzenie czy miejsce jest wolne
				check = gra.jesli_mozna_ustaw_pionek(gospodarz.getX(), gospodarz.getY(), gospodarz.getKolor());
				
				while (check == 0) {
					printf("Na wybranym miejscu nie można postawić pionka.\n");
					printf("Gdzie chcesz postawić pionek?\n");

					printf("X=");
					int x = scan_int(1, 19) - 1;
					gospodarz.setX(x);

					printf("Y=");
					int y = scan_int(1, 19) - 1;
					gospodarz.setY(y);

					check = gra.jesli_mozna_ustaw_pionek(gospodarz.getX(), gospodarz.getY(), gospodarz.getKolor());
				}

				//dodanie zbitych, jesli sa, do puli gracza 1
				licznik1 += gra.ile_zbitych_po_ruchu(gospodarz.getX(), gospodarz.getY(), gospodarz.getKolor());
				gospodarz.addZbite(licznik1);

				//druk planszy dla gracza
				gra.print(gospodarz, ai);

				//wincheck gracz 1
				if (gospodarz.getZbite() >= 10) {
					printf("Wygrywa gracz 1 poprzez zbicie %d pionków!\n", gospodarz.getZbite());
					break;
				}
				else if (gra.sprawdzenie_wygranej_przez_ulozenie_po_ruchu(gospodarz.getX(), gospodarz.getY(), gospodarz.getKolor())) {
					printf("Wygrywa gracz 1 poprzez ułożenie 5 pionków w rzędzie!\n");
					break;
				}			

				//ruch komputera, jesli miejsce jest zajete, powtarzamy losowanie////////////////////////////////////////////////////////////////////
				printf("Ruch komputera.\n");
				while (1) {
					ai.ruch();
					//jesli poprawnie mozna postawic pionek, opuszczamy petle losowania
					if (gra.jesli_mozna_ustaw_pionek(ai.getX(), ai.getY(), ai.getKolor()))	break;
				}

				//dodanie do licznika zbitych
				licznik2 += gra.ile_zbitych_po_ruchu(ai.getX(), ai.getY(), ai.getKolor());
				ai.addZbite(licznik2);

				//druk wybranych wspolrzednych przez komputer
				printf("Wylosowany ruch:\n");
				printf("X=%d\n", ai.getX());
				printf("Y=%d\n", ai.getY());

				//druk planszy dla gracza
				gra.print(gospodarz, ai);

				//wincheck komputer
				if (ai.getZbite() >= 10) {
					printf("Wygrywa gracz 1 poprzez zbicie %d pionków!\n", ai.getZbite());
					break;
				}
				else if (gra.sprawdzenie_wygranej_przez_ulozenie_po_ruchu(ai.getX(), ai.getY(), ai.getKolor())) {
					printf("Wygrywa gracz 1 poprzez ułożenie 5 pionków w rzędzie!\n");
					break;
				}
			}
		}
		//gracz vs gracz
		else {
			gracz gospodarz, gosc;

			//przygotowanie do gry, wybor kolorow
			printf("Jaki kolor wybiera pierwszy gracz?\n");
			printf("1. Biały.\n2. Czarny.\n3. Losowy.\n");
			choice = scan_int(1, 3);

			//bialy
			if (choice == 1) {
				gospodarz.setKolor(1);
				gosc.setKolor(2);
			}
			//czarny
			else if (choice == 2) {
				gospodarz.setKolor(1);
				gosc.setKolor(1);
			}
			//losowy
			else {
				gospodarz.setKolor(rand() % 2 + 1);
				if (gospodarz.getKolor() == 1) {
					printf("Wylosowano kolor biały.\n\n");
					gospodarz.setKolor(1);
					gosc.setKolor(2);
				}
				else {
					printf("Wylosowano kolor czarny.\n\n");
					gospodarz.setKolor(2);
					gosc.setKolor(1);
				}
			}

			//rozpoczecie rozgrywki
			printf("\nZaczynamy grę!\n\n");
			while (1) {
				int x, y, check, licznik1 = 0, licznik2 = 0;

				//druk planszy dla gracza 1
				gra.print(gospodarz, gosc);
				
				//ruch pierwszego gracza
				printf("Ruch gracza 1.\n");
				gospodarz.ruch();

				//sprawdzenie czy miejsce jest wolne
				check = gra.jesli_mozna_ustaw_pionek(gospodarz.getX(), gospodarz.getY(), gospodarz.getKolor());

				while (check == 0) {
					printf("Na wybranym miejscu nie można postawić pionka.\n");
					printf("Gdzie chcesz postawić pionek?\n");

					printf("X=");
					int x = scan_int(1, 19) - 1;
					gospodarz.setX(x);

					printf("Y=");
					int y = scan_int(1, 19) - 1;
					gospodarz.setY(y);

					check = gra.jesli_mozna_ustaw_pionek(gospodarz.getX(), gospodarz.getY(), gospodarz.getKolor());
				}

				//dodanie zbitych, jesli sa, do puli gracza 1
				licznik1 += gra.ile_zbitych_po_ruchu(gospodarz.getX(), gospodarz.getY(), gospodarz.getKolor());
				gospodarz.addZbite(licznik1);

				//druk planszy
				gra.print(gospodarz, gosc);

				//wincheck gracz 1
				if (gospodarz.getZbite() >= 10) {
					printf("Wygrywa gracz 1 poprzez zbicie %d pionków!\n", gospodarz.getZbite());
					break;
				}
				else if (gra.sprawdzenie_wygranej_przez_ulozenie_po_ruchu(gospodarz.getX(), gospodarz.getY(), gospodarz.getKolor())) {
					printf("Wygrywa gracz 1 poprzez ułożenie 5 pionków w rzędzie!\n");
					break;
				}

				//ruch drugiego gracza (gosc)////////////////////////////////////////////////////////////////////////////////////////////////////
				printf("Ruch gracza 2.\n");
				gosc.ruch();

				//sprawdzenie czy miejsce jest wolne
				check = gra.jesli_mozna_ustaw_pionek(gosc.getX(), gosc.getY(), gosc.getKolor());

				while (check == 0) {
					printf("Na wybranym miejscu nie można postawić pionka.\n");
					printf("Gdzie chcesz postawić pionek?\n");

					printf("X=");
					int x = scan_int(1, 19) - 1;
					gosc.setX(x);

					printf("Y=");
					int y = scan_int(1, 19) - 1;
					gosc.setY(y);

					check = gra.jesli_mozna_ustaw_pionek(gosc.getX(), gosc.getY(), gosc.getKolor());
				}

				//dodanie zbitych, jesli sa, do puli gracza 2
				licznik2 += gra.ile_zbitych_po_ruchu(gosc.getX(), gosc.getY(), gosc.getKolor());
				gosc.addZbite(licznik2);	

				//druk planszy
				gra.print(gospodarz, gosc);
				
				//wincheck gracz 2
				if (gosc.getZbite() >= 10) {
					printf("Wygrywa gracz 2 poprzez zbicie %d pionków!\n", gosc.getZbite());
					break;
				}
				else if (gra.sprawdzenie_wygranej_przez_ulozenie_po_ruchu(gosc.getX(), gosc.getY(), gosc.getKolor())) {
					printf("Wygrywa gracz 2 poprzez ułożenie 5 pionków w rzędzie!\n");
					break;
				}
			}
		}
	}
	else if (choice == 2) {

	}
	else {
		printf("Zamykanie gry...\n");
		exit(1);
	}

	return 0;
}