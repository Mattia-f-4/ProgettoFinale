#ifndef DISPOSITIVOCICLO_H
#define DISPOSITIVOCICLO_H

#include "Dispositivo.h"
#include <map>

class DispCicloPrefissato : public Dispositivo {
    public:
        
        //Enum class per elencare i vari tipi di dispositivi
        enum class DispDomotico {
            Lavatrice,
            Lavastoviglie,
            Tapparelle_elettriche,
            Forno_a_microonde,
            Asciugatrice,
            Televisore
        };

        //Costruttore
        DispCicloPrefissato(std::string, DispDomotico, Tempo);

        //Getter
        Tempo getDurata() const;

        //Setter
        void setAccensione(const Tempo&);

    private:
        
        //Variabili d'istanza
        std::map<DispDomotico, std::pair<Tempo, double>> tipiDispositivi;
        DispDomotico tipoDispositivo;
        Tempo durata;
}; 

#endif