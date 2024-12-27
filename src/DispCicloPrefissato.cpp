#include "DispCicloPrefissato.h"

DispCicloPrefissato::DispCicloPrefissato(int ID, std::string nome, DispDomotico tipo, Tempo accensione)
    : Dispositivo(ID, nome, accensione), tipoDispositivo{tipo}
{
    switch(tipoDispositivo) {
        case DispDomotico::Lavatrice:
            tipiDispositivi[tipoDispositivo] = {{1, 50}, -2.0};
            break;
        case DispDomotico::Lavastoviglie:
            tipiDispositivi[tipoDispositivo] = {{3, 15}, -1.5};
            break;
        case DispDomotico::Tapparelle_elettriche:
            tipiDispositivi[tipoDispositivo] = {{0, 1}, -0.3};
            break;
        case DispDomotico::Forno_a_microonde:
            tipiDispositivi[tipoDispositivo] = {{0, 2}, -0.8};
            break;
        case DispDomotico::Asciugatrice:
            tipiDispositivi[tipoDispositivo] = {{1, 0}, -0.5};
            break;
        case DispDomotico::Televisore:
            tipiDispositivi[tipoDispositivo] = {{1, 0}, -0.2};
            break;
    }

    durata = tipiDispositivi[tipoDispositivo].first;
    potenza = tipiDispositivi[tipoDispositivo].second;
}

Tempo DispCicloPrefissato::getDurata() const { return durata; }
double DispCicloPrefissato::getPotenza() const { return potenza; }