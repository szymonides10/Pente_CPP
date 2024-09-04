#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#pragma warning(disable:4996)

char int_ascii(int a) {
	return (a + 'a');
}

void flush() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

void print_pente3d() {
	printf("                                             ,----,            \n");
	printf(",-.----.                        ,--.       ,/   .`|            \n");
	printf("\\    /  \\       ,---,.        ,--.'|     ,`   .'  :     ,---,. \n");
	printf("|   :    \\    ,'  .' |    ,--,:  : |   ;    ;     /   ,'  .' | \n");
	printf("|   |  .\\ : ,---.'   | ,`--.'`|  ' : .'___,/    ,'  ,---.'   | \n");
	printf(".   :  |: | |   |   .' |   :  :  | | |    :     |   |   |   .' \n");
	printf("|   |   \\ : :   :  |-, :   |   \\ | : ;    |.';  ;   :   :  |-, \n");
	printf("|   : .   / :   |  ;/| |   : '  '; | `----'  |  |   :   |  ;/| \n");
	printf(";   | |`-'  |   :   .' '   ' ;.    ;     '   :  ;   |   :   .'  \n");
	printf("|   | ;     |   |  |-, |   | | \\   |     |   |  '   |   |  |-, \n");
	printf(":   ' |     '   :  ;/| '   : |  ; .'     '   :  |   '   :  ;/| \n");
	printf("|   | :     |   :   .' '   : |           '---'      |   :   .' \n");
	printf("`---'.|     |   | ,'   ;   |.'                      |   | ,'   \n");
	printf("  `---`     `----'     '---'                        `----'     \n");
	printf("                                                               \n\n");

}

void info() {
	setlocale(LC_ALL, "");
	printf("Autor programu: Szymon Jarząbski.\n\n");
	print_pente3d();
}

int czy_plik_istnieje(char* nazwa) {
	FILE* stream = fopen(nazwa, "r");
	if (stream == NULL)	return 0;
	else return 1;
}

int scan_int(int min, int max) {
	int x;
	while ((scanf_s("%d", &x)) != 1 || x<min || x>max) {
		printf("Złe dane, wprowadź jeszcze raz.\n");
		flush();
	}
	return x;
}