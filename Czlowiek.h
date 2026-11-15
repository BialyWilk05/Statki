#pragma once
#include "Gracz.h"

class Czlowiek : public Gracz
{
public:
    Czlowiek(const string& imie = "Gracz");
    void rozstawFlote(TrybRozstawienia tryb) override;
    Pole wybierzStrzal(const Plansza& przeciwnik) const override;
};
