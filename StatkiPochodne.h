#pragma once
#include <memory>
#include "Statek.h"

class Jednomasztowiec : public Statek
{
public:
    int rozmiar() const override;
    string nazwa() const override;
};

class Dwumasztowiec : public Statek
{
public:
    int rozmiar() const override;
    string nazwa() const override;
};

class Trzymasztowiec : public Statek
{
public:
    int rozmiar() const override;
    string nazwa() const override;
};

class Czteromasztowiec : public Statek
{
public:
    int rozmiar() const override;
    string nazwa() const override;
};

unique_ptr<Statek> stworzStatek(int rozmiar);
