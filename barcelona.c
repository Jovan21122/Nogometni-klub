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
        perror("Alokacija neuspješna");
        fclose(file);
        return 0;
    }
    fread(igraci, sizeof(Igrac), *broj, file);
    fclose(file);
    return 1;
}

void spremiUBinarnuDatoteku(Igrac igraci[], int broj) {
    FILE* file = fopen("igraci.dat", "wb");
    if (!file) return;
    fwrite(&broj, sizeof(int), 1, file);
    fwrite(igraci, sizeof(Igrac), broj, file);
    fclose(file);
}

void spremiUBinarnu() {
    spremiUBinarnuDatoteku(igraci, brojIgraca);
}

void dodajIgraca() {
    void* novi = realloc(igraci, (brojIgraca + 1) * sizeof(Igrac));
    if (!novi) {
        perror("realloc failed");
        return;
    }
    igraci = novi;

    Igrac noviIgrac;
    noviIgrac.id = brojIgraca + 1;

    printf("Unesi ime igraca: ");
    scanf(" %29[^\n]", noviIgrac.ime);
    printf("Unesi dob: ");
    scanf("%d", &noviIgrac.dob);
    printf("Pozicija (1-Vratar, 2-Obrana, 3-Vezni, 4-Napad): ");
    int p;
    scanf("%d", &p);
    noviIgrac.pozicija = (Pozicija)p;
    printf("Golovi: ");
    scanf("%d", &noviIgrac.golovi);
    printf("Asistencije: ");
    scanf("%d", &noviIgrac.asistencije);

    igraci[brojIgraca++] = noviIgrac;
}

void azurirajIgraca() {
    int id;
    printf("Unesi ID igraca za azuriranje: ");
    scanf("%d", &id);

    for (int i = 0; i < brojIgraca; i++) {
        if (igraci[i].id == id) {
            printf("Novo ime: ");
            scanf(" %29[^\n]", igraci[i].ime);
            printf("Nova dob: ");
            scanf("%d", &igraci[i].dob);
            printf("Novi broj golova: ");
            scanf("%d", &igraci[i].golovi);
            printf("Novi broj asistencija: ");
            scanf("%d", &igraci[i].asistencije);
            return;
        }
    }
    printf("Igrac nije pronadjen.\n");
}

void obrisiIgraca() {
    int id;
    printf("Unesi ID igraca za brisanje: ");
    scanf("%d", &id);

    for (int i = 0; i < brojIgraca; i++) {
        if (igraci[i].id == id) {
            for (int j = i; j < brojIgraca - 1; j++)
                igraci[j] = igraci[j + 1];
            brojIgraca--;
            igraci = realloc(igraci, brojIgraca * sizeof(Igrac));
            printf("Igrac obrisan.\n");
            return;
        }
    }
    printf("Igrac nije pronadjen.\n");
}

void brisiMemoriju() {
    free(igraci);
    igraci = NULL;
    brojIgraca = 0;
}

void sortirajPoGolovima() {
    qsort(igraci, brojIgraca, sizeof(Igrac), usporedbaGolova);
}
void sortirajPoAsistencijama() {
    qsort(igraci, brojIgraca, sizeof(Igrac), usporedbaAsistencija);
}
void sortirajPoImenu() {
    qsort(igraci, brojIgraca, sizeof(Igrac), usporedbaImena);
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

void pretraziPoImenu(const char* ime) {
    for (int i = 0; i < brojIgraca; i++) {
        if (strcmp(igraci[i].ime, ime) == 0) {
            printf("Pronaden: %s (%d god) | Pozicija: %s | Golovi: %d | Asistencije: %d\n",
                igraci[i].ime, igraci[i].dob, nazivPozicije(igraci[i].pozicija),
                igraci[i].golovi, igraci[i].asistencije);
            return;
        }
    }
    printf("Nema igraca s tim imenom.\n");
}

void ispisiRekurzivno(int index) {
    if (index >= brojIgraca) return;
    printf("%d. %s, %d god, %s, Golovi: %d, Asistencije: %d\n",
        igraci[index].id, igraci[index].ime, igraci[index].dob,
        nazivPozicije(igraci[index].pozicija),
        igraci[index].golovi, igraci[index].asistencije);
    ispisiRekurzivno(index + 1);
}

void ispisiIgracePoPoziciji(Igrac igraci[], int broj) {
    for (int p = VRATAR; p <= NAPAD; p++) {
        printf("\n--- %s ---\n", nazivPozicije((Pozicija)p));
        for (int i = 0; i < broj; i++) {
            if (igraci[i].pozicija == p)
                printf("%s\n", igraci[i].ime);
        }
    }
}

void prikaziStatistiku(Igrac igraci[], int broj) {
    printf("\n--- Statistika (2024/25) ---\n");
    for (int i = 0; i < broj; i++) {
        printf("%s - Golovi: %d, Asistencije: %d\n", igraci[i].ime, igraci[i].golovi, igraci[i].asistencije);
    }
}

void prikaziTrofeje() {
    printf("\n--- Trofeji FC Barcelone ---\n");
    printf("La Liga: 27\nCopa del Rey: 31\nLiga prvaka: 5\nSuperkup Europe: 5\nKlupsko SP: 3\n");
}

void ispisiVelicinuBinDatoteke() {
    FILE* file = fopen("igraci.dat", "rb");
    if (!file) {
        perror("Ne mogu otvoriti datoteku");
        return;
    }

    fseek(file, 0, SEEK_END);
    long velicina = ftell(file);
    fclose(file);

    printf("Velicina binarne datoteke: %ld bajtova\n", velicina);
}
