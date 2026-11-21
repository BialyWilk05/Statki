#pragma once
#include <stdexcept>
#include <string>
using namespace std;

class PoleZajeteException : public runtime_error
{
public:
    PoleZajeteException(const string& komunikat = "Pole jest juz zajete przez inny statek")
        : runtime_error(komunikat)
    {
    }
};

class PoleOstrzelaneException : public runtime_error
{
public:
    PoleOstrzelaneException() : runtime_error("To pole zostalo juz ostrzelane")
    {
    }
};