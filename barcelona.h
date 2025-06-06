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
void prikaziNajboljeStrijelce(Igrac igraci[], int broj);
void prikaziNajboljeAsistente(Igrac igraci[], int broj);
void prikaziTrofeje();
void ispisiIgracePoPoziciji(Igrac igraci[], int broj);
void pretraziIgracaPoImenu(Igrac igraci[], int broj, const char* ime);

#endif
