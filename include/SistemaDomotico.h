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
        std::ostream& setOff(std::ostream&, std::string);
        std::ostream& setOn(std::ostream&, std::string);
        std::ostream& setTimer(std::ostream&, std::string, Tempo&);
        std::ostream& setTimer(std::ostream&, std::string, Tempo&, Tempo&);
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
        std::multimap<Tempo, std::string> TimeLine;
        std::stack<std::string> OrdineAccensione;
        std::map<std::string,Dispositivo*> DataBase;

        /* DATI MEMBRO */
        constexpr static double limitePotenza = 3.5; 
        double potenzaResidua;
        Tempo orario;
        int size;

        //Funzione di controllo 
        void sovraccarico();
};

#endif