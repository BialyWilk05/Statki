#pragma once
#include <ostream>
#include <string>
#include "Ustawienia.h"
using namespace std;

class Wynik
{
private:
    string imie;
    int liczbaRuchow;
    PoziomTrudnosci poziom;

public:
    Wynik(const string& imie = "", int liczbaRuchow = 0,
          PoziomTrudnosci poziom = PoziomTrudnosci::Latwy);

    string getImie() const;
    int getLiczbaRuchow() const;
    PoziomTrudnosci getPoziom() const;
    void setImie(const string& noweImie);

    // "a < b" oznacza, ze wynik a jest lepszy i w rankingu stoi wyzej
    bool operator<(const Wynik& inny) const;
    friend ostream& operator<<(ostream& os, const Wynik& w);
};
