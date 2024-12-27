#include "Dispositivo.h"

using namespace std;

/* COSTRUTTORI */

    //Costruttore parametrico
    Dispositivo::Dispositivo(int ID, std::string nome, int prod, int consumo, Tempo accensione, Tempo accensionePost)
        : ID{ID}, nome{nome}, prodPotenza{prod}, consumoPotenza{consumo}, oraAccensione{accensione}, oraAccensionePost{accensionePost}, stato{false} {
        if(prod != 0 && consumo != 0)
            throw invalid_argument("A device cannot produce and consume power at the same time");

    }

/* FUNZIONI MEMBRO */

    //Getter
    int Dispositivo::getID() const { return ID; }
    string Dispositivo::getNome() const { return nome; }
    int Dispositivo::getProdPotenza() const { return prodPotenza; }
    int Dispositivo::getConsumoPotenza() const { return consumoPotenza; }
    bool Dispositivo::getStato() const { return stato; }
    Tempo Dispositivo::getAccensione() const { return oraAccensione; }
    Tempo Dispositivo::getAccensionePost() const { return oraAccensionePost; }

    //Setter
    void Dispositivo::setStato(bool s) { stato = s; }
    void Dispositivo::setAccensione(const Tempo& ora) { oraAccensione = ora; }
    void Dispositivo::setAccensionePost(const Tempo& ora) { oraAccensionePost = ora; }

    //changeStatus, per accendere/spegnere il dispositivo
    void Dispositivo::changeStatus() {
        if(getStato())
            setStato(false);
        else
            setStato(true);
    }