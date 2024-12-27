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
        Tempo getAccensione() const;

        //Setter
        void setStato(bool s);
        void setAccensione(const Tempo& ora);

        //Member Function
        void changeStatus();
    
    protected:
        //Costruttori
        Dispositivo(int ID, std::string nome, Tempo accensione);

        //Distruttore
        virtual ~Dispositivo() = default;

        //Variabili d'istanza
        int ID;
        std::string nome;
        bool stato;
        Tempo oraAccensione;
};

#endif