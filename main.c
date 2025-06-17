#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "barcelona.h"

typedef enum {
    IZLAZ,
    PRIKAZ_IGRACA,
    STATISTIKA,
    STRIJELCI,
    ASISTENTI,
    TROFEJI,
    PRETRAGA,
    POZICIJE
} Izbor;

void menu() {
    if (!ucitajIzBinarneDatoteke(igraci, &brojIgraca)) {
        printf("Binarna datoteka nije pronadjena. Ucitavanje iz tekstualne...
");
        ucitajIzTekstualne();
        spremiUBinarnu();
    }
    else {
        printf("Podaci uspjesno ucitani iz binarne datoteke.
");
    }

    int izbor;
    char imeZaPretragu[30];

    do {
        printf("\n--- FC Barcelona Menu ---\n");
        printf("1. Prikaz igraca\n");
        printf("2. Prikaz statistike igraca (2024/25)\n");
        printf("3. Najbolji strijelci\n");
        printf("4. Najbolji asistenti\n");
        printf("5. Prikaz trofeja\n");
        printf("6. Pretraga igraca po imenu\n");
        printf("7. Ispis igraca po pozicijama\n");
        printf("0. Izlaz\n");
        printf("Izbor: ");
        if (scanf("%d", &izbor) != 1) break;

        switch ((Izbor)izbor) {
            case PRIKAZ_IGRACA:
                ispisiRekurzivno(0);
                break;
            case STATISTIKA:
                prikaziStatistiku(igraci, brojIgraca);
                break;
            case STRIJELCI:
                sortirajPoGolovima();
                ispisiRekurzivno(0);
                break;
            case ASISTENTI:
                sortirajPoAsistencijama();
                ispisiRekurzivno(0);
                break;
            case TROFEJI:
                prikaziTrofeje();
                break;
            case PRETRAGA:
                printf("Unesi ime igraca: ");
                scanf(" %[^
]", imeZaPretragu);
                pretraziPoImenu(imeZaPretragu);
                break;
            case POZICIJE:
                ispisiIgracePoPoziciji(igraci, brojIgraca);
                break;
            case IZLAZ:
                spremiUBinarnu();
                brisiMemoriju();
                printf("Podaci spremljeni. Izlaz iz programa.\n");
                break;
            default:
                printf("Nepoznat izbor. Pokusaj ponovo.\n");
        }
    } while (izbor != 0);
}

int main() {
    menu();
    return 0;
}
