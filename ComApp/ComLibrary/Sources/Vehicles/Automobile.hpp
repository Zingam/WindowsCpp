#pragma once

////////////////////////////////////////////////////////////////////////////////
#include "Interfaces/IVehicle.hpp"
#include "Utilities/UDLiterals.hpp"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// COM Class
////////////////////////////////////////////////////////////////////////////////

class Automobile : public IAutomobile, public IMotor, public IPassangerCabin
{
public:
    Automobile ();
    virtual ~Automobile ();

public:
    // IAutomobile
    void ShiftGear (int gear) final;
    auto Wheels () -> int final;

    // IMotor
    auto Power () -> int64_t final;

    // IPassangerCabin
    auto Passangers() -> int final;

    // IVehicle
    auto Speed () -> int64_t final;

    // IUnknown
    auto AddRef () -> unsigned long final;
    auto Release () -> unsigned long final;
    auto QueryInterface (IID const& id, void** result) -> HRESULT override;

public:
    void SwitchGear ();

private:
    // Reference counter
    long count = 0;

    // Properties
    int gear = 1;
    int passangers = 5;
    int64_t power = 100_hp;
    int64_t speed = 200_kmh;
    int wheels = 4;
};

////////////////////////////////////////////////////////////////////////////////
