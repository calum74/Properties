# CMakeList.txt : CMake project for Properties, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Properties "Properties.cpp" "Properties.h")

add_executable (PropertiesTest "Tests.cpp" "Property.hpp")
add_executable (PropertiesSample "Samples.cpp" "Property.hpp")


# TODO: Add tests and install targets if needed.
