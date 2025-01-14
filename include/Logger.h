/* Creato da: DAVID PADOVAN */

#ifndef LOGGER_H
#define LOGGER_H

#include "Tempo.h"

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

class Logger {
    public:
        
        //Costruttore
        Logger(const std::string&);

        //Distruttore
        ~Logger();

        //Member Function
        void log(const std::string&);
        void log(const Tempo&);
        void logInput(const std::string&);

    private:

        //Variabili d'istanza
        std::ofstream logFile;          //File di log       
        std::string filePath;           //Percorso del file di log
};

#endif