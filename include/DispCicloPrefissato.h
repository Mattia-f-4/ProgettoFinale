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

        //Costruttori
        DispCicloPrefissato(std::string, DispDomotico);
        DispCicloPrefissato(std::string, DispDomotico, Tempo);

        //Getter
        Tempo getDurata() const;

        //Distruttore
        ~DispCicloPrefissato() = default;

    private:
        
        //Variabili d'istanza
        static std::map<DispDomotico, std::pair<Tempo, double>> tipiDispositivi;
        DispDomotico tipoDispositivo;
        Tempo durata;
}; 

#endif