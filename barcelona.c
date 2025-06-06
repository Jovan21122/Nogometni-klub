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

void prikaziNajboljeStrijelce(Igrac igraci[], int broj) {
    printf("\n--- Najbolji strijelci ---\n");
    for (int i = 0; i < broj; i++) {
        for (int j = i + 1; j < broj; j++) {
            if (igraci[j].golovi > igraci[i].golovi) {
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
    for (int i = 0; i < broj; i++) {
        for (int j = i + 1; j < broj; j++) {
            if (igraci[j].asistencije > igraci[i].asistencije) {
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

    char linija[MAX_LINIJA];
    printf("\n--- Trofeji FC Barcelone ---\n");
    while (fgets(linija, sizeof(linija), file)) {
        printf("%s", linija);
    }

    fclose(file);
}

void ispisiIgracePoPoziciji(Igrac igraci[], int broj) {
    const char* pozicije[] = { "Golman", "Branic", "Vezni", "Napadac" };
    int n = sizeof(pozicije) / sizeof(pozicije[0]);

    printf("\n--- Igraci po pozicijama ---\n");
    for (int p = 0; p < n; p++) {
        printf("\n%s:\n", pozicije[p]);
        for (int i = 0; i < broj; i++) {
            if (_stricmp(igraci[i].pozicija, pozicije[p]) == 0) {
                printf("%s\n", igraci[i].ime);
            }
        }
    }
}

void pretraziIgracaPoImenu(Igrac igraci[], int broj, const char* ime) {
    int found = 0;
    for (int i = 0; i < broj; i++) {
        if (_stricmp(igraci[i].ime, ime) == 0) {
            printf("Pronadjen: %s - %s, Golovi: %d, Asistencije: %d\n",
                igraci[i].ime, igraci[i].pozicija, igraci[i].golovi, igraci[i].asistencije);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Igrac nije pronadjen.\n");
    }
}
