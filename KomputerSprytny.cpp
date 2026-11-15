#include "KomputerSprytny.h"
#include <cstdlib>
#include <vector>

static bool czyNieostrzelane(const Plansza& plansza, const Pole& p)
{
    StanPola stan = plansza.getStan(p);
    return stan == StanPola::Puste || stan == StanPola::Statek;
}

static bool czyTrafionyNiezatopiony(const Plansza& plansza, const Pole& p)
{
    return plansza.czyWPlanszy(p) &&
           plansza.getStan(p) == StanPola::Trafione &&
           !plansza.czyZatopionyStatekNaPolu(p);
}

KomputerSprytny::KomputerSprytny(const string& imie) : Gracz(imie)
{
}

Pole KomputerSprytny::wybierzStrzal(const Plansza& przeciwnik) const
{
    const int dk[4] = {1, -1, 0, 0};
    const int dw[4] = {0, 0, 1, -1};

    vector<Pole> priorytetowe; // dalszy ciag linii co najmniej dwoch trafien
    vector<Pole> zwykle;       // sasiedzi pojedynczego trafienia

    for (int w = 0; w < Plansza::ROZMIAR; w++)
    {
        for (int k = 0; k < Plansza::ROZMIAR; k++)
        {
            Pole p(k, w);
            if (!czyTrafionyNiezatopiony(przeciwnik, p))
                continue;
            for (int d = 0; d < 4; d++)
            {
                Pole cel(k + dk[d], w + dw[d]);
                if (!przeciwnik.czyWPlanszy(cel) || !czyNieostrzelane(przeciwnik, cel))
                    continue;
                Pole wstecz(k - dk[d], w - dw[d]);
                if (czyTrafionyNiezatopiony(przeciwnik, wstecz))
                    priorytetowe.push_back(cel);
                else
                    zwykle.push_back(cel);
            }
        }
    }

    if (!priorytetowe.empty())
        return priorytetowe[rand() % priorytetowe.size()];
    if (!zwykle.empty())
        return zwykle[rand() % zwykle.size()];
    return przeciwnik.losoweNieostrzelanePole(); // brak trafien do dobicia
}
