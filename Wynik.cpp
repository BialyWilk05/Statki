#include "Wynik.h"

Wynik::Wynik(const string& imie, int liczbaRuchow, PoziomTrudnosci poziom)
    : imie(imie), liczbaRuchow(liczbaRuchow), poziom(poziom)
{
}

string Wynik::getImie() const
{
    return imie;
}
int Wynik::getLiczbaRuchow() const
{
    return liczbaRuchow;
}
PoziomTrudnosci Wynik::getPoziom() const
{
    return poziom;
}
void Wynik::setImie(const string& noweImie)
{
    imie = noweImie;
}

bool Wynik::operator<(const Wynik& inny) const
{
    if (poziom != inny.poziom)
        return static_cast<int>(poziom) > static_cast<int>(inny.poziom); // trudniejszy wyzej
    if (liczbaRuchow != inny.liczbaRuchow)
        return liczbaRuchow < inny.liczbaRuchow; // mniej ruchow = lepiej
    return imie < inny.imie;
}

ostream& operator<<(ostream& os, const Wynik& w)
{
    return os << w.imie << " - " << w.liczbaRuchow << " ruchow (" << nazwaPoziomu(w.poziom) << ")";
}
