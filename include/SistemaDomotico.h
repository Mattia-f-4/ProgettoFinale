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
        
        //Costruttore
        SistemaDomotico();    

        //Member Function
        std::ostream& setTime(std::ostream&, Tempo&);
        std::ostream& setOff(std::ostream&, Dispositivo&);
        std::ostream& setOn(std::ostream&, Dispositivo&);
        std::ostream& setTimer(std::ostream&, Dispositivo&, Tempo&);
        std::ostream& setTimer(std::ostream&, DispManuale&, Tempo&, Tempo&);
        std::ostream& rm(std::ostream&, DispManuale&);

        //Funzioni per logging
        std::ostream& show(std::ostream&); 
        std::ostream& show(std::ostream&, Dispositivo&);

        //Funzioni per la gestione dei dispositivi
        void add(DispManuale::DispDomotico);
        void add(DispCicloPrefissato::DispDomotico);
        void erase(int);

        // Funzioni di debug
        std::ostream& resetTime(std::ostream&);
        void resetTimers();
        void resetAll();

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
        std::multimap<Tempo, int> TimeLine;
        std::stack<int> OrdineAccensione;
        std::map<int,Dispositivo&> DataBase;

    /* DATI MEMBRO */
    const double limitePotenza;
    double potenzaResidua;
    Tempo orario;
    int size;

        //Funzione di controllo 
        void sovraccarico();
};

#endif