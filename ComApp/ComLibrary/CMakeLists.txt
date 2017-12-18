cmake_minimum_required (VERSION 3.9)

if (NOT "${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
  message (FATAL_ERROR "===> ERROR: 64bit architectures are supported only")
endif ()

add_library ("ComLibrary"
  "Sources/Interfaces/IVehicle.cpp"
  "Sources/Interfaces/IVehicle.hpp"
  "Sources/Utilities/ComPtr.cpp"
  "Sources/Utilities/ComPtr.hpp"
  "Sources/Utilities/ComPtr.hpp"
  "Sources/Utilities/UDLiterals.cpp"
  "Sources/Utilities/UDLiterals.hpp"
  "Sources/Vehicles/Airplane.cpp"
  "Sources/Vehicles/Airplane.hpp"
  "Sources/Vehicles/Automobile.cpp"
  "Sources/Vehicles/Automobile.hpp"
  "Sources/Vehicles/Drone.cpp"
  "Sources/Vehicles/Drone.hpp"
  "Sources/Vehicles/Glider.cpp"
  "Sources/Vehicles/Glider.hpp"
  "Sources/Vehicles.cpp"
  "Sources/Vehicles.hpp"
)
target_compile_options ("ComLibrary"
  PUBLIC
    "/std:c++latest"
    "/permissive-"
)
target_include_directories ("ComLibrary"
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Sources"
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
