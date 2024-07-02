#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void ucitajKamione(int* brojKamiona, Kamion** kamioni) {
    FILE* file = fopen("kamioni.txt", "r");
    if (file == NULL) {
        perror("Ne moze se otvoriti datoteka kamioni.txt");
        return;
    }

    *brojKamiona = 0;
    *kamioni = (Kamion*)malloc(10 * sizeof(Kamion));
    if (*kamioni == NULL) {
        perror("Ne moze se alocirati memorija");
        fclose(file);
        return;
    }

    char line[256];

    while (*brojKamiona < 10) {
        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "ID: %d", &(*kamioni)[*brojKamiona].id) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "Registracija: %99s", (*kamioni)[*brojKamiona].registracija) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "Model: %99s", (*kamioni)[*brojKamiona].model) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "Godina Proizvodnje: %d", &(*kamioni)[*brojKamiona].godinaProizvodnje) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "Kilometraža: %d", &(*kamioni)[*brojKamiona].kilometraza) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "Stanje Goriva: %d", &(*kamioni)[*brojKamiona].stanjeGoriva) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;

        (*brojKamiona)++;
    }

    printf("Ucitano kamiona: %d\n", *brojKamiona);

    fclose(file);
}

void ucitajVozace(int* brojVozaca, Vozac** vozaci) {
    FILE* file = fopen("vozaci.txt", "r");
    if (file == NULL) {
        perror("Ne moze se otvoriti datoteka vozaci.txt");
        return;
    }

    *brojVozaca = 0;
    *vozaci = (Vozac*)malloc(10 * sizeof(Vozac));
    if (*vozaci == NULL) {
        perror("Ne moze se alocirati memorija");
        fclose(file);
        return;
    }

    char line[256];

    while (*brojVozaca < 10) {
        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "ID vozaca : %d", &(*vozaci)[*brojVozaca].id) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "Ime vozaca: %99s", (*vozaci)[*brojVozaca].ime) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "Prezime vozaca: %99s", (*vozaci)[*brojVozaca].prezime) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "Broj vozacke dozvole: %99s", (*vozaci)[*brojVozaca].vozackaDozvola) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "Godine iskustva: %d", &(*vozaci)[*brojVozaca].godineIskustva) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;

        (*brojVozaca)++;
    }

    printf("Ucitano vozaca: %d\n", *brojVozaca);

    fclose(file);
}

void ucitajRute(int* brojRuta, Ruta** rute) {
    FILE* file = fopen("rute.txt", "r");
    if (file == NULL) {
        perror("Ne moze se otvoriti datoteka rute.txt");
        return;
    }

    *brojRuta = 0;
    *rute = (Ruta*)malloc(10 * sizeof(Ruta));
    if (*rute == NULL) {
        perror("Ne moze se alocirati memorija");
        fclose(file);
        return;
    }

    char line[256];

    while (*brojRuta < 10) {
        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "ID rute: %d", &(*rute)[*brojRuta].id) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "ID kamiona: %d", &(*rute)[*brojRuta].idKamiona) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "ID vozaca: %d", &(*rute)[*brojRuta].idVozaca) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "Pocetna lokacija: %99s", (*rute)[*brojRuta].pocetnaLokacija) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "Krajnja lokacija: %99s", (*rute)[*brojRuta].krajnjaLokacija) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "Udaljenost: %f", &(*rute)[*brojRuta].udaljenost) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;
        if (sscanf(line, "Trajanje rute: %f", &(*rute)[*brojRuta].trajanje) != 1) break;

        if (fgets(line, sizeof(line), file) == NULL) break;

        (*brojRuta)++;
    }

    printf("Ucitano ruta: %d\n", *brojRuta);

    fclose(file);
}
//generiranje izvjestaja o kamionima, vozacima i rutama
void generirajIzvjestaj() {
    int brojKamiona = 0;
    int brojVozaca = 0;
    int brojRuta = 0;

    Kamion* kamioni = NULL;
    Vozac* vozaci = NULL;
    Ruta* rute = NULL;

    ucitajKamione(&brojKamiona, &kamioni);
    ucitajVozace(&brojVozaca, &vozaci);
    ucitajRute(&brojRuta, &rute);

    if (kamioni == NULL || vozaci == NULL || rute == NULL) {
        printf("Greska pri ucitavanju podataka.\n");
        free(kamioni);
        free(vozaci);
        free(rute);
        return;
    }

    FILE* file = fopen("izvjestaj.txt", "w");
    if (file == NULL) {
        perror("Ne moze se otvoriti datoteka za izvjestaj");
        free(kamioni);
        free(vozaci);
        free(rute);
        return;
    }

    fprintf(file, "===== Izvjestaj o Kamionima =====\n");
    for (int i = 0; i < brojKamiona; i++) {
        fprintf(file, "ID: %d\nRegistracija: %s\nModel: %s\nGodina proizvodnje: %d\nKilometraza: %d\nStanje goriva: %d\n\n",
            kamioni[i].id, kamioni[i].registracija, kamioni[i].model, kamioni[i].godinaProizvodnje,
            kamioni[i].kilometraza, kamioni[i].stanjeGoriva);
    }

    fprintf(file, "\n===== Izvjestaj o Vozacima =====\n");
    for (int i = 0; i < brojVozaca; i++) {
        fprintf(file, "ID: %d\nIme: %s\nPrezime: %s\nBroj vozacke dozvole: %s\nGodine iskustva: %d\n\n",
            vozaci[i].id, vozaci[i].ime, vozaci[i].prezime, vozaci[i].vozackaDozvola, vozaci[i].godineIskustva);
    }

    fprintf(file, "\n===== Izvjestaj o Rutama =====\n");
    for (int i = 0; i < brojRuta; i++) {
        fprintf(file, "ID: %d\nKamion ID: %d\nVozac ID: %d\nPocetna lokacija: %s\nKrajnja lokacija: %s\nUdaljenost: %.2f km\nTrajanje: %.2f sati\n\n",
            rute[i].id, rute[i].idKamiona, rute[i].idVozaca, rute[i].pocetnaLokacija, rute[i].krajnjaLokacija, rute[i].udaljenost, rute[i].trajanje);
    }

    fclose(file);
    free(kamioni);
    free(vozaci);
    free(rute);

    printf("Izvjestaj je uspjesno generiran u fajlu 'izvjestaj.txt'.\n");
}