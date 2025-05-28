#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "barcelona.h"

void ucitajIgrace(Igrac igraci[], int* broj) {
    FILE* file = fopen("igraci.txt", "r");
    if (!file) {
        perror("Greska pri otvaranju fajla igraci.txt");
        return;
    }

    char linija[100];
    *broj = 0;

    while (fgets(linija, sizeof(linija), file)) {
        // Ukloni \n s kraja ako postoji
        linija[strcspn(linija, "\n")] = 0;

        if (strlen(linija) == 0) continue; // preskoci prazne redove

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

    char linija[100];
    while (fgets(linija, sizeof(linija), file)) {
        int id, golovi, asistencije;
        char ime[50];
        if (sscanf(linija, "%d;%49[^;];%d;%d", &id, ime, &golovi, &asistencije) == 4) {
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

void prikaziNajboljeStrijelce(Igrac igraci[], int broj) {
    printf("\n--- Najbolji strijelci ---\n");

    for (int i = 0; i < broj - 1; i++) {
        for (int j = i + 1; j < broj; j++) {
            if (igraci[i].golovi < igraci[j].golovi) {
                Igrac temp = igraci[i];
                igraci[i] = igraci[j];
                igraci[j] = temp;
            }
        }
    }

    for (int i = 0; i < broj; i++) {
        printf("%s - %d golova\n", igraci[i].ime, igraci[i].golovi);
    }
}

void prikaziNajboljeAsistente(Igrac igraci[], int broj) {
    printf("\n--- Najbolji asistenti ---\n");

    for (int i = 0; i < broj - 1; i++) {
        for (int j = i + 1; j < broj; j++) {
            if (igraci[i].asistencije < igraci[j].asistencije) {
                Igrac temp = igraci[i];
                igraci[i] = igraci[j];
                igraci[j] = temp;
            }
        }
    }

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

    char linija[100];
    printf("\n--- Trofeji FC Barcelone ---\n");
    while (fgets(linija, sizeof(linija), file)) {
        printf("%s", linija);
    }

    fclose(file);
}