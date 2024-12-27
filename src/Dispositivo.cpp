#include "Dispositivo.h"

using namespace std;

/* VARIABILE GLOBALE ID */
    int globalID = 0;

/* COSTRUTTORI */

    //Costruttore parametrico
    Dispositivo::Dispositivo(std::string nome, Tempo accensione)
        : nome{nome}, oraAccensione{accensione}, stato{false}, ID{++globalID} {}

/* FUNZIONI MEMBRO */

    //Getter
    int Dispositivo::getID() const { return ID; }
    string Dispositivo::getNome() const { return nome; }
    bool Dispositivo::getStato() const { return stato; }
    Tempo Dispositivo::getAccensione() const { return oraAccensione; }

    //Setter
    void Dispositivo::setStato(bool s) { stato = s; }
    void Dispositivo::setAccensione(const Tempo& ora) { oraAccensione = ora; }

    //changeStatus, per accendere/spegnere il dispositivo
    void Dispositivo::changeStatus() {
        if(getStato())
            setStato(false);
        else
            setStato(true);
    }