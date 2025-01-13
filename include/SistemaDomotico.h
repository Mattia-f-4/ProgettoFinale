#ifndef SISTEMADOMOTICO_H
#define SISTEMADOMOTICO_H

#include "DispManuale.h"
#include "DispCicloPrefissato.h"
#include "Logger.h"
#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <memory>
#include <queue>
#include <cmath>
#include <set>
#include <iomanip>
#include <sstream>

class SistemaDomotico
{
    public:
        //Costruttore
        SistemaDomotico(Logger&);    

        //Member Function
        void setTime(Tempo&);
        void setOff(std::string); //se si vuole scrivere in un file mettere 2 stream di output
        void setOn(std::string);    
        void setTimer(std::string, Tempo&);
        void setTimer(std::string, Tempo&, Tempo&);
        void rm(std::string);
    
        //Funzioni per logging
        void show(); 
        void show(std::string);
        void printTime();

        //Funzioni per la gestione dei dispositivi
        void add(std::string, DispCicloPrefissato::DispDomotico);
        void add(std::string, DispManuale::DispDomotico);
        void erase(std::string);

        // Funzioni di debug
        void resetTime();
        void resetTimers();
        void resetAll();
        
        //Getter
        int getSize() const;
        double getPotenzaResidua() const;
        double getLimitePotenza() const;
        Logger& getLogger() const;

        
    private:
        
        //Contenitori STL
        //int serve per indicare se si tratta di accensione o spegnimento  
        std::multimap<Tempo, std::pair<int,std::shared_ptr<Dispositivo>>> TimeLine;
        std::stack<std::string> OrdineAccensione;
        std::map<std::string,std::shared_ptr<Dispositivo>> DataBase;

        /* DATI MEMBRO */
        inline const static double limitePotenza = 3.5; //inline necessario per evitare di usare constexpr oppure di definire nel .cpp 
        double potenzaResidua;
        Tempo orario;
        int size;
        Logger& logger;

        /*FUNZIONI MEMBRO PRIVATE*/
        //Funzione di controllo 
        void sovraccarico();

        //Funzioni di supporto
        void setOffbyTimer(std::string);
        void setOnbyTimer(std::string);
        void setDatabase();
        void resetDatabase();
        void rmAll(std::string);


        //Funzione di supporto per il controllo dei timer
        bool isTimerValido(Tempo&, Tempo&, std::string, std::shared_ptr<Dispositivo>);

        //DEVONO ESSERE CANCELLATE ALLA FINE
        //Funzione di debug per capire il funzionamento generale
        void printTimeLine();
        void debugDatabase();
};

//Helper Function
bool isManuale(std::shared_ptr<Dispositivo>);
bool isCP(std::shared_ptr<Dispositivo>);

#endif