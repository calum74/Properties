# CMakeList.txt : CMake project for Properties, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
include_directories("../include")

add_executable (PropertiesTest "Tests.cpp")
