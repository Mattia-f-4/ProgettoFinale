#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H

#include "Tempo.h"
#include <string>

class Dispositivo {
    public:
        //Costruttori
        Dispositivo(int ID, std::string nome, int prod, int consumo, Tempo accensione, Tempo accensionePost);
        
        //Distruttore
        virtual ~Dispositivo() = default;

        //Getter
        int getID() const;
        std::string getNome() const;
        int getProdPotenza() const;
        int getConsumoPotenza() const;
        bool getStato() const;
        Tempo getAccensione() const;
        Tempo getAccensionePost() const;

        //Setter
        void setStato(bool s);
        void setAccensione(const Tempo& ora);
        void setAccensionePost(const Tempo& ora);

        //Member Function
        void changeStatus();
    
    protected:
        //Variabili d'istanza
        int ID;
        std::string nome;
        int prodPotenza;
        int consumoPotenza;
        bool stato;
        Tempo oraAccensione;
        Tempo oraAccensionePost;
};

#endif