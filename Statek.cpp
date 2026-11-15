#include "Statek.h"

void Statek::ustawPola(const vector<Pole>& nowePola)
{
    pola = nowePola;
    trafione.assign(pola.size(), false);
}

const vector<Pole>& Statek::getPola() const
{
    return pola;
}

bool Statek::czyZajmuje(const Pole& p) const
{
    for (const Pole& pole : pola)
        if (pole == p)
            return true;
    return false;
}

bool Statek::przyjmijTrafienie(const Pole& p)
{
    for (size_t i = 0; i < pola.size(); i++)
    {
        if (pola[i] == p)
        {
            trafione[i] = true;
            return true;
        }
    }
    return false;
}

bool Statek::czyZatopiony() const
{
    if (trafione.empty())
        return false;
    for (bool t : trafione)
        if (!t)
            return false;
    return true;
}
