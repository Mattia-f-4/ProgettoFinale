#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H

#include "Tempo.h"
#include <string>
#include <cmath>

class Dispositivo {
    public:
        
        //Getter
        int getID() const;
        std::string getNome() const;
        bool getStato() const;
        double getPotenza() const;
        Tempo getAccensione() const;
        Tempo getSpegnimento() const;
        Tempo getDurataAccensione() const;

        //Setter
        void setStato(bool);
        void setAccensione(const Tempo&);
        void setSpegnimento(const Tempo&);

        //Member Function
        void changeStatus();
        double consumoEnergetico(const Tempo&) const;
        void reset();
    
    protected:
        
        //Costruttori
        Dispositivo(std::string, Tempo, Tempo);
        Dispositivo(std::string, Tempo);
        Dispositivo(std::string);
        
        //Variabili d'istanza
        int ID = 0;
        std::string nome;
        bool stato;
        double potenza;
        Tempo oraAccensione;
        Tempo oraSpegnimento;
        Tempo durataAccensione;

        //Distruttore
        virtual ~Dispositivo() = default;
};

#endif