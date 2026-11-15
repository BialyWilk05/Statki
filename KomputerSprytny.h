#pragma once
#include "Gracz.h"

class KomputerSprytny : public Gracz
{
public:
    KomputerSprytny(const string& imie = "Komputer (trudny)");
    Pole wybierzStrzal(const Plansza& przeciwnik) const override;
};
