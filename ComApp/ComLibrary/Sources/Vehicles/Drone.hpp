#pragma once

////////////////////////////////////////////////////////////////////////////////
#include "Interfaces/IVehicle.hpp"
#include "Utilities/UDLiterals.hpp"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// COM Classes
////////////////////////////////////////////////////////////////////////////////

class Drone : public IDrone, public IMotor
{
public:
    Drone ();
    virtual ~Drone ();

public:
    // IAircraft
    auto Wings () -> int final;

    // IDrone
    void TakePhoto () final;

    // IMotor
    auto Power () -> int64_t final;

    // IVehicle
    auto Speed () -> int64_t final;

    // IUnknown
    auto AddRef () -> unsigned long final;
    auto Release () -> unsigned long final;
    auto QueryInterface (IID const& id, void** result) -> HRESULT override;

private:
    // Reference counter
    long count = 0;

    // Properties
    int64_t power = 50_hp;
    int64_t speed = 250_kmh;
    int wings = 2;
};

////////////////////////////////////////////////////////////////////////////////
