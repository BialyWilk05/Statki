#include "Pole.h"
#include <algorithm>
#include <cctype>
#include <stdexcept>

Pole::Pole(int k, int w) : kolumna(k), wiersz(w)
{
}
int Pole::getKolumna() const
{
    return kolumna;
}
int Pole::getWiersz() const
{
    return wiersz;
}
void Pole::setKolumna(int k)
{
    kolumna = k;
}
void Pole::setWiersz(int w)
{
    wiersz = w;
}

bool Pole::operator==(const Pole& inne) const
{
    return kolumna == inne.kolumna && wiersz == inne.wiersz;
}

ostream& operator<<(ostream& os, const Pole& p)
{
    return os << char('A' + p.kolumna) << p.wiersz + 1;
}

Pole Pole::zTekstu(const string& tekst)
{
    if (tekst.size() < 2 || tekst.size() > 3 || !isalpha((unsigned char)tekst[0]))
        throw invalid_argument("Niepoprawny format pola (podaj np. C7)");
    string numer = tekst.substr(1);
    bool tylkoCyfry = all_of(numer.begin(), numer.end(),
                             [](unsigned char c)
                             {
                                 return isdigit(c) != 0;
                             });
    if (!tylkoCyfry)
        throw invalid_argument("Niepoprawny format pola (podaj np. C7)");
    int kolumna = toupper((unsigned char)tekst[0]) - 'A';
    int wiersz = stoi(numer) - 1;
    return Pole(kolumna, wiersz);
}
