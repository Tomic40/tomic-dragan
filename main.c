#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"

int main() {
    printf("\n-----Dobrodosli u sustav za pracenje voznog parka kamiona logisticke tvrtke!-----\n-----U nastavku imate izbornik pomocu kojeg mozete upravljati sustavom\n     (dodavati, brisati, azuzirati, pretrazivati itd...)!-----\n-----Ozake za kilometre, litre i sate ne morate pisati!-----\n");
    IzbornikOpcijaMain izbor;
    do {
        printf("\nGlavni izbornik:\n");
        printf("1. Prijava kao administrator\n");
        printf("2. Prijava kao korisnik\n");
        printf("3. Izlaz\n");
        printf("Odaberite opciju: ");
        scanf("%d", &izbor);
        getchar(); 

        switch (izbor) {
        case ADMINISTRATOR:
            prijavaAdministratora();
            break;
        case KORISNIK:
            prijavaKorisnika();
            break;
        case EXIT:
            printf("Izlaz iz programa.\n");
            return 0;
            break;
        default:
            printf("Nepostojeca opcija. Pokusajte ponovno.\n");
        }
    } while (izbor != EXIT);

    return 0;
}