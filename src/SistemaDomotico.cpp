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

    Dispositivo* ImpiantoFotovoltaico = new DispManuale("Impianto fotovoltaico",DispManuale::DispDomotico::Impianto_Fotovoltaico);

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
        Dispositivo* d = DataBase.find(disp) -> second;
        d -> setStato(0); //spegniamo il dispositivo
        if(isManuale(d))//solo i manuali hanno il timer di spegnimento
        {
            for(auto p = TimeLine.begin(); p != TimeLine.end(); p++)
                {
                    if(p->second.second -> getNome() == disp && p->second.first==0)
                    {
                        TimeLine.erase(p);
                    }
                    break; //tolgo solo il primo di spegnimento
                }; 
        }
        //Il calcolo della potenza sarà poi fatto da show
        d->setSpegnimento(orario);

        potenzaResidua -= DataBase.find(disp) -> second -> getPotenza(); //aggiorniamo la potenza residua del sistema
        if(potenzaResidua<0)
        {
            sovraccarico();
        }
        
        //Non rimuovo dallo stack il dispositivo, in caso di spegnimento controllerò se è ancora acceso
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
        //Se la sua accensione comporterebbe un superamento della potenza non lo accendo
        if(potenzaResidua + DataBase.find(disp) -> second -> getPotenza() > limitePotenza)
        {
            //Solo i manuali hanno i timer di spegnimento
            Dispositivo* d = DataBase.find(disp)->second;
            if(isManuale(d)) 
            {
                //Rimuovo eventuali timer di spegnimento nel caso in cui l'accensione sia stata chiamata da un timer
                for(auto p = TimeLine.begin(); p != TimeLine.end(); p++)
                {
                    if(p->second.second -> getNome() == disp && p->second.first==0)
                    {
                        TimeLine.erase(p);
                    }
                    break; //tolgo solo il primo di spegnimento
                }; 
            }
            out << orario << " " << disp << " non acceso. Limite di potenza raggiunto." << std::endl; 
        }
        else
        {
            Dispositivo* d = DataBase.find(disp)->second;
            d-> setStato(1); //accendiamo il dispositivo
            potenzaResidua += d -> getPotenza(); //aggiorniamo la potenza residua del sistema
            d->setAccensione(orario); //indichiamo l'ora di accensione

            //Se è a ciclo prefissato dobbiamo inserire nella TimeLine il suo spegnimento
            if(isCP(d))
            {
                //I distruttori virtuali servono per garantire che questo metodo funzioni
                DispCicloPrefissato* cp = dynamic_cast<DispCicloPrefissato*>(d);

                Tempo spegn = cp->getDurata() + orario;
                TimeLine.insert(std::make_pair(spegn, std::make_pair(0,d)));
            }

            //Mettiamo nello stack l'accensione in modo da poter gestire la politca di spegnimento
            OrdineAccensione.push(disp);
            //Mostriamo a schermo il messaggio
            out << orario << " Il dispositivo" << disp << " si è acceso." << std::endl;
        } //VA CONTROLLATO SE VA BENE CON LA MULTIMAP
    }

    return out;
}

//Funzioni di supporto per determinare il tipo di dispositivo
bool SistemaDomotico::isManuale(Dispositivo* d)
{
    return d->getID()%2==0;
}
bool SistemaDomotico::isCP(Dispositivo* d)
{
    return d->getID()%2==1;
}

//setTimer
std::ostream& SistemaDomotico::setTimer(std::ostream& out, std::string disp, Tempo& accensione)
{
    auto  p = DataBase.find(disp);
    if(p == DataBase.end())
    {
        //se cerco di impostare un timer per un dispositivo inesistente mi avverte
        out << orario << " Il dispositivo " << disp << " non esiste. Impossibile impostare il timer desiderato." << std::endl;
    }
    else
    {
        if(accensione<orario || accensione == Tempo(-1,0)) //Non imposto il timer se gli orari non sono validi
        {
            out << orario << " L'orario di accensione inserito è non valido. Timer non settato." << std::endl;
        }
        else
        {
            TimeLine.insert(std::make_pair(accensione, std::make_pair(1, p -> second)));

            //si potrebbe dividere il messaggio per cp e manuale, dicendo per i cp l'orario in cui si spegne
            out << orario << " Impostato un timer per il dispositivo " << disp << " dalle ore " << accensione <<std::endl;
        }
    }
    return out;
}

std::ostream& SistemaDomotico::setTimer(std::ostream& out, std::string disp, Tempo& accensione, Tempo& spegnimento)
{
    auto p = DataBase.find(disp);
    if(p == DataBase.end())
    {
        //se cerco di impostare un timer per un dispositivo inesistente mi avverte
        out << orario << " Il dispositivo " << disp << " non esiste. Impossibile impostare il timer desiderato." << std::endl;
    }
    else
    {
        if(accensione<orario || accensione == Tempo(-1,0) || spegnimento == Tempo(-1,0) || accensione > spegnimento) //Non imposto il timer se gli orari non sono validi
        {
            out << orario << " L'orario inserito non è valido. Timer non settato." << std::endl;
        }
        else
        {  
            Dispositivo* d = p -> second;
            //Il timer di accensione viene sempre messo
            TimeLine.insert(std::make_pair(accensione, std::make_pair(1, d)));

            //Per i dispositivi CP il timer di spegnimento viene ignorato
            if(isCP(d))
            {
                out << orario << " Impostato un timer per il dispositivo " << disp << " dalle ore " << accensione << "." <<std::endl;
            }
            else if(isManuale(d)) //uso else if nel caso in cui venissero introdotti ulteriori tipi di dispositivi
            {
                TimeLine.insert(std::make_pair(spegnimento, std::make_pair(0, d)));

                out << orario << " Impostato un timer per il dispositivo " << disp << " dalle ore " << accensione << " alle ore" << spegnimento << "."<<std::endl;

            }
        }
    }
    return out;
}

//Rimozione del timer
std::ostream& SistemaDomotico::rm(std::ostream& out, std::string disp)
{
    auto p = DataBase.find(disp);
    if(p == DataBase.end())
    {
        //se cerco di eliminare un timer per un dispositivo inesistente mi avverte
        out << orario << " Il dispositivo " << disp << " non esiste. Impossibile eliminare il timer desiderato." << std::endl;
    }
    else
    {
        //In questo modo rimuove tutti i timer dei dispositivi
        for(auto p = TimeLine.begin(); p != TimeLine.end(); p++)
        {
            if(p->second.second -> getNome() == disp)
            {
                TimeLine.erase(p);
            }
            //se cerco di eliminare un timer per un dispositivo inesistente mi avverte
            out << orario << " Rimosso il timer dal dispositivo " << disp << " ." << std::endl;
        }; 
    }
    return out;
}

//setTime
std::ostream& SistemaDomotico::setTime(std::ostream& out, Tempo& t)
{
    if(t<orario)
    {
        out << orario << " orario inserito non valido." << std::endl;
    }
    else
    {

        for(auto p = TimeLine.begin(); p != TimeLine.end(); p++)
        {
            //aggiorno l'ora del sistema
            orario = p->first;
            Dispositivo* d = p->second.second;
            //Se devo accendere
            if(p->second.first==1)
            {
                setOn(out, d->getNome());
            }
            else if(p->second.first==1) //uso un else if se in futuro ci saranno altri comandi
            {
                setOff(out, d->getNome());
            }         
            

            TimeLine.erase(p);
        }; 
    }

    return out;
}
