cmake_minimum_required(VERSION 3.21)
project(lab6_7dinamic)

set(CMAKE_CXX_STANDARD 14)

include_directories(lab6-7dinamic)

add_executable(lab6_7dinamic
        lab6-7dinamic/DynamicVector.h
        lab6-7dinamic/main.cpp
        lab6-7dinamic/Masina.cpp
        lab6-7dinamic/Masina.h
        lab6-7dinamic/RepoMasina.cpp
        lab6-7dinamic/RepoMasina.h
        lab6-7dinamic/ServiceMasina.cpp
        lab6-7dinamic/ServiceMasina.h
        lab6-7dinamic/UI.cpp
        lab6-7dinamic/UI.h
        lab6-7dinamic/ValidatorMasina.cpp
        lab6-7dinamic/ValidatorMasina.h)
