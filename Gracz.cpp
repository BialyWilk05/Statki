#include "Gracz.h"

Gracz::Gracz(const string& imie) : imie(imie)
{
}
string Gracz::getImie() const
{
    return imie;
}
void Gracz::setImie(const string& noweImie)
{
    imie = noweImie;
}
Plansza& Gracz::getPlansza()
{
    return plansza;
}
const Plansza& Gracz::getPlansza() const
{
    return plansza;
}

void Gracz::rozstawFlote(TrybRozstawienia /*tryb*/)
{
    plansza.rozstawLosowo();
}
