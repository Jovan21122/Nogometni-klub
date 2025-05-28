#ifndef BARCELONA_H
#define BARCELONA_H

#define MAX_IGRACA 100
#define MAX_LINIJA 256


typedef struct {
    int id;
    char ime[50];
    char pozicija[20];
    int golovi;
    int asistencije;
} Igrac;


void ucitajIgrace(Igrac igraci[], int* broj);
void ucitajStatistiku(Igrac igraci[], int broj);
void prikaziIgrace(Igrac igraci[], int broj);
void prikaziStatistiku(Igrac igraci[], int broj);
void sortirajPoGolovima(Igrac igraci[], int broj);
void sortirajPoAsistencijama(Igrac igraci[], int broj);
void prikaziTrofeje(void);
void menu();

#endif
