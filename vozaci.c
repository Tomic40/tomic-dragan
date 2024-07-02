#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

//fnkcija za dodavanje vozaca
void dodajVozaca() {
    FILE* file = fopen("vozaci.txt", "a+");
    if (file == NULL) {
        perror("Ne moze se otvoriti datoteka za vozace");
        exit(1);
    }

    Vozac* noviVozac = (Vozac*)malloc(sizeof(Vozac));
    if (noviVozac == NULL) {
        perror("Ne moze se alocirati memorija za novog vozaca");
        fclose(file);
        exit(1);
    }

    printf("Unesite ID: ");
    if (scanf("%d", &noviVozac->id) != 1) {
        printf("Neispravan unos ID-a.\n");
        fclose(file);
        free(noviVozac);
        return;
    }

   // Provjera da li ID već postoji
    fseek(file, 0, SEEK_SET); // Premjesti pokazivač na početak datoteke
    char line[256]; // Pretpostavka: linija neće biti dulja od 255 znakova
    int idPostoji = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        int id;
        if (sscanf(line, "ID vozaca: %d", &id) == 1) {
            if (id == noviVozac->id) {
                idPostoji = 1;
                break;
            }
        }
    }


    if (idPostoji) {
        printf("Vozac sa ID %d vec postoji.\n", noviVozac->id);
        fclose(file);
        free(noviVozac);
        return;
    }

    printf("Unesite ime: ");
    if (scanf("%s", noviVozac->ime) != 1) {
        fclose(file);
        free(noviVozac);
        return;
    }

    printf("Unesite prezime: ");
    if (scanf("%s", noviVozac->prezime) != 1) {
        fclose(file);
        free(noviVozac);
        return;
    }

    printf("Unesite broj vozacke dozvole: ");
    if (scanf("%s", noviVozac->vozackaDozvola) != 1) {
        printf("Neispravan unos broja vozacke dozvole.\n\n");
        fclose(file);
        free(noviVozac);
        return;
    }

    printf("Unesite godine iskustva: ");
    if (scanf("%d", &noviVozac->godineIskustva) != 1) {
        printf("Neispravan unos godina iskustva.\n\n");
        fclose(file);
        free(noviVozac);
        return;
    }

    // Premjesti pokazivač na kraj datoteke za dodavanje novog vozača
    fseek(file, 0, SEEK_END);
    fprintf(file, "ID vozaca: %d\nIme vozaca: %s\nPrezime vozaca: %s\nBroj vozacke dozvole: %s\nGodine iskustva: %d\n\n", noviVozac->id, noviVozac->ime, noviVozac->prezime, noviVozac->vozackaDozvola, noviVozac->godineIskustva);

    fclose(file);
    free(noviVozac);
    printf("Vozac uspjesno dodan.\n\n");
}

//fnkcija z abrisanje vozaca
void brisiVozaca() {
    FILE* file = fopen("vozaci.txt", "r");
    if (file == NULL) {
        perror("Ne moze se otvoriti datoteka za vozace");
        exit(1);
    }

    FILE* tempFile = fopen("temp_vozaci.txt", "w");
    if (tempFile == NULL) {
        perror("Ne moze se otvoriti privremena datoteka");
        fclose(file);
        exit(1);
    }

    int idZaBrisanje;
    printf("Unesite ID vozaca kojeg zelite obrisati: ");
    if (scanf("%d", &idZaBrisanje) != 1) {
        printf("Neispravan unos ID-a.\n");
        fclose(file);
        fclose(tempFile);
        return;
    }

    char line[256];
    int found = 0;
    int skip = 0; //preskakanje linija koje pripadaju vozacu za brisanje
    while (fgets(line, sizeof(line), file) != NULL) {
        int id;
        if (sscanf(line, "ID vozaca: %d", &id) == 1) {
            if (id == idZaBrisanje) {
                found = 1;
                skip = 1; // nadeni ID, zapocinje preskakanje
                continue;
            }
        }
        if (skip && strncmp(line, "\n", 1) == 0) {
            skip = 0; // kkraj podataka za vozaca, prestaje preskakanje
            continue;
        }
        if (!skip) {
            fputs(line, tempFile); // kopiraj liniju u privremenu datoteku
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Vozac sa ID %d nije pronaden.\n", idZaBrisanje);
        remove("temp_vozaci.txt"); // brise privremenu datoteku
    }
    else {
        remove("vozaci.txt"); // brise originalnu datoteku
        rename("temp_vozaci.txt", "vozaci.txt"); // preimenuje privremenu u originalnu
        printf("Vozac sa ID %d je obrisan.\n", idZaBrisanje);
    }
}

//fnkcija za sortiranje vozaca po godinama iskustva
void sortiraj_po_iskustvu() {
    FILE* file = fopen("vozaci.txt", "r");
    if (file == NULL) {
        perror("Greska pri otvaranju datoteke");
        exit(EXIT_FAILURE);
    }
    rewind(file);

    Vozac* vozaci = (Vozac*)malloc(10 * sizeof(Vozac));

    char line[256];
    int i = 0;

    while (i < 10) {
        if (fgets(line, sizeof(line), file) == NULL) break; // citanje linije "ID vozaca: X"
        sscanf(line, "ID vozaca: %d", &vozaci[i].id);

        if (fgets(line, sizeof(line), file) == NULL) break; 
        sscanf(line, "Ime vozaca: %s", vozaci[i].ime);

        if (fgets(line, sizeof(line), file) == NULL) break; 
        sscanf(line, "Prezime vozaca: %s", vozaci[i].prezime);

        if (fgets(line, sizeof(line), file) == NULL) break; 
        sscanf(line, "Broj vozacke dozvole: %s", vozaci[i].vozackaDozvola);

        if (fgets(line, sizeof(line), file) == NULL) break; 
        sscanf(line, "Godine iskustva: %d", &vozaci[i].godineIskustva);

        // Preskočite praznu liniju između zapisa vozača
        fgets(line, sizeof(line), file);

        i++;
    }

    fclose(file);

    int e, j;
    Vozac temp;
    for (e = 0; e < i - 1; e++) {
        for (j = 0; j < i - e - 1; j++) {
            if (vozaci[j].godineIskustva > vozaci[j + 1].godineIskustva) {
                temp = vozaci[j];
                vozaci[j] = vozaci[j + 1];
                vozaci[j + 1] = temp;
            }
        }
    }

    pisi_u_datoteku(vozaci, i);
}

void pisi_u_datoteku(Vozac* vozaci, const int broj_vozaca) {
    FILE* file = fopen("vozaci.txt", "w");
    if (file == NULL) {
        perror("Greska pri otvaranju datoteke");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < broj_vozaca; i++) {
        fprintf(file, "ID vozaca: %d\nIme vozaca: %s\nPrezime vozaca: %s\nBroj vozacke dozvole: %s\nGodine iskustva: %d\n\n",
            vozaci[i].id, vozaci[i].ime, vozaci[i].prezime,
            vozaci[i].vozackaDozvola, vozaci[i].godineIskustva);
    }

    fclose(file);
}


