#include "Ranking.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

Ranking::Ranking(const string& sciezka) : sciezka(sciezka)
{
}

void Ranking::dodaj(const Wynik& wynik)
{
    wyniki.push_back(wynik);
}

int Ranking::usun(const string& imie)
{
    size_t przed = wyniki.size();
    wyniki.erase(remove_if(wyniki.begin(), wyniki.end(),
                           [&](const Wynik& w)
                           {
                               return w.getImie() == imie;
                           }),
                 wyniki.end());
    return static_cast<int>(przed - wyniki.size());
}

vector<Wynik> Ranking::wyszukaj(const string& imie) const
{
    vector<Wynik> znalezione;
    for (const Wynik& w : wyniki)
        if (w.getImie() == imie)
            znalezione.push_back(w);
    return znalezione;
}

int Ranking::zmienImie(const string& stare, const string& nowe)
{
    int zmienione = 0;
    for (Wynik& w : wyniki)
    {
        if (w.getImie() == stare)
        {
            w.setImie(nowe);
            zmienione++;
        }
    }
    sortuj();
    return zmienione;
}

void Ranking::sortuj()
{
    sort(wyniki.begin(), wyniki.end()); // uzywa Wynik::operator<
}

int Ranking::rozmiar() const
{
    return static_cast<int>(wyniki.size());
}

void Ranking::zapisz() const
{
    ofstream plik(sciezka);
    if (!plik.is_open())
        throw runtime_error("Nie mozna zapisac pliku rankingu: " + sciezka);
    for (const Wynik& w : wyniki)
        plik << w.getImie() << ' ' << w.getLiczbaRuchow() << ' '
             << static_cast<int>(w.getPoziom()) << '\n';
}

void Ranking::wczytaj()
{
    ifstream plik(sciezka);
    if (!plik.is_open())
        return; // pierwszy start: ranking jeszcze nie istnieje

    vector<Wynik> wczytane;
    string linia;
    while (getline(plik, linia))
    {
        if (linia.empty())
            continue;
        istringstream wejscie(linia);
        string imie;
        int ruchy, poziom;
        if (!(wejscie >> imie >> ruchy >> poziom) || ruchy < 0 || poziom < 0 || poziom > 1)
            throw runtime_error("Uszkodzony plik rankingu: " + sciezka);
        wczytane.push_back(Wynik(imie, ruchy, static_cast<PoziomTrudnosci>(poziom)));
    }
    wyniki = wczytane;
    sortuj();
}

ostream& operator<<(ostream& os, const Ranking& ranking)
{
    if (ranking.wyniki.empty())
        return os << "Ranking jest pusty\n";
    for (size_t i = 0; i < ranking.wyniki.size(); i++)
        os << i + 1 << ". " << ranking.wyniki[i] << '\n';
    return os;
}
