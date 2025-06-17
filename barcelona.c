#define _CRT_SECURE_NO_WARNINGS
#include "barcelona.h"

Igrac* igraci = NULL;
int brojIgraca = 0;

const char* nazivPozicije(Pozicija p) {
    switch (p) {
    case VRATAR: return "Vratar";
    case OBRANA: return "Obrana";
    case VEZNI: return "Vezni";
    case NAPAD: return "Napad";
    default: return "Nepoznato";
    }
}

int ucitajIzBinarneDatoteke(Igrac igraci_local[], int* broj) {
    FILE* file = fopen("igraci.dat", "rb");
    if (!file) return 0;

    fread(broj, sizeof(int), 1, file);
    igraci = malloc(*broj * sizeof(Igrac));
    if (!igraci) {
        perror("Greska pri alokaciji memorije");
        fclose(file);
        return 0;
    }

    fread(igraci, sizeof(Igrac), *broj, file);
    fclose(file);
    return 1;
}

void spremiUBinarnuDatoteku(Igrac igraci[], int broj) {
    FILE* file = fopen("igraci.dat", "wb");
    if (!file) {
        perror("Greska pri spremanju u binarnu datoteku");
        return;
    }
    fwrite(&broj, sizeof(int), 1, file);
    fwrite(igraci, sizeof(Igrac), broj, file);
    fclose(file);
}

void spremiUBinarnu() {
    FILE* file = fopen("igraci.dat", "wb");
    if (!file) {
        perror("Greska pri spremanju u binarnu datoteku");
        return;
    }
    fwrite(&brojIgraca, sizeof(int), 1, file);
    fwrite(igraci, sizeof(Igrac), brojIgraca, file);
    fclose(file);
}

void ucitajIzTekstualne() {
    FILE* f = fopen("igraci.txt", "r");
    if (!f) { perror("Greska otvaranja"); return; }

    Igrac temp;
    while (fscanf(f, "%d;%29[^;];%d;%d;%d;%d\n", &temp.id, temp.ime,
        &temp.dob, (int*)&temp.pozicija, &temp.golovi, &temp.asistencije) == 6) {
        void* novi = realloc(igraci, (brojIgraca + 1) * sizeof(Igrac));
        if (!novi) {
            perror("realloc failed");
            exit(EXIT_FAILURE);
        }
        igraci = novi;
        igraci[brojIgraca++] = temp;
    }
    fclose(f);
}

void dodajIgraca() {
    void* novi = realloc(igraci, (brojIgraca + 1) * sizeof(Igrac));
    if (!novi) {
        perror("Greska pri alokaciji memorije");
        exit(EXIT_FAILURE);
    }
    igraci = novi;

    Igrac noviIgrac;
    noviIgrac.id = brojIgraca + 1;

    printf("Unesi ime igraca: ");
    if (scanf(" %29[^\n]", noviIgrac.ime) != 1) return;
    printf("Unesi dob: ");
    if (scanf("%d", &noviIgrac.dob) != 1) return;
    printf("Pozicija (1-Vratar, 2-Obrana, 3-Vezni, 4-Napad): ");
    int p;
    if (scanf("%d", &p) != 1) return;
    noviIgrac.pozicija = (Pozicija)p;
    printf("Golovi: ");
    if (scanf("%d", &noviIgrac.golovi) != 1) return;
    printf("Asistencije: ");
    if (scanf("%d", &noviIgrac.asistencije) != 1) return;

    igraci[brojIgraca++] = noviIgrac;
}

void azurirajIgraca() {
    int id;
    printf("Unesi ID igraca za azuriranje: ");
    if (scanf("%d", &id) != 1) return;
    for (int i = 0; i < brojIgraca; i++) {
        if (igraci[i].id == id) {
            printf("Novo ime: ");
            if (scanf(" %29[^\n]", igraci[i].ime) != 1) return;
            printf("Nova dob: ");
            if (scanf("%d", &igraci[i].dob) != 1) return;
            printf("Novi broj golova: ");
            if (scanf("%d", &igraci[i].golovi) != 1) return;
            printf("Novi broj asistencija: ");
            if (scanf("%d", &igraci[i].asistencije) != 1) return;
            return;
        }
    }
    printf("Igrac s ID %d nije pronaden.\n", id);
}

