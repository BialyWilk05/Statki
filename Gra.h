#pragma once
#include <memory>
#include "Gracz.h"
#include "Ustawienia.h"
using namespace std;

class Gra
{
private:
    unique_ptr<Gracz> gracz1; // czlowiek, zaczyna gre
    unique_ptr<Gracz> gracz2;
    TrybRozstawienia tryb;
    int liczbaRuchow; // strzaly gracza 1
    bool wygralGracz1;
    void wyswietlPlansze() const;

public:
    Gra(unique_ptr<Gracz> g1, unique_ptr<Gracz> g2, TrybRozstawienia tryb);
    void graj();
    int getLiczbaRuchow() const;
    bool czyWygralGracz1() const;
};
