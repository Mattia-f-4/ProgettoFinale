#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "Tempo.h"

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
        std::ofstream logFile;
        std::string filePath;

};