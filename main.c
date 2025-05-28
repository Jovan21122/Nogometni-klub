#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "barcelona.h"

void menu() {
    Igrac igraci[100];
    int broj = 0;

    ucitajIgrace(igraci, &broj);
    ucitajStatistiku(igraci, broj);

    int izbor;
    do {
        printf("\n--- FC Barcelona Menu ---\n");
        printf("1. Prikaz igraca\n");
        printf("2. Prikaz statistike igraca (2024/25)\n");
        printf("3. Najbolji strijelci\n");
        printf("4. Najbolji asistenti\n");
        printf("5. Prikaz trofeja\n");
        printf("0. Izlaz\n");
        printf("Izbor: ");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            prikaziIgrace(igraci, broj);
            break;
        case 2:
            prikaziStatistiku(igraci, broj);
            break;
        case 3:
            prikaziNajboljeStrijelce(igraci, broj);
            break;
        case 4:
            prikaziNajboljeAsistente(igraci, broj);
            break;
        case 5:
            prikaziTrofeje();
            break;
        case 0:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Nepoznat izbor. Pokusaj ponovo.\n");
        }

    } while (izbor != 0);
}

int main() {
    menu();
    return 0;
}
