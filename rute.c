#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void dodajRutu() {
    FILE* file = fopen("rute.txt", "a+");
    if (file == NULL) {
        perror("Ne moze se otvoriti datoteka za rute");
        exit(1);
    }

    Ruta* novaRuta = (Ruta*)malloc(sizeof(Ruta));
    if (novaRuta == NULL) {
        perror("Ne moze se alocirati memorija za novou rutu");
        fclose(file);
        exit(1);
    }
    printf("Unesite ID: ");
    if (scanf("%d", &novaRuta->id) != 1) {
        printf("Neispravan unos ID-a.\n");
        fclose(file);
        free(novaRuta);
        return 1;
    }

    // Provjera da li ID već postoji
    fseek(file, 0, SEEK_SET); // Premjesti pokazivač na početak datoteke
    char line[256]; // Pretpostavka: linija neće biti dulja od 255 znakova
    int idPostojeci = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        int id;
        if (sscanf(line, "ID vozaca: %d", &id) == 1) {
            if (id == novaRuta->id) {
                idPostojeci = 1;
                break;
            }
        }
    }

    if (idPostojeci) {
        printf("Ruta sa ID %d vec postoji.\n", novaRuta->id);
        fclose(file);
        free(novaRuta);
        return 1;
    }

    printf("Unesite ID kamiona: ");
    if (scanf("%d", &novaRuta->idKamiona) != 1) {
        fclose(file);
        free(novaRuta);
        return 1;
    }

    printf("Unesite ID vozaca: ");
    if (scanf("%d", &novaRuta->idVozaca) != 1) {
        fclose(file);
        free(novaRuta);
        return 1;
    }


    printf("Unesite pocetnu lokaciju: ");
    if (scanf("%s", novaRuta->pocetnaLokacija) != 1) {
        fclose(file);
        free(novaRuta);
        return 1;
    }


    printf("Unesite krajnju lokaciju: ");
    if (scanf("%s", novaRuta->krajnjaLokacija) != 1) {
        fclose(file);
        free(novaRuta);
        return 1;
    }


    printf("Unesite udaljenost u km: ");
    if (scanf("%f", &novaRuta->udaljenost) != 1) {
        fclose(file);
        free(novaRuta);
        return 1;
    }

    printf("Unesite trajanje rute u h: ");
    if (scanf("%f", &novaRuta->trajanje) != 1) {
        fclose(file);
        free(novaRuta);
        return 1;
    }

   // fseek(file, 0, SEEK_END);
    fprintf(file, "ID rute: %d\nID kamiona: %d\nID vozaca: %d\nPocetna lokacija: %s\nKrajnja lokacija: %s\nUdaljenost: %.2f km\nTrajanje rute: %.2f h\n\n", novaRuta->id, novaRuta->idKamiona, novaRuta->idVozaca, novaRuta->pocetnaLokacija, novaRuta->krajnjaLokacija, novaRuta->udaljenost, novaRuta->trajanje);

    fclose(file);
    free(novaRuta);

    printf("Ruta uspjesno dodana.\n\n");

    return 0;
}

void brisiRutu() {
    FILE* file = fopen("rute.txt", "r");
    if (file == NULL) {
        perror("Ne moze se otvoriti datoteka za vozace");
        exit(1);
    }

    FILE* tempFile = fopen("temp_rute.txt", "w");
    if (tempFile == NULL) {
        perror("Ne moze se otvoriti privremena datoteka");
        fclose(file);
        exit(1);
    }

    int idZaBrisanje2;
    printf("Unesite ID rute koju zelite obrisati: ");
    if (scanf("%d", &idZaBrisanje2) != 1) {
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
        if (sscanf(line, "ID rute: %d", &id) == 1) {
            if (id == idZaBrisanje2) {
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
        printf("Ruta sa ID %d nije pronadena.\n", idZaBrisanje2);
        remove("temp_rute.txt"); // brise privremenu datoteku
    }
    else {
        remove("rute.txt"); // brise originalnu datoteku
        rename("temp_rute.txt", "rute.txt"); // preimenuje privremenu u originalnu
        printf("Ruta sa ID %d je obrisana.\n", idZaBrisanje2);
    }
}
