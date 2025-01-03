#ifndef DISPOSITIVOMANUALE_H
#define DISPOSITIVOMANUALE_H

#include "Dispositivo.h"
#include <map>

class DispManuale : public Dispositivo {
    public:
        
        //Enum class per elencare i vari dispositivi possibili
        enum class DispDomotico {
            Impianto_Fotovoltaico,
            Pompa_di_calore_termostato,
            Scaldabagno,
            Frigorifero
        };

        //Costruttore
        DispManuale(std::string, DispDomotico, Tempo, Tempo);

        //Setter
        void setSpegnimento(const Tempo&);

    private:

        //Variabili d'istanza
        std::map<DispDomotico, double> tipiDispositivi;
        DispDomotico tipoDispositivo;
}; 

#endif