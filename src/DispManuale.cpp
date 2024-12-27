#include "DispManuale.h"

DispManuale::DispManuale(std::string nome, DispDomotico tipo, Tempo accensione, Tempo spegnimento)
    : Dispositivo(nome, accensione), tipoDispositivo{tipo}, oraSpegnimento{spegnimento}
{
    switch(tipoDispositivo) {
        case DispDomotico::Impianto_Fotovoltaico:
            tipiDispositivi[tipoDispositivo] = 1.5;
            break;
        case DispDomotico::Pompa_di_calore_termostato:
            tipiDispositivi[tipoDispositivo] = -2.0;
            break;
        case DispDomotico::Scaldabagno:
            tipiDispositivi[tipoDispositivo] = -1.0;
            break;
        case DispDomotico::Frigorifero:
            tipiDispositivi[tipoDispositivo] = -0.4;
            break;
    }

    potenza = tipiDispositivi[tipoDispositivo];
}

Tempo DispManuale::getSpegnimento() const { return oraSpegnimento; }
double DispManuale::getPotenza() const { return potenza; }