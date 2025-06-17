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

int ucitajIzBinarneDatoteke(Igrac igraci[], int* broj);
void spremiUBinarnuDatoteku(Igrac igraci[], int broj);
void spremiUBinarnu();
void ucitajIzTekstualne();


void sortirajPoGolovima();
void sortirajPoAsistencijama();
void sortirajPoImenu();
void pretraziPoImenu(const char* ime);


void prikaziStatistiku(Igrac igraci[], int broj);
void prikaziTrofeje();
void ispisiIgracePoPoziciji(Igrac igraci[], int broj);
void ispisiRekurzivno(int index);


int usporedbaGolova(const void*, const void*);
int usporedbaAsistencija(const void*, const void*);
int usporedbaImena(const void*, const void*);
void preimenujDatoteku(const char* staro, const char* novo);
void obrisiDatoteku(const char* naziv);
void ispisiVelicinuBinDatoteke();
void brisiMemoriju();

#endif
