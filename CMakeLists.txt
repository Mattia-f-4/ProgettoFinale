cmake_minimum_required(VERSION 2.8)

#Diamo un nome al progetto
project(Domotica LANGUAGES CXX )

#Specifichiammo il c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Aggiungiamo l'opzione di ottimizzazione
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

#Aggiugiamo la directory agli header
include_directories(include)

#Elenco manuale dei file sorgente
set(
    SOURCES
    src/main.cpp
    src/SistemaDomotico.cpp
    src/Dispositivo.cpp
    src/DispManuale.cpp
    src/DispCicloPrefissato.cpp
    src/Tempo.cpp
)

#Creiamo l'eseguibile
add_executable(main ${SOURCES})