#ifndef DISPOSITIVOMANUALE_H
#define DISPOSITIVOMANUALE_H

#include "Dispositivo.h"
#include <map>

class DispManuale : public Dispositivo {
    public:
        enum class DispDomotico {
            Impianto_Fotovoltaico,
            Pompa_di_calore_termostato,
            Scaldabagno,
            Frigorifero
        };

        DispManuale(std::string, DispDomotico, Tempo, Tempo);

        // Setter
        void setSpegnimento(const Tempo&);

    private:
        std::map<DispDomotico, double> tipiDispositivi;
        DispDomotico tipoDispositivo;
}; 

#endif