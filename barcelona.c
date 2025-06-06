#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "barcelona.h"



void ucitajIgrace(Igrac igraci[], int* broj) {
    FILE* file = fopen("igraci.txt", "r");
    if (!file) {
        perror("Greska pri otvaranju fajla igraci.txt");
        return;
    }

    char linija[MAX_LINIJA];
    *broj = 0;

    while (fgets(linija, sizeof(linija), file)) {
        linija[strcspn(linija, "\n")] = 0;
        if (strlen(linija) == 0) continue;

        Igrac igrac;
        if (sscanf(linija, "%d;%49[^;];%19[^\n]", &igrac.id, igrac.ime, igrac.pozicija) == 3) {
            igrac.golovi = 0;
            igrac.asistencije = 0;
            igraci[(*broj)++] = igrac;
        }
        else {
            printf("Preskacem neispravnu liniju: %s\n", linija);
        }
    }

    fclose(file);
}

void ucitajStatistiku(Igrac igraci[], int broj) {
    FILE* file = fopen("statistika.txt", "r");
    if (!file) {
        perror("Greska pri otvaranju fajla statistika.txt");
        return;
    }

    char linija[MAX_LINIJA];
    while (fgets(linija, sizeof(linija), file)) {
        int id, golovi, asistencije;
        char ime[50];
        if (sscanf(linija, " %d ; %49[^;] ; %d ; %d", &id, ime, &golovi, &asistencije) == 4) {

            for (int i = 0; i < broj; i++) {
                if (igraci[i].id == id) {
                    igraci[i].golovi = golovi;
                    igraci[i].asistencije = asistencije;
                    break;
                }
            }
        }
    }

    fclose(file);
}
    


void prikaziIgrace(Igrac igraci[], int broj) {
    printf("\n--- Igraci ---\n");
    for (int i = 0; i < broj; i++) {
        printf("%d. %s - %s\n", igraci[i].id, igraci[i].ime, igraci[i].pozicija);
    }
}

void prikaziStatistiku(Igrac igraci[], int broj) {
    printf("\n--- Statistika igraca (2024/25) ---\n");
    for (int i = 0; i < broj; i++) {
        printf("%s: %d golova, %d asistencija\n", igraci[i].ime, igraci[i].golovi, igraci[i].asistencije);
    }
}


int usporedbaGolova(const void* a, const void* b) {
    return ((Igrac*)b)->golovi - ((Igrac*)a)->golovi;
}
void sortirajPoGolovima(Igrac igraci[], int broj) {
    qsort(igraci, broj, sizeof(Igrac), usporedbaGolova);
}

int usporedbaAsistencija(const void* a, const void* b) {
    return ((Igrac*)b)->asistencije - ((Igrac*)a)->asistencije;
}
void sortirajPoAsistencijama(Igrac igraci[], int broj) {
    qsort(igraci, broj, sizeof(Igrac), usporedbaAsistencija);
}

void prikaziNajboljeStrijelce(Igrac igraci[], int broj) {
    printf("\n--- Najbolji strijelci ---\n");
    sortirajPoGolovima(igraci, broj);
    for (int i = 0; i < broj; i++) {
        printf("%s - %d golova\n", igraci[i].ime, igraci[i].golovi);
    }
}

void prikaziNajboljeAsistente(Igrac igraci[], int broj) {
    printf("\n--- Najbolji asistenti ---\n");
    sortirajPoAsistencijama(igraci, broj);
    for (int i = 0; i < broj; i++) {
        printf("%s - %d asistencija\n", igraci[i].ime, igraci[i].asistencije);
    }
}

void prikaziTrofeje() {
    FILE* file = fopen("trofeji.txt", "r");
    if (!file) {
        perror("Greska pri otvaranju fajla trofeji.txt");
        return;
    }

    char linija[MAX_LINIJA];
    printf("\n--- Trofeji FC Barcelone ---\n");
    while (fgets(linija, sizeof(linija), file)) {
        printf("%s", linija);
    }

    fclose(file);
}


int usporediImena(const void* a, const void* b) {
    Igrac* igrac1 = (Igrac*)a;
    Igrac* igrac2 = (Igrac*)b;
    return _stricmp(igrac1->ime, igrac2->ime);
}


Igrac* pretraziIgracaPoImenu(Igrac igraci[], int broj, const char* ime) {
    sortirajPoGolovima(igraci, broj);
    Igrac temp;
    strncpy(temp.ime, ime, sizeof(temp.ime));
    return (Igrac*)bsearch(&temp, igraci, broj, sizeof(Igrac), usporediImena);
}


void ispisiIgraceRekurzivno(Igrac igraci[], int indeks, int broj) {
    if (indeks >= broj) return;
    printf("%d. %s - %s\n", igraci[indeks].id, igraci[indeks].ime, igraci[indeks].pozicija);
    ispisiIgraceRekurzivno(igraci, indeks + 1, broj);
}

void preimenujStatistiku() {
    if (rename("statistika.txt", "stara_statistika.txt") == 0)
        printf("Datoteka preimenovana.\n");
    else
        perror("Greska pri preimenovanju.");
}

void obrisiTrofeje() {
    if (remove("trofeji.txt") == 0)
        printf("Datoteka trofeji.txt je obrisana.\n");
    else
        perror("Greska pri brisanju.");
}
