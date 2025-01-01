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
        std::ostream& setOff(std::ostream&, std::string); //se si vuole scrivere in un file mettere 2 stream di output
        std::ostream& setOn(std::ostream&, std::string);    
        std::ostream& setTimer(std::ostream&, std::string, Tempo&);
        std::ostream& setTimer(std::ostream&, std::string, Tempo&, Tempo&);
        std::ostream& rm(std::ostream&, std::string);
    
        //Funzioni per logging
        std::ostream& show(std::ostream&); 
        std::ostream& show(std::ostream&, std::string);

        //Funzioni per la gestione dei dispositivi
        void add(std::string, DispCicloPrefissato::DispDomotico);
        void add(std::string, DispManuale::DispDomotico);
        void erase(std::string);

        // Funzioni di debug
        std::ostream& resetTime(std::ostream&);
        void resetTimers();
        void resetAll();

        //Funzioni di supporto alle funzioni di debug
        void setOffAll();
        void rmAll();
        //Funzioni di supporto alle member function
        bool isManuale(Dispositivo*);
        bool isCP(Dispositivo*);

        //Getter
        int getSize() const;
        Tempo getTime() const;
        double getPotenzaResidua() const;
        double getLimitePotenza() const;

    private:
        
        //Contenitori STL 
        //int serve per indicare se si tratta di accensione o spegnimento  
        std::multimap<Tempo, std::pair<int,Dispositivo*>> TimeLine;
        std::stack<std::string> OrdineAccensione;
        std::map<std::string,Dispositivo*> DataBase;

        /* DATI MEMBRO */
        inline const static double limitePotenza = 3.5; //inline necessario per evitare di usare constexpr oppure di definire nel .cpp 
        double potenzaResidua;
        Tempo orario;
        int size;

        //Funzione di controllo 
        void sovraccarico(std::ostream&);
};

#endif