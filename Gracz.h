#pragma once
#include <string>
#include "Plansza.h"
#include "Ustawienia.h"
using namespace std;

class Gracz
{
protected:
    string imie;
    Plansza plansza;

public:
    Gracz(const string& imie = "Gracz");
    virtual ~Gracz() = default;

    string getImie() const;
    void setImie(const string& noweImie);
    Plansza& getPlansza();
    const Plansza& getPlansza() const;

    // domyslnie (komputer) flota zawsze rozstawiana losowo
    virtual void rozstawFlote(TrybRozstawienia tryb);
    virtual Pole wybierzStrzal(const Plansza& przeciwnik) const = 0;
};
