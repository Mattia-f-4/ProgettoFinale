/* Creato da: GIACOMO CARLOTTO */

#include "DispCicloPrefissato.h"

/* VARIABILE GLOBALE ID */
    int CycleID = 1;    // ID dispari per dispositivo a ciclo prefissato

/* COSTRUTTORI */
    
    // Costruttore parametrico con orario di accensione
    DispCicloPrefissato::DispCicloPrefissato(std::string nome, DispDomotico tipo, Tempo accensione)
        : Dispositivo(nome, accensione), tipoDispositivo{tipo}
    {
        // Assegnamento e aggiornamento ID
        ID = CycleID;
        CycleID += 2;

        durata = tipiDispositivi[tipoDispositivo].first;
        oraSpegnimento = getAccensione() + durata;
        potenza = tipiDispositivi[tipoDispositivo].second;
    }

    // Costruttore parametrico senza orario di accensione
    DispCicloPrefissato::DispCicloPrefissato(std::string nome, DispDomotico tipo)
        : Dispositivo(nome), tipoDispositivo{tipo}
    {
        // Assegnamento e aggiornamento ID
        ID = CycleID;
        CycleID += 2;

        durata = tipiDispositivi[tipoDispositivo].first;
        potenza = tipiDispositivi[tipoDispositivo].second;

    }

/* FUNZIONI MEMBRO*/

    // Getter
    Tempo DispCicloPrefissato::getDurata() const { return durata; }

/* MAPPA */

    //Mappa per tipi dispositivi a ciclo prefissato
    std::map<DispCicloPrefissato::DispDomotico, std::pair<Tempo, double>> DispCicloPrefissato::tipiDispositivi = {
        {DispCicloPrefissato::DispDomotico::Lavatrice, {{1, 50}, -2.0}},
        {DispCicloPrefissato::DispDomotico::Lavastoviglie, {{3, 15}, -1.5}},
        {DispCicloPrefissato::DispDomotico::Tapparelle_elettriche, {{0, 1}, -0.3}},
        {DispCicloPrefissato::DispDomotico::Forno_a_microonde, {{0, 2}, -0.8}},
        {DispCicloPrefissato::DispDomotico::Asciugatrice, {{1, 0}, -0.5}},
        {DispCicloPrefissato::DispDomotico::Televisore, {{1, 0}, -0.2}}
    };