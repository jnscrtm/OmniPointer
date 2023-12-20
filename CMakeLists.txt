# CMakeList.txt : CMake project for OmniPointer, include source and define

cmake_minimum_required (VERSION 3.1)

project ("OmniPointer")
add_library (OmniPointer STATIC "OmniPointer.cpp" "OmniPointer.hpp")
set_property(TARGET OmniPointer PROPERTY CXX_STANDARD 11)
