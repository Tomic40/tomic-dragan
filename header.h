#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//enum
typedef enum {
    ADMINISTRATOR = 1,
    KORISNIK = 2,
    EXIT = 3
} IzbornikOpcijaMain;

typedef enum {
    DODAJ_KAMION = 1,
    DODAJ_VOZACA,
    PLANIRAJ_RUTU,
    GENERIRAJ_IZVJESTAJ,
    IZBRISI_KAMION,
    IZBRISI_VOZACA,
    IZBRISI_RUTU,
    SORTIRAJ_VOZACE,
    PRETRAZI_KAMIONE,
    BRISANJE_DATOTEKE_KAMIONA,
    ADMINISTRATORSKI_IZLAZ
} AdministratorskaOpcija;

typedef enum {
    DODAJ_KAMION_KORISNIK = 1,
    DODAJ_VOZACA_KORISNIK,
    PLANIRAJ_RUTU_KORISNIK,
    GENERIRAJ_IZVJESTAJ_KORISNIK,
    SORTIRAJ_VOZACE_KORISNIK,
    PRETRAZI_KAMIONE_KORISNIK,
    AZURIRAJ_KILOMETRAZU_KAMIONA,
    KORISNICKI_IZLAZ
} KorisnickaOpcija;

#define REG 20      //s ovim smo izbjegli VLA
#define MODEL 20
#define REGA 20

// definicija struktura koristeci typedef
typedef struct {
    int id;
    char registracija[REG];
    char trazenaRegistracija[REGA];
    char model[MODEL];
    int godinaProizvodnje;
    int kilometraza;
    int stanjeGoriva;
} Kamion;


#define IME 20
#define PREZIME 20
#define VOZACKA 20

typedef struct {
    int id;
    char ime[IME];
    char prezime[PREZIME];
    char vozackaDozvola[VOZACKA];
    int godineIskustva;
} Vozac;

#define P_LOKACIJA 50
#define K_LOKACIJA 50

typedef struct {
    int id;
    int idKamiona;
    int idVozaca;
    char pocetnaLokacija[P_LOKACIJA];
    char krajnjaLokacija[K_LOKACIJA];
    float udaljenost;
    float trajanje;
} Ruta;

//prijava
extern void prijavaAdministratora();
extern void prijavaKorisnika();

//Kamioni
extern void dodajKamione();
extern void obrisiKamion();
extern void pretraziKamionePoID();
inline extern void brisanjeDatotekeKamiona();
extern void azurirajKilometaraKamiona();

//vozaci
extern void dodajVozaca();
extern void brisiVozaca();
extern void sortiraj_po_iskustvu();
extern void pisi_u_datoteku(Vozac*, const int);

//rute
extern void dodajRutu();
extern void brisiRutu();

//generiranje izvjestaja
extern void generirajIzvjestaj();

#endif // HEADER_H

