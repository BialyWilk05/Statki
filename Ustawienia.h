#pragma once
#include <string>
using namespace std;

enum class TrybRozstawienia
{
    Reczne,
    Losowe
};
enum class PoziomTrudnosci
{
    Latwy = 0,
    Trudny = 1
};

inline string nazwaPoziomu(PoziomTrudnosci poziom)
{
    return poziom == PoziomTrudnosci::Latwy ? "Latwy" : "Trudny";
}
