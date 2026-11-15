#include "Plansza.h"
#include "Wyjatki.h"
#include "StatkiPochodne.h"
#include <cstdlib>
#include <stdexcept>
using namespace std;

Plansza::Plansza() : siatka(ROZMIAR * ROZMIAR, StanPola::Puste)
{
}

int Plansza::indeks(const Pole& p) const
{
    return p.getWiersz() * ROZMIAR + p.getKolumna();
}

bool Plansza::czyWPlanszy(const Pole& p) const
{
    return p.getKolumna() >= 0 && p.getKolumna() < ROZMIAR &&
           p.getWiersz() >= 0 && p.getWiersz() < ROZMIAR;
}

StanPola Plansza::getStan(const Pole& p) const
{
    if (!czyWPlanszy(p))
        throw out_of_range("Pole poza plansza");
    return siatka[indeks(p)];
}

void Plansza::ustawStatek(unique_ptr<Statek> statek, const Pole& poczatek, bool poziomo)
{
    vector<Pole> pola;
    for (int i = 0; i < statek->rozmiar(); i++)
    {
        Pole p(poczatek.getKolumna() + (poziomo ? i : 0),
               poczatek.getWiersz() + (poziomo ? 0 : i));
        if (!czyWPlanszy(p))
            throw out_of_range("Statek wychodzi poza plansze");
        if (siatka[indeks(p)] != StanPola::Puste)
            throw PoleZajeteException();
        pola.push_back(p);
    }
    for (const Pole& p : pola)
        siatka[indeks(p)] = StanPola::Statek;
    statek->ustawPola(pola);
    statki.push_back(move(statek));
}

void Plansza::rozstawLosowo()
{
    // 1x czteromasztowiec, 2x trzymasztowiec, 3x dwumasztowiec, 4x jednomasztowiec
    for (int rozmiar = 4; rozmiar >= 1; rozmiar--)
    {
        int ile = 5 - rozmiar;
        for (int i = 0; i < ile; i++)
        {
            bool postawiony = false;
            while (!postawiony)
            {
                Pole start(rand() % ROZMIAR, rand() % ROZMIAR);
                bool poziomo = (rand() % 2 == 0);
                try
                {
                    ustawStatek(stworzStatek(rozmiar), start, poziomo);
                    postawiony = true;
                }
                catch (const out_of_range&)
                {
                }
                catch (const PoleZajeteException&)
                {
                }
            }
        }
    }
}

WynikStrzalu Plansza::strzal(const Pole& p)
{
    StanPola stan = getStan(p);
    if (stan == StanPola::Trafione || stan == StanPola::Pudlo)
        throw PoleOstrzelaneException();

    if (stan == StanPola::Puste)
    {
        siatka[indeks(p)] = StanPola::Pudlo;
        return WynikStrzalu::Pudlo;
    }

    siatka[indeks(p)] = StanPola::Trafione;
    for (auto& s : statki)
    {
        if (s->czyZajmuje(p))
        {
            s->przyjmijTrafienie(p);
            return s->czyZatopiony() ? WynikStrzalu::Zatopiony : WynikStrzalu::Trafiony;
        }
    }
    return WynikStrzalu::Trafiony;
}

bool Plansza::czyZatopionyStatekNaPolu(const Pole& p) const
{
    for (const auto& s : statki)
        if (s->czyZajmuje(p))
            return s->czyZatopiony();
    return false;
}

Pole Plansza::losoweNieostrzelanePole() const
{
    while (true)
    {
        Pole p(rand() % ROZMIAR, rand() % ROZMIAR);
        StanPola stan = siatka[indeks(p)];
        if (stan == StanPola::Puste || stan == StanPola::Statek)
            return p;
    }
}

bool Plansza::czyWszystkieZatopione() const
{
    for (const auto& s : statki)
        if (!s->czyZatopiony())
            return false;
    return true;
}

void Plansza::rysuj(ostream& os, bool pokazStatki) const
{
    os << "   ";
    for (int k = 0; k < ROZMIAR; k++)
        os << char('A' + k) << ' ';
    os << '\n';
    for (int w = 0; w < ROZMIAR; w++)
    {
        os << (w + 1 < 10 ? " " : "") << w + 1 << ' ';
        for (int k = 0; k < ROZMIAR; k++)
        {
            switch (siatka[w * ROZMIAR + k])
            {
                case StanPola::Puste:
                    os << '.';
                    break;
                case StanPola::Statek:
                    os << (pokazStatki ? 'S' : '.');
                    break;
                case StanPola::Trafione:
                    os << 'X';
                    break;
                case StanPola::Pudlo:
                    os << 'o';
                    break;
            }
            os << ' ';
        }
        os << '\n';
    }
}

ostream& operator<<(ostream& os, const Plansza& plansza)
{
    plansza.rysuj(os, true);
    return os;
}
