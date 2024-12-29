#include "SistemaDomotico.h"

//Getter
int SistemaDomotico::getSize() const {return size;}

Tempo SistemaDomotico::getTime() const {return orario;}

double SistemaDomotico::getPotenzaResidua() const {return potenzaResidua;}

double SistemaDomotico::getLimitePotenza() const {return limitePotenza;}

//Costruttore
SistemaDomotico::SistemaDomotico() : orario{0,0}, size{10}, potenzaResidua{limitePotenza}
{
    //Creazione dei dispositivi manuali predefiniti
    Dispositivo* Frigorifero = new DispManuale("Frigorifero",DispManuale::DispDomotico::Frigorifero);

    Dispositivo* ImpiantoFotovoltaico = new DispManuale("Impianto Fotovoltaico",DispManuale::DispDomotico::Impianto_Fotovoltaico);

    Dispositivo* Pompa_di_calore_termostato = new DispManuale("Pompa di calore + termostato",DispManuale::DispDomotico::Pompa_di_calore_termostato);

    Dispositivo* Scaldabagno = new DispManuale("Scaldabagno",DispManuale::DispDomotico::Scaldabagno);

    //Creazione dei dispositivi a ciclo prefissato predefiniti
    Dispositivo* Asciugatrice = new DispCicloPrefissato("Asciugatrice",DispCicloPrefissato::DispDomotico::Asciugatrice);

    Dispositivo* Forno_a_microonde = new DispCicloPrefissato("Forno a microonde",DispCicloPrefissato::DispDomotico::Forno_a_microonde);

    Dispositivo* Lavastoviglie = new DispCicloPrefissato("Lavastoviglie",DispCicloPrefissato::DispDomotico::Lavastoviglie);

    Dispositivo* Lavatrice = new DispCicloPrefissato("Lavatrice",DispCicloPrefissato::DispDomotico::Lavatrice);

    Dispositivo* Tapparelle_elettriche = new DispCicloPrefissato("Tapparelle elettriche",DispCicloPrefissato::DispDomotico::Tapparelle_elettriche);

    Dispositivo* Televisore = new DispCicloPrefissato("Televisore",DispCicloPrefissato::DispDomotico::Televisore);

    //Creazione del DataBase
    DataBase.insert(std::make_pair(Frigorifero ->getNome(),Frigorifero));
    DataBase.insert(std::make_pair(ImpiantoFotovoltaico ->getNome(),ImpiantoFotovoltaico));
    DataBase.insert(std::make_pair(Pompa_di_calore_termostato ->getNome(),Pompa_di_calore_termostato));
    DataBase.insert(std::make_pair(Scaldabagno ->getNome(),Scaldabagno));
    DataBase.insert(std::make_pair(Asciugatrice ->getNome(),Asciugatrice));
    DataBase.insert(std::make_pair(Forno_a_microonde ->getNome(),Forno_a_microonde));
    DataBase.insert(std::make_pair(Lavastoviglie ->getNome(),Lavastoviglie));
    DataBase.insert(std::make_pair(Lavatrice ->getNome(),Lavatrice));
    DataBase.insert(std::make_pair(Tapparelle_elettriche ->getNome(),Tapparelle_elettriche));
    DataBase.insert(std::make_pair(Televisore ->getNome(),Televisore));

}

/*MEMBER FUNCTION*/

//setOff
std::ostream& SistemaDomotico::setOff(std::ostream& out, std::string disp)
{
    if(DataBase.find(disp)==DataBase.end())
    {
        out << orario << " " << disp << " non presente nel Sistema Domotico." << std::endl;
    }
    else
    {
        DataBase.find(disp) -> second -> setStato(0); //spegniamo il dispositivo
        potenzaResidua -= DataBase.find(disp) -> second -> getPotenza(); //aggiorniamo la potenza residua del sistema

        //Mostriamo a schermo il messaggio
        out << orario << " Il dispositivo" << disp << " si è spento." << std::endl;
    }

    return out;
}

//setOn
std::ostream& SistemaDomotico::setOn(std::ostream& out, std::string disp)
{
    if(DataBase.find(disp)==DataBase.end())
    {
        out << orario << " " << disp << " non presente nel Sistema Domotico." << std::endl;
    }
    else
    {
        DataBase.find(disp) -> second -> setStato(1); //accendiamo il dispositivo
        potenzaResidua += DataBase.find(disp) -> second -> getPotenza(); //aggiorniamo la potenza residua del sistema

        //Mettiamo nello stack l'accensione in modo da poter gestire la politca di spegnimento
        OrdineAccensione.push(disp);
        //Mostriamo a schermo il messaggio
        out << orario << " Il dispositivo" << disp << " si è acceso." << std::endl;
    }

    return out;
}

//setTimer
std::ostream& SistemaDomotico::setTimer(std::ostream& out, std::string disp, Tempo& accensione)
{
    if(accensione<orario)
    {
        //da terminare
    }
    return out;
}

std::ostream& SistemaDomotico::setTimer(std::ostream& out, std::string disp, Tempo& accensione, Tempo& spegnimento)
{
    return out;
}
