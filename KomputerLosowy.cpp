#include "KomputerLosowy.h"

KomputerLosowy::KomputerLosowy(const string& imie) : Gracz(imie)
{
}

Pole KomputerLosowy::wybierzStrzal(const Plansza& przeciwnik) const
{
    return przeciwnik.losoweNieostrzelanePole();
}
