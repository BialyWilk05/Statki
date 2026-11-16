#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include "Gra.h"
#include "Czlowiek.h"
#include "KomputerLosowy.h"
#include "KomputerSprytny.h"
#include "Ranking.h"
#include "Ustawienia.h"
using namespace std;

int wczytajWybor()
{
    int wybor;
    while (!(cin >> wybor))
    {
        if (cin.eof())
            throw runtime_error("Koniec wejscia");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Podaj liczbe: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return wybor;
}

void zapiszRanking(const Ranking& ranking)
{
    try
    {
        ranking.zapisz();
    }
    catch (const runtime_error& e)
    {
        cout << "Uwaga: " << e.what() << endl;
    }
}

void nowaGra(Ranking& ranking)
{
    string imie;
    cout << "Podaj imie: ";
    cin >> imie;

    cout << "\nRozstawienie statkow:\n";
    cout << "1. Reczne\n";
    cout << "2. Losowe\n";
    cout << "Wybor: ";
    int wyborTrybu = wczytajWybor();
    TrybRozstawienia tryb = (wyborTrybu == 1) ? TrybRozstawienia::Reczne
                                              : TrybRozstawienia::Losowe;

    cout << "\nPoziom trudnosci:\n";
    cout << "1. Latwy\n";
    cout << "2. Trudny\n";
    cout << "Wybor: ";
    int wyborPoziomu = wczytajWybor();
    PoziomTrudnosci poziom = (wyborPoziomu == 2) ? PoziomTrudnosci::Trudny
                                                 : PoziomTrudnosci::Latwy;

    unique_ptr<Gracz> przeciwnik;
    if (poziom == PoziomTrudnosci::Trudny)
        przeciwnik = make_unique<KomputerSprytny>();
    else
        przeciwnik = make_unique<KomputerLosowy>();

    Gra gra(make_unique<Czlowiek>(imie), move(przeciwnik), tryb);
    gra.graj();

    if (gra.czyWygralGracz1())
    {
        ranking.dodaj(Wynik(imie, gra.getLiczbaRuchow(), poziom));
        ranking.sortuj();
        zapiszRanking(ranking);
        cout << "Twoj wynik zapisano w rankingu: " << gra.getLiczbaRuchow()
             << " ruchow (" << nazwaPoziomu(poziom) << ")" << endl;
    }
}

void menuRanking(Ranking& ranking)
{
    int wybor = 0;
    do
    {
        cout << "\n=== RANKING ===\n";
        cout << "1. Pokaz ranking\n";
        cout << "2. Szukaj gracza\n";
        cout << "3. Usun gracza\n";
        cout << "4. Zmien imie gracza\n";
        cout << "5. Powrot\n";
        cout << "Wybor: ";
        wybor = wczytajWybor();

        switch (wybor)
        {
            case 1:
                cout << "\n"
                     << ranking;
                break;
            case 2:
            {
                string imie;
                cout << "Podaj imie: ";
                cin >> imie;
                vector<Wynik> znalezione = ranking.wyszukaj(imie);
                if (znalezione.empty())
                    cout << "Brak wynikow gracza " << imie << endl;
                for (const Wynik& w : znalezione)
                    cout << w << endl;
                break;
            }
            case 3:
            {
                string imie;
                cout << "Podaj imie: ";
                cin >> imie;
                int usuniete = ranking.usun(imie);
                cout << "Usunieto wynikow: " << usuniete << endl;
                if (usuniete > 0)
                    zapiszRanking(ranking);
                break;
            }
            case 4:
            {
                string stare, nowe;
                cout << "Obecne imie: ";
                cin >> stare;
                cout << "Nowe imie: ";
                cin >> nowe;
                int zmienione = ranking.zmienImie(stare, nowe);
                cout << "Zmieniono wynikow: " << zmienione << endl;
                if (zmienione > 0)
                    zapiszRanking(ranking);
                break;
            }
            case 5:
                break;
            default:
                cout << "Niepoprawny wybor" << endl;
        }
    } while (wybor != 5);
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    Ranking ranking("ranking.txt");
    try
    {
        ranking.wczytaj();
    }
    catch (const runtime_error& e)
    {
        cout << "Uwaga: " << e.what() << " (ranking zostanie pusty)" << endl;
    }

    try
    {
        int wybor = 0;
        do
        {
            cout << "\n=== BITWA MORSKA ===\n";
            cout << "1. Nowa gra\n";
            cout << "2. Ranking\n";
            cout << "3. Wyjscie\n";
            cout << "Wybor: ";
            wybor = wczytajWybor();

            switch (wybor)
            {
                case 1:
                    nowaGra(ranking);
                    break;
                case 2:
                    menuRanking(ranking);
                    break;
                case 3:
                    cout << "Do widzenia!" << endl;
                    break;
                default:
                    cout << "Niepoprawny wybor" << endl;
            }
        } while (wybor != 3);
    }
    catch (const runtime_error& e)
    {
        cout << "\nPrzerwano: " << e.what() << endl;
    }

    return 0;
}
