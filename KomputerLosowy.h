#pragma once
#include "Gracz.h"

class KomputerLosowy : public Gracz
{
public:
    KomputerLosowy(const string& imie = "Komputer");
    Pole wybierzStrzal(const Plansza& przeciwnik) const override;
};
