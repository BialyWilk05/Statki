#pragma once
#include <string>
#include <vector>
using namespace std;
#include "Pole.h"

class Statek
{
protected:
    vector<Pole> pola;
    vector<bool> trafione;

public:
    virtual ~Statek() = default;
    virtual int rozmiar() const = 0;
    virtual string nazwa() const = 0;

    void ustawPola(const vector<Pole>& nowePola);
    const vector<Pole>& getPola() const;
    bool czyZajmuje(const Pole& p) const;
    bool przyjmijTrafienie(const Pole& p);
    bool czyZatopiony() const;
};
