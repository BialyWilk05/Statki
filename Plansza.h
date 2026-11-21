#pragma once
#include <memory>
#include <ostream>
#include <vector>
using namespace std;
#include "Pole.h"
#include "Statek.h"

enum class WynikStrzalu
{
    Pudlo,
    Trafiony,
    Zatopiony
};

class Plansza
{
public:
    static const int ROZMIAR = 10;

private:
    vector<StanPola> siatka;
    vector<unique_ptr<Statek>> statki;
    int indeks(const Pole& p) const;
    bool czySasiadujeZeStatkiem(const Pole& p) const;

public:
    Plansza();
    bool czyWPlanszy(const Pole& p) const;
    StanPola getStan(const Pole& p) const;
    void ustawStatek(unique_ptr<Statek> statek, const Pole& poczatek, bool poziomo);
    void rozstawLosowo();
    WynikStrzalu strzal(const Pole& p);
    bool czyWszystkieZatopione() const;
    bool czyZatopionyStatekNaPolu(const Pole& p) const;
    Pole losoweNieostrzelanePole() const;
    void rysuj(ostream& os, bool pokazStatki) const;
};

ostream& operator<<(ostream& os, const Plansza& plansza);