#ifndef SISTEMADOMOTICO_H
#define SISTEMADOMOTICO_H

#include "DispManuale.h"
#include "DispCicloPrefissato.h"
#include <iostream>
#include <map>
#include <stack>
#include <vector>

class SistemaDomotico
{
    public:
        //Costruttori
        SistemaDomotico(); 
        SistemaDomotico(double);    

        //Member Function
        void setTime(Tempo&);
        void setOff(Dispositivo&);
        void setOn(Dispositivo&);
        void setTimer(Dispositivo&, Tempo&);
        void setTimer(DispManuale&, Tempo&, Tempo&);
        void rm(DispManuale&);
        void add(DispManuale::DispDomotico);
        void add(DispCicloPrefissato::DispDomotico);
        void erase(int);
        
        //Funzioni di debug
        void resetTime();
        void resetTimers();
        void resetAll();

    private:
        //Contenitori STL
        std::multimap<Tempo, int> TimeLine;
        std::stack<int> OrdineAccensione;
        std::map<int,Dispositivo&> DataBase;

        //Variabili d'istanza
        const double limitePotenza;
        double potenzaResidua;
        Tempo orario;
        int size;

        //Member function
        void sovraccarico();
};

//Helper function
std::ostream& show(std::ostream&, SistemaDomotico&);
std::ostream& show(std::ostream&, SistemaDomotico&, Dispositivo&);

#endif