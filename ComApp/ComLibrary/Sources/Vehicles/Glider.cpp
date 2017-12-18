////////////////////////////////////////////////////////////////////////////////
#include "Glider.hpp"
////////////////////////////////////////////////////////////////////////////////
// Windows system headers
////////////////////////////////////////////////////////////////////////////////
#include <crtdbg.h>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// class Glider
////////////////////////////////////////////////////////////////////////////////

// Constructors and destructors

Glider::Glider ()
{
    OutputDebugString ("Object of class 'Glider' created\n");
}

Glider::~Glider ()
{
    OutputDebugString ("Object of class 'Glider' destroyed\n");
}

// Inherited methods - IAircraft

int
Glider::Wings ()
{
    return this->wings;
}

// Inherited methods - IGlider

void
Glider:: DropParachute ()
{
    OutputDebugString ("Glider: Dropped a parachute\n");
}

// Inherited methods - IPassangerCabin

int
Glider::Passangers ()
{
    return this->passangers;
}

// Inherited methods - IVehicle

int64_t
Glider::Speed ()
{
    return this->speed;
}

// Inherited methods - IUnknown

unsigned long 
Glider::AddRef ()
{
    return _InterlockedIncrement (&this->count);
}

unsigned long 
Glider::Release ()
{
    auto result = _InterlockedDecrement (&this->count);

    if (0 == result)
    {
        delete this;
    }

    return result;
}

HRESULT 
Glider::QueryInterface (IID const& id, void** result)
{
    _ASSERTE (result);

    if ((id == __uuidof (IAircraft))
        || (id == __uuidof (IVehicle))
        || (id == __uuidof (IUnknown)))
    {
        *result = static_cast<IAircraft*> (this);
    }
    if (id == __uuidof (IPassangerCabin))
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
