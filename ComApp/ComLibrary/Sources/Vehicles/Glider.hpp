#pragma once

////////////////////////////////////////////////////////////////////////////////
#include "Interfaces/IVehicle.hpp"
#include "Utilities/UDLiterals.hpp"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// COM Class
////////////////////////////////////////////////////////////////////////////////

class Glider : public IGlider, public IPassangerCabin
{
public:
    Glider ();
    virtual ~Glider ();

public:
    // IAircraft
    auto Wings () -> int final;

    // IGlider
    void DropParachute () final;

    // IPassangerCabin
    auto Passangers () -> int final;

    // IVehicle
    auto Speed () -> int64_t final;

    // IUnknown
    auto AddRef () -> unsigned long final;
    auto Release () -> unsigned long final;
    auto QueryInterface (IID const & id, void ** result) -> HRESULT override;

private:
    // Reference counter
    long count = 0;

    // Properties
    int passangers = 2;
    int64_t speed = 200_kmh;
    int wings;
};

////////////////////////////////////////////////////////////////////////////////
