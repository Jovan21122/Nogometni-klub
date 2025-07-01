#ifndef BARCELONA_H
#define BARCELONA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    VRATAR = 1,
    OBRANA,
    VEZNI,
    NAPAD
} Pozicija;

typedef struct {
    int id;
    char ime[30];
    int dob;
    Pozicija pozicija;
    int golovi;
    int asistencije;
} Igrac;

extern Igrac* igraci;
extern int brojIgraca;

const char* nazivPozicije(Pozicija p);

void dodajIgraca();
void azurirajIgraca();
void obrisiIgraca();
void brisiMemoriju();

int ucitajIzBinarneDatoteke(Igrac igraci_local[], int* broj);
void spremiUBinarnu();
void spremiUBinarnuDatoteku(Igrac igraci[], int broj);

void sortirajPoGolovima();
void sortirajPoAsistencijama();
void sortirajPoImenu();
void pretraziPoImenu(const char* ime);

void ispisiRekurzivno(int index);
void ispisiIgracePoPoziciji(Igrac igraci[], int broj);
void prikaziStatistiku(Igrac igraci[], int broj);
void prikaziTrofeje();
void ispisiVelicinuBinDatoteke();

int usporedbaGolova(const void*, const void*);
int usporedbaAsistencija(const void*, const void*);
int usporedbaImena(const void*, const void*);

#endif
