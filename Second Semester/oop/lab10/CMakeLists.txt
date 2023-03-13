cmake_minimum_required(VERSION 3.22)
project(lab10)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab10 main.cpp FileRepository.cpp FileRepository.h Medicament.cpp Medicament.h Repository.cpp Repository.h Reteta.cpp Reteta.h Service.cpp Service.h UI.cpp UI.h Validation.cpp Validation.h VectDin.h Undo.h abstractrepo.cpp abstractrepo.h)
