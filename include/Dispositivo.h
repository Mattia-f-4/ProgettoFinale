#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H

#include "Tempo.h"
#include <string>

class Dispositivo {
    public:
        
        //Getter
        int getID() const;
        std::string getNome() const;
        bool getStato() const;
        double getPotenza() const;
        Tempo getAccensione() const;
        Tempo getSpegnimento() const;

        //Setter
        void setStato(bool);
        void setAccensione(const Tempo&);
        void setSpegnimento(const Tempo&);

        //Member Function
        void changeStatus();
        double consumoEnergetico(const Tempo&) const;
    
    protected:
        
        //Costruttori
        Dispositivo(std::string, Tempo);
        
        //Variabili d'istanza
        int ID = 0;
        std::string nome;
        bool stato;
        double potenza;
        Tempo oraAccensione;
        Tempo oraSpegnimento;

};


#endif