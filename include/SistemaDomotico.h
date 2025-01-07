#ifndef SISTEMADOMOTICO_H
#define SISTEMADOMOTICO_H

#include "DispManuale.h"
#include "DispCicloPrefissato.h"
#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <memory>
#include <queue>
#include <cmath>
#include <set>

class SistemaDomotico
{
    public:
        //Costruttore
        SistemaDomotico();    

        //Member Function
        std::ostream& setTime(std::ostream&, Tempo&);
        std::ostream& setOff(std::ostream&, std::string); //se si vuole scrivere in un file mettere 2 stream di output
        std::ostream& setOn(std::ostream&, std::string);    
        std::ostream& setTimer(std::ostream&, std::string, Tempo&);
        std::ostream& setTimer(std::ostream&, std::string, Tempo&, Tempo&);
        std::ostream& rm(std::ostream&, std::string);
    
        //Funzioni per logging
        std::ostream& show(std::ostream&); 
        std::ostream& show(std::ostream&, std::string);

        //Funzioni per la gestione dei dispositivi
        std::ostream& add(std::ostream&, std::string, DispCicloPrefissato::DispDomotico);
        std::ostream& add(std::ostream&, std::string, DispManuale::DispDomotico);
        std::ostream& erase(std::ostream&, std::string);

        // Funzioni di debug
        std::ostream& resetTime(std::ostream&);
        std::ostream& resetTimers(std::ostream&);
        std::ostream& resetAll(std::ostream&);

        //Funzioni di supporto alle funzioni di debug
        void setOffAll();
        void rmAll();
        
        //Getter
        int getSize() const;
        Tempo getTime() const;
        double getPotenzaResidua() const;
        double getLimitePotenza() const;

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

        //Funzione di controllo 
        void sovraccarico(std::ostream&);

        //Funzione di supporto
        std::ostream& setOffbyTimer(std::ostream&, std::string);
        std::ostream& setOnbyTimer(std::ostream&, std::string);

        //Funzione di supporto per il controllo dei timer
        bool isTimerValido(Tempo&, Tempo&, std::string, std::shared_ptr<Dispositivo>);

        //Funzione di debug per capire il funzionamento generale
        std::ostream& printTimeLine(std::ostream&);

};

//Helper Function
bool isManuale(std::shared_ptr<Dispositivo>);
bool isCP(std::shared_ptr<Dispositivo>);

#endif