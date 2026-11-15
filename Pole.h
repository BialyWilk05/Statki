#pragma once
#include <ostream>
#include <string>
using namespace std;

enum class StanPola
{
    Puste,
    Statek,
    Trafione,
    Pudlo
};

class Pole
{
private:
    int kolumna;
    int wiersz;

public:
    Pole(int k = 0, int w = 0);
    int getKolumna() const;
    int getWiersz() const;
    void setKolumna(int k);
    void setWiersz(int w);
    bool operator==(const Pole& inne) const;
    static Pole zTekstu(const string& tekst);
    friend ostream& operator<<(ostream& os, const Pole& p);
};
