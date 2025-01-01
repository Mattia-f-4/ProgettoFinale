cmake_minimum_required(VERSION 3.0)

#Diamo un nome al progetto
project(Domotica VERSION 1.0 LANGUAGES CXX )

#Specifichiammo il c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Aggiungiamo l'opzione di ottimizzazione
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

#Aggiugiamo la directory agli header
include_directories(include)

#Aggiugiamo i file sorgente
file(GLOB_RECURSE SOURCES src/*.cpp)

#Creiamo l'eseguibile
add_executable(main ${SOURCES})