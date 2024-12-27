#ifndef DISPOSITIVOCICLO_H
#define DISPOSITIVOCICLO_H

#include "Dispositivo.h"
#include <map>

class DispCicloPrefissato : public Dispositivo {
    public:
        enum class DispDomotico {
            Lavatrice,
            Lavastoviglie,
            Tapparelle_elettriche,
            Forno_a_microonde,
            Asciugatrice,
            Televisore
        };

        DispCicloPrefissato(std::string nome, DispDomotico tipo, Tempo accensione);

        //Getter
        Tempo getDurata() const;

        //Setter
        void setAccensione(const Tempo& ora);

    private:
        std::map<DispDomotico, std::pair<Tempo, double>> tipiDispositivi;
        Tempo durata;
        DispDomotico tipoDispositivo;
}; 

#endif