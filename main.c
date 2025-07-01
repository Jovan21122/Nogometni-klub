#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "barcelona.h"

typedef enum {
    IZLAZ,
    PRIKAZ_IGRACA,
    STATISTIKA,
    STRIJELCI,
    ASISTENTI,
    TROFEJI,
    PRETRAGA,
    POZICIJE,
    DODAJ,
    AZURIRAJ,
    OBRISI,
    SORT_G,
    SORT_A,
    SORT_I,
    OBRISI_SVE
} Izbor;

void menu() {
    if (!ucitajIzBinarneDatoteke(igraci, &brojIgraca)) {
        printf("Binarna datoteka nije pronadjena. Trenutno nema igraca.\n");
    }
    else {
        printf("Podaci uspjesno ucitani iz binarne datoteke.\n");
    }

    int izbor;
    char imeZaPretragu[30];

    do {
        printf("\n--- FC Barcelona Menu ---\n");
        printf("1. Prikaz igraca\n2. Statistika\n3. Najbolji strijelci\n4. Najbolji asistenti\n");
        printf("5. Trofeji\n6. Pretraga po imenu\n7. Igraci po pozicijama\n");
        printf("8. Dodaj igraca\n9. Azuriraj igraca\n10. Obrisi igraca\n");
        printf("11. Sortiraj po golovima\n12. Sortiraj po asistencijama\n13. Sortiraj po imenu\n");
        printf("14. Obrisi sve igrace\n0. Izlaz\nIzbor: ");
        scanf("%d", &izbor);

        switch ((Izbor)izbor) {
        case PRIKAZ_IGRACA: ispisiRekurzivno(0); break;
        case STATISTIKA: prikaziStatistiku(igraci, brojIgraca); break;
        case STRIJELCI: sortirajPoGolovima(); ispisiRekurzivno(0); break;
        case ASISTENTI: sortirajPoAsistencijama(); ispisiRekurzivno(0); break;
        case TROFEJI: prikaziTrofeje(); break;
        case PRETRAGA:
            printf("Unesi ime igraca: ");
            scanf(" %29[^\n]", imeZaPretragu);
            pretraziPoImenu(imeZaPretragu);
            break;
        case POZICIJE: ispisiIgracePoPoziciji(igraci, brojIgraca); break;
        case DODAJ: dodajIgraca(); break;
        case AZURIRAJ: azurirajIgraca(); break;
        case OBRISI: obrisiIgraca(); break;
        case SORT_G: sortirajPoGolovima(); ispisiRekurzivno(0); break;
        case SORT_A: sortirajPoAsistencijama(); ispisiRekurzivno(0); break;
        case SORT_I: sortirajPoImenu(); ispisiRekurzivno(0); break;
        case OBRISI_SVE:
            brisiMemoriju();
            remove("igraci.dat");
            printf("Svi igraci i datoteka su obrisani.\n");
            break;
        case IZLAZ:
            spremiUBinarnu();
            brisiMemoriju();
            ispisiVelicinuBinDatoteke();
            printf("Podaci spremljeni. Izlaz iz programa.\n");
            break;
        default: printf("Nepoznat izbor.\n");
        }
    } while (izbor != 0);
}

int main() {
    menu();
    return 0;
}
