/* Creato da: GIACOMO CARLOTTO */

#ifndef DISPOSITIVOMANUALE_H
#define DISPOSITIVOMANUALE_H

#include "Dispositivo.h"
#include <map>

class DispManuale : public Dispositivo {
    public:
        
        // Enum class per elencare i vari tipi di dispositivi
        enum class DispDomotico {
            Impianto_Fotovoltaico,
            Pompa_di_calore_termostato,
            Scaldabagno,
            Frigorifero
        };

        // Costruttori
        DispManuale(std::string, DispDomotico);
        DispManuale(std::string, DispDomotico, Tempo, Tempo);

        // Setter
        void setSpegnimento(const Tempo&);

        // Distruttore
        ~DispManuale() = default;

    private:

        // Variabili d'istanza
        static std::map<DispDomotico, double> tipiDispositivi; // Mappa per caratteristiche dispositivi
        DispDomotico tipoDispositivo; // Tipo dispositivo da enum class
}; 

#endif