void obrisiIgraca() {
    int id;
    printf("Unesi ID igraca za brisanje: ");
    if (scanf("%d", &id) != 1) return;
    for (int i = 0; i < brojIgraca; i++) {
        if (igraci[i].id == id) {
            for (int j = i; j < brojIgraca - 1; j++) {
                igraci[j] = igraci[j + 1];
            }
            brojIgraca--;
            void* novi = realloc(igraci, brojIgraca * sizeof(Igrac));
            if (!novi && brojIgraca > 0) {
                perror("realloc failed");
                exit(EXIT_FAILURE);
            }
            igraci = novi;
            printf("Igrac obrisan.\n");
            return;
        }
    }
    printf("Igrac nije pronaden.\n");
}

void sortirajPoGolovima() {
    qsort(igraci, brojIgraca, sizeof(Igrac), usporedbaGolova);
}

void sortirajPoAsistencijama() {
    qsort(igraci, brojIgraca, sizeof(Igrac), usporedbaAsistencija);
}

int usporedbaGolova(const void* a, const void* b) {
    return ((Igrac*)b)->golovi - ((Igrac*)a)->golovi;
}

int usporedbaAsistencija(const void* a, const void* b) {
    return ((Igrac*)b)->asistencije - ((Igrac*)a)->asistencije;
}

int usporedbaImena(const void* a, const void* b) {
    return strcmp(((Igrac*)a)->ime, ((Igrac*)b)->ime);
}

void sortirajPoImenu() {
    qsort(igraci, brojIgraca, sizeof(Igrac), usporedbaImena);
}

void pretraziPoImenu(const char* ime) {
    for (int i = 0; i < brojIgraca; i++) {
        if (strcmp(igraci[i].ime, ime) == 0) {
            printf("Pronaden: %s, %d god, Pozicija: %s, Golovi: %d, Asistencije: %d\n",
                igraci[i].ime, igraci[i].dob, nazivPozicije(igraci[i].pozicija), igraci[i].golovi, igraci[i].asistencije);
            return;
        }
    }
    printf("Nema igraca s tim imenom.\n");
}

void ispisiRekurzivno(int index) {
    if (index >= brojIgraca) return;
    printf("%d. %s, %d god, Pozicija: %s, Golovi: %d, Asistencije: %d\n",
        igraci[index].id, igraci[index].ime, igraci[index].dob,
        nazivPozicije(igraci[index].pozicija), igraci[index].golovi, igraci[index].asistencije);
    ispisiRekurzivno(index + 1);
}

void preimenujDatoteku(const char* staro, const char* novo) {
    if (rename(staro, novo) != 0) {
        perror("Greska pri preimenovanju");
    }
    else {
        printf("Datoteka preimenovana.\n");
    }
}

void obrisiDatoteku(const char* naziv) {
    if (remove(naziv) != 0) {
        perror("Greska pri brisanju");
    }
    else {
        printf("Datoteka obrisana.\n");
    }
}

void ispisiVelicinuBinDatoteke() {
    FILE* f = fopen("igraci.dat", "rb");
    if (!f) { perror("Greska otvaranja"); return; }
    fseek(f, 0, SEEK_END);
    long velicina = ftell(f);
    fclose(f);
    printf("Velicina binarne datoteke: %ld bajtova\n", velicina);
}

void prikaziStatistiku(Igrac igraci[], int broj) {
    printf("\nStatistika igraca (2024/25):\n");
    for (int i = 0; i < broj; i++) {
        printf("%s - Golovi: %d, Asistencije: %d\n", igraci[i].ime, igraci[i].golovi, igraci[i].asistencije);
    }
}

void prikaziTrofeje() {
    printf("\n--- Trofeji FC Barcelone ---\n");
    printf("La Liga: 27\n");
    printf("Copa del Rey: 31\n");
    printf("Liga prvaka: 5\n");
    printf("Superkup Europe: 5\n");
    printf("Klupsko SP: 3\n");
}

void ispisiIgracePoPoziciji(Igrac igraci[], int broj) {
    printf("\n--- Igraci po pozicijama ---\n");
    for (int p = VRATAR; p <= NAPAD; p++) {
        printf("\nPozicija: %s\n", nazivPozicije((Pozicija)p));
        for (int i = 0; i < broj; i++) {
            if (igraci[i].pozicija == p) {
                printf("- %s\n", igraci[i].ime);
            }
        }
    }
}

void brisiMemoriju() {
    free(igraci);
    igraci = NULL;
    brojIgraca = 0;
}

