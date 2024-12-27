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

        DispManuale(int ID, std::string nome, DispDomotico tipoDispositivo, Tempo accensione, Tempo spegnimento);

        // Getter
        Tempo getSpegnimento() const;
        double getPotenza() const;

        // Setter
        void setAccensione(const Tempo& ora);

    private:
        std::map<DispDomotico, double> tipiDispositivi;
        Tempo oraSpegnimento;
        DispDomotico tipoDispositivo;
        double potenza;
}; 

#endif