#pragma once

////////////////////////////////////////////////////////////////////////////////
#include "Interfaces/IVehicle.hpp"
#include "Utilities/UDLiterals.hpp"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// COM Class
////////////////////////////////////////////////////////////////////////////////

class Airplane : public IAirplane, public IMotor, public IPassangerCabin
{
public:
    Airplane ();
    virtual ~Airplane ();

public:
    // IAircraft
    auto Wings () -> int final;

    // IAirplane
    void DisableAutopilot () final;
    void EnableAutopilot () final;
 
    // IMotor
    auto Power() -> int64_t final;

    // IPassangerCabin
    auto Passangers() -> int final;

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
    int passangers = 196;
    int64_t power = 10000_hp;
    int64_t speed = 500_kmh;
    int wings = 2;
};

////////////////////////////////////////////////////////////////////////////////
