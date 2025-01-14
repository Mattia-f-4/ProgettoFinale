/* Creato da: DAVID PADOVAN */

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
        Dispositivo(std::string, Tempo, Tempo);     //I costruttori sono protected perchè non deve essere possibile istanziare oggetti della classe Dispositivo
        Dispositivo(std::string, Tempo);
        Dispositivo(std::string);
        
        //Variabili d'istanza
        int ID = 0;
        std::string nome;
        bool stato;                                 //Acceso = True, Spento = False
        double potenza;                             //Potenza intesa sia come Produzione (+) sia come Consumo (-)
        Tempo oraAccensione;
        Tempo oraSpegnimento;                       //Lo spegnimento è gestito differentemente per Disp. Manuali o CP, ma entrambi possiedono un orario di spegnimento (tramite durata o timer)
        Tempo durataAccensione;                     //Durata intesa come periodo di tempo totale in cui il Dispositivo è rimasto acceso

        //Distruttore
        virtual ~Dispositivo() = default;
};

#endif