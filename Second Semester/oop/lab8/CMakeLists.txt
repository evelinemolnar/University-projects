cmake_minimum_required(VERSION 3.22)
project(lab8)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab8 main.cpp Medicament.cpp Medicament.h Repository.cpp Repository.h Service.cpp Service.h UI.cpp UI.h Validator.cpp Validator.h Exceptii.cpp Exceptii.h)
