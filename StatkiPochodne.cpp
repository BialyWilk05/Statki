#include "StatkiPochodne.h"

int Jednomasztowiec::rozmiar() const
{
    return 1;
}
string Jednomasztowiec::nazwa() const
{
    return "Jednomasztowiec";
}

int Dwumasztowiec::rozmiar() const
{
    return 2;
}
string Dwumasztowiec::nazwa() const
{
    return "Dwumasztowiec";
}

int Trzymasztowiec::rozmiar() const
{
    return 3;
}
string Trzymasztowiec::nazwa() const
{
    return "Trzymasztowiec";
}

int Czteromasztowiec::rozmiar() const
{
    return 4;
}
string Czteromasztowiec::nazwa() const
{
    return "Czteromasztowiec";
}

unique_ptr<Statek> stworzStatek(int rozmiar)
{
    switch (rozmiar)
    {
        case 1:
            return make_unique<Jednomasztowiec>();
        case 2:
            return make_unique<Dwumasztowiec>();
        case 3:
            return make_unique<Trzymasztowiec>();
        default:
            return make_unique<Czteromasztowiec>();
    }
}
