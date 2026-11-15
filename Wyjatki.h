#pragma once
#include <stdexcept>
using namespace std;

class PoleZajeteException : public runtime_error
{
public:
    PoleZajeteException() : runtime_error("Pole jest juz zajete przez inny statek")
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
