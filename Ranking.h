#pragma once
#include <ostream>
#include <string>
#include <vector>
#include "Wynik.h"
using namespace std;

class Ranking
{
private:
    vector<Wynik> wyniki;
    string sciezka;

public:
    Ranking(const string& sciezka = "ranking.txt");

    void dodaj(const Wynik& wynik);
    int usun(const string& imie); // zwraca liczbe usunietych wynikow
    vector<Wynik> wyszukaj(const string& imie) const;
    int zmienImie(const string& stare, const string& nowe);
    void sortuj();
    int rozmiar() const;

    void zapisz() const; // rzuca runtime_error, gdy nie mozna zapisac pliku
    void wczytaj();      // brak pliku = pusty ranking; uszkodzony plik = runtime_error

    friend ostream& operator<<(ostream& os, const Ranking& ranking);
};
