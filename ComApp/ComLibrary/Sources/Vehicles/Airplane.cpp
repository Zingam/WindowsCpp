////////////////////////////////////////////////////////////////////////////////
#include "Airplane.hpp"
////////////////////////////////////////////////////////////////////////////////
// Windows system headers
////////////////////////////////////////////////////////////////////////////////
#include "crtdbg.h"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// class Airplane
////////////////////////////////////////////////////////////////////////////////

// Constructors and destructors

Airplane::Airplane ()
{
    OutputDebugString ("Object of class 'Airplane' created\n");
}

Airplane::~Airplane ()
{
    OutputDebugString ("Object of class 'Airplane' destroyed\n");
}

// Inherited methods - IAircraft

int Airplane::Wings ()
{
    return this->wings;
}

// Inherited methods - IAirplane

void Airplane::DisableAutopilot ()
{
    OutputDebugString ("Airplane: Autopilot disabled\n");
}

void Airplane::EnableAutopilot ()
{
    OutputDebugString ("Airplane: Autopilot enabled\n");
}

// Inherited methods - IMotor

int64_t
Airplane::Power ()
{
    return this->power;
}

// Inherited methods - IPassangerCabin
int
Airplane::Passangers ()
{
    return this->passangers;
}

// Inherited methods - IVehicle

int64_t
Airplane::Speed ()
{
    return this->speed;
}

//  Inherited methods - IUnknown

unsigned long 
Airplane::AddRef ()
{
    return _InterlockedIncrement (&this->count);
}

unsigned long
Airplane::Release ()
{
    auto result = _InterlockedDecrement (&this->count);

    if (0 == result)
    {
        delete this;
    }

    return result;
}

HRESULT 
Airplane::QueryInterface (IID const& id, void** result)
{
    _ASSERTE (result);

    if ((id == __uuidof (IAircraft))
        || (id == __uuidof (IVehicle))
        || (id == __uuidof (IUnknown)))
    {
        *result = static_cast<IAircraft*> (this);
    }
    else if (id == __uuidof (IMotor))
    {
        *result = static_cast<IMotor*> (this);
    }
    else if (id == __uuidof (IPassangerCabin))
    {
        *result = static_cast<IPassangerCabin*> (this);
    }
    else
    {
        *result = 0;

        return E_NOINTERFACE;
    }

    static_cast<IUnknown*> (*result)->AddRef ();

    return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
