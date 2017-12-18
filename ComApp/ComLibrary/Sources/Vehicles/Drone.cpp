////////////////////////////////////////////////////////////////////////////////
#include "Drone.hpp"
////////////////////////////////////////////////////////////////////////////////
// Windows system headers
////////////////////////////////////////////////////////////////////////////////
#include <crtdbg.h>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// class Drone
////////////////////////////////////////////////////////////////////////////////

// Constructors and destructors

Drone::Drone ()
{
    OutputDebugString ("Object of class 'Drone' created\n");
}

Drone::~Drone ()
{
    OutputDebugString ("Object of class 'Drone' destroyed\n");
}

// Inherited methods - IAircraft

int
Drone::Wings ()
{
    return this->wings;
}

// Inherited methods - IDrone

void
Drone::TakePhoto ()
{
    OutputDebugString ("Drone: Photo taken\n");
}

// Inherited methods - IMotor

int64_t
Drone::Power ()
{
    return this->power;
}

// Inherited methods - IVehicle

int64_t
Drone::Speed ()
{
    return this->speed;
}

// Inherited methods - IUnknown

unsigned long 
Drone::AddRef ()
{
    return _InterlockedIncrement (&this->count);
}

unsigned long 
Drone::Release ()
{
    auto result = _InterlockedDecrement (&this->count);

    if (0 == result)
    {
        delete this;
    }

    return result;
}

HRESULT 
Drone::QueryInterface (IID const& id, void** result)
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
    else
    {
        *result = 0;

        return E_NOINTERFACE;
    }

    static_cast<IUnknown*> (*result)->AddRef ();

    return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
