////////////////////////////////////////////////////////////////////////////////
#include "Vehicles.hpp"
////////////////////////////////////////////////////////////////////////////////
// Library headers
////////////////////////////////////////////////////////////////////////////////
#include "Vehicles/Airplane.hpp"
#include "Vehicles/Automobile.hpp"
#include "Vehicles/Drone.hpp"
#include "Vehicles/Glider.hpp"
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Factory function templates
////////////////////////////////////////////////////////////////////////////////

template <typename Vehicle>
std::pair<IVehicle*, HRESULT>
CreateVehicle ()
{
    auto vehicle = new (std::nothrow) Vehicle;

    if (nullptr == vehicle)
    {
        return std::make_pair<IVehicle*, HRESULT> (std::move (vehicle), E_OUTOFMEMORY);
    }

    vehicle->AddRef ();

    return std::make_pair<IVehicle*, HRESULT> (std::move (vehicle), S_OK);
}

template <typename T>
inline HRESULT
CreateVehicle (IVehicle** vehicle)
{
    auto [ptr, result] = CreateVehicle<T> ();

    _ASSERTE (vehicle);
    *vehicle = ptr;

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// Factory functions - Aircraft
////////////////////////////////////////////////////////////////////////////////

// Airplane

std::pair<IVehicle*, HRESULT>
CreateAirplane ()
{
    return CreateVehicle<Airplane> ();
}

HRESULT
CreateAirplane (IVehicle** vehicle)
{
    return CreateVehicle<Airplane> (vehicle);
}

// Drone

std::pair<IVehicle*, HRESULT>
CreateDrone ()
{
    return CreateVehicle<Drone> ();
}

HRESULT
CreateDrone (IVehicle** vehicle)
{
    return CreateVehicle<Airplane> (vehicle);
}

// Glinder

std::pair<IVehicle*, HRESULT>
CreateGlider ()
{
    return CreateVehicle<Glider> ();
}

HRESULT
CreateGlider (IVehicle** vehicle)
{
    return CreateVehicle<Airplane> (vehicle);
}

////////////////////////////////////////////////////////////////////////////////
// Factory functions - Automobiles
////////////////////////////////////////////////////////////////////////////////

// Automobile

std::pair<IVehicle*, HRESULT>
CreateAutomobile ()
{
    return CreateVehicle<Automobile> ();
}

HRESULT
CreateAutomobile (IVehicle** vehicle)
{
    return CreateVehicle<Automobile> (vehicle);
}
