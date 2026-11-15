#include "Czlowiek.h"
#include "StatkiPochodne.h"
#include "Wyjatki.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>

Czlowiek::Czlowiek(const string& imie) : Gracz(imie)
{
}

void Czlowiek::rozstawFlote(TrybRozstawienia tryb)
{
    if (tryb == TrybRozstawienia::Losowe)
    {
        Gracz::rozstawFlote(tryb);
        return;
    }

    cout << "\nRozstawianie floty. Podaj pole startowe i kierunek: H (poziomo) lub V (pionowo),\n";
    cout << "np. B3 H. Dla jednomasztowca wystarczy samo pole.\n";

    for (int rozmiar = 4; rozmiar >= 1; rozmiar--)
    {
        int ile = 5 - rozmiar;
        for (int i = 1; i <= ile; i++)
        {
            bool postawiony = false;
            while (!postawiony)
            {
                unique_ptr<Statek> statek = stworzStatek(rozmiar);
                cout << "\n";
                plansza.rysuj(cout, true);
                cout << "Ustaw " << statek->nazwa() << " (rozmiar " << rozmiar
                     << ") [" << i << "/" << ile << "]: ";

                string linia;
                if (!getline(cin >> ws, linia))
                    throw runtime_error("Koniec wejscia");
                istringstream wejscie(linia);
                string tekstPola, tekstKierunku;
                wejscie >> tekstPola >> tekstKierunku;

                try
                {
                    bool poziomo = true;
                    if (rozmiar > 1)
                    {
                        if (tekstKierunku.size() != 1)
                            throw invalid_argument("Podaj kierunek: H (poziomo) lub V (pionowo)");
                        char kierunek = toupper(static_cast<unsigned char>(tekstKierunku[0]));
                        if (kierunek == 'H')
                            poziomo = true;
                        else if (kierunek == 'V')
                            poziomo = false;
                        else
                            throw invalid_argument("Kierunek to H (poziomo) lub V (pionowo)");
                    }
                    Pole start = Pole::zTekstu(tekstPola);
                    plansza.ustawStatek(move(statek), start, poziomo);
                    postawiony = true;
                }
                catch (const logic_error& e) // invalid_argument, out_of_range
                {
                    cout << "Blad: " << e.what() << endl;
                }
                catch (const PoleZajeteException& e)
                {
                    cout << "Blad: " << e.what() << endl;
                }
            }
        }
    }

    cout << "\nFlota rozstawiona:\n";
    plansza.rysuj(cout, true);
}

Pole Czlowiek::wybierzStrzal(const Plansza& przeciwnik) const
{
    while (true)
    {
        cout << imie << ", podaj pole do strzalu: ";
        string tekst;
        if (!(cin >> tekst))
            throw runtime_error("Koniec wejscia");

        // opcja testowa: "podglad" pokazuje statki przeciwnika (nie liczy sie jako ruch)
        string male = tekst;
        transform(male.begin(), male.end(), male.begin(),
                  [](unsigned char c)
                  {
                      return static_cast<char>(tolower(c));
                  });
        if (male == "podglad")
        {
            cout << "\n--- PODGLAD: plansza wroga ---\n";
            przeciwnik.rysuj(cout, true);
            cout << endl;
            continue;
        }

        return Pole::zTekstu(tekst);
    }
}
