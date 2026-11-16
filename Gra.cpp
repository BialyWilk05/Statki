#include "Gra.h"
#include "Wyjatki.h"
#include <iostream>
#include <stdexcept>

Gra::Gra(unique_ptr<Gracz> g1, unique_ptr<Gracz> g2, TrybRozstawienia tryb)
    : gracz1(move(g1)), gracz2(move(g2)), tryb(tryb), liczbaRuchow(0), wygralGracz1(false)
{
}

int Gra::getLiczbaRuchow() const
{
    return liczbaRuchow;
}
bool Gra::czyWygralGracz1() const
{
    return wygralGracz1;
}

void Gra::wyswietlPlansze() const
{
    cout << "\n--- Twoja plansza ---\n";
    gracz1->getPlansza().rysuj(cout, true);
    cout << "\n--- Plansza wroga ---\n";
    gracz2->getPlansza().rysuj(cout, false);
}

void Gra::graj()
{
    gracz1->rozstawFlote(tryb);
    gracz2->rozstawFlote(tryb);

    Gracz* aktualny = gracz1.get();
    Gracz* przeciwnik = gracz2.get();

    while (true)
    {
        wyswietlPlansze();

        Pole pole;
        WynikStrzalu wynik = WynikStrzalu::Pudlo;
        bool poprawnyStrzal = false;
        while (!poprawnyStrzal)
        {
            try
            {
                pole = aktualny->wybierzStrzal(przeciwnik->getPlansza());
                wynik = przeciwnik->getPlansza().strzal(pole);
                poprawnyStrzal = true;
            }
            catch (const logic_error& e) // invalid_argument, out_of_range
            {
                cout << "Blad: " << e.what() << endl;
            }
            catch (const PoleOstrzelaneException& e)
            {
                cout << "Blad: " << e.what() << endl;
            }
        }

        if (aktualny == gracz1.get())
            liczbaRuchow++;

        cout << aktualny->getImie() << " strzela w " << pole << ": ";
        switch (wynik)
        {
            case WynikStrzalu::Pudlo:
                cout << "pudlo" << endl;
                break;
            case WynikStrzalu::Trafiony:
                cout << "trafiony!" << endl;
                break;
            case WynikStrzalu::Zatopiony:
                cout << "trafiony zatopiony!" << endl;
                break;
        }

        if (przeciwnik->getPlansza().czyWszystkieZatopione())
        {
            wygralGracz1 = (aktualny == gracz1.get());
            cout << "\nWygrywa " << aktualny->getImie() << "!" << endl;
            wyswietlPlansze();
            break;
        }

        if (wynik == WynikStrzalu::Pudlo) // po trafieniu strzela ponownie
            swap(aktualny, przeciwnik);
    }
}
