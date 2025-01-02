#include "DispCicloPrefissato.h"

/* VARIABILE GLOBALE ID */
    int CycleID = 1;    //Disp. a ciclo prefissato hanno ID dispari

/* COSTRUTTORI */
    
    //Costruttore parametrico
    DispCicloPrefissato::DispCicloPrefissato(std::string nome, DispDomotico tipo, Tempo accensione)
        : Dispositivo(nome, accensione), tipoDispositivo{tipo}
    {
        //Assegnamento e aggiornamento ID
        ID = CycleID;
        CycleID += 2;

        durata = tipiDispositivi[tipoDispositivo].first;
        oraSpegnimento = getAccensione() + durata;
        potenza = tipiDispositivi[tipoDispositivo].second;
    }

    DispCicloPrefissato::DispCicloPrefissato(std::string nome, DispDomotico tipo)
        : Dispositivo(nome), tipoDispositivo{tipo}
    {
        //Assegnamento e aggiornamento ID
        ID = CycleID;
        CycleID += 2;

        durata = tipiDispositivi[tipoDispositivo].first;
        oraSpegnimento = getAccensione() + durata;
        potenza = tipiDispositivi[tipoDispositivo].second;
    }

    DispCicloPrefissato::DispCicloPrefissato(std::string nome, DispDomotico tipo)
        : Dispositivo(nome), tipoDispositivo{tipo}
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

        //Assegnamento e aggiornamento ID
        ID = CycleID;
        CycleID = CycleID + 2;

        durata = tipiDispositivi[tipoDispositivo].first;
        potenza = tipiDispositivi[tipoDispositivo].second;
    }

/* FUNZIONI MEMBRO*/

    //Getter
    Tempo DispCicloPrefissato::getDurata() const { return durata; }

/* MAPPA */

    //Mappa per tipi dispositivi a ciclo prefissato
    std::map<DispCicloPrefissato::DispDomotico, std::pair<Tempo, double>> DispCicloPrefissato::tipiDispositivi={
        {DispCicloPrefissato::DispDomotico::Lavatrice, {{1, 50}, -2.0}},
        {DispCicloPrefissato::DispDomotico::Lavastoviglie, {{3, 15}, -1.5}},
        {DispCicloPrefissato::DispDomotico::Tapparelle_elettriche, {{0, 1}, -0.3}},
        {DispCicloPrefissato::DispDomotico::Forno_a_microonde, {{0, 2}, -0.8}},
        {DispCicloPrefissato::DispDomotico::Asciugatrice, {{1, 0}, -0.5}},
        {DispCicloPrefissato::DispDomotico::Televisore, {{1, 0}, -0.2}}
    };