#include "SistemaDomotico.h"

/*COSTRUTTORI*/    

    //Costruttore parametrico
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

/*FUNZIONI MEMBRO*/

    //Getter
    int SistemaDomotico::getSize() const {return size;}
    Tempo SistemaDomotico::getTime() const {return orario;}
    double SistemaDomotico::getPotenzaResidua() const {return potenzaResidua;}
    double SistemaDomotico::getLimitePotenza() const {return limitePotenza;}

    //setOff
    std::ostream& SistemaDomotico::setOff(std::ostream& out, std::string disp)
    {
        auto pData = DataBase.find(disp);
        if(pData==DataBase.end())
        {
            out << orario << " " << disp << " non presente nel Sistema Domotico." << std::endl;
        }
        else
        {
            if(pData->second->getStato()==0)
            {
                out << orario << " " << disp << " gia' spento." << std::endl;
            }
            else
            {
                Dispositivo* d = pData->second;
                d -> setStato(0); //spegniamo il dispositivo
                
                for(auto p = TimeLine.begin(); p != TimeLine.end(); p++)
                    {
                        if(p->second.second -> getNome() == disp && p->second.first==0 && p->first!=orario)
                        {
                            TimeLine.erase(p);
                        }
                        break; //tolgo solo il primo di spegnimento
                    }; 
                
                //Il calcolo della potenza sarà poi fatto da show
                d->setSpegnimento(orario);

                potenzaResidua -= pData -> second -> getPotenza(); //aggiorniamo la potenza residua del sistema
                if(potenzaResidua<0)
                {
                    sovraccarico(out);
                }
                
                //Non rimuovo dallo stack il dispositivo, in caso di spegnimento controllerò se è ancora acceso
                //Mostriamo a schermo il messaggio
                out << orario << " Il dispositivo " << disp << " si e' spento." << std::endl;
            }
        }

        return out;
    }

    //setOn
    std::ostream& SistemaDomotico::setOn(std::ostream& out, std::string disp)
    {
        //Se il dispositivo non è presente nel DataBase non faccio nulla
        auto pData = DataBase.find(disp);
        if(pData==DataBase.end())
        {
            out << orario << " " << disp << " non presente nel Sistema Domotico." << std::endl;
        }
        else
        {
            Dispositivo* d = pData->second;
            //Se il dispositivo è gia acceso prolungo la sua durata nel caso in cui sia CP, se manuale non faccio nulla
            if(pData-> second -> getStato()==1)
            {
                out << orario << " " << disp << " gia' acceso." << std::endl;

                if(isCP(d))
                {
                    //Rimuovo timer di spegnimento in quanto dispositivo CP ne ha sempre uno
                    for(auto pTime = TimeLine.begin(); pTime != TimeLine.end(); pTime++)
                    {
                        if(pTime->second.second -> getNome() == disp && pTime->second.first==0)
                        {
                            TimeLine.erase(pTime);
                        }
                        break; //tolgo solo il primo di spegnimento
                    }; 

                    //Aggiorno il timer di spegnimento
                    DispCicloPrefissato* cp = dynamic_cast<DispCicloPrefissato*>(d);
                    Tempo spegn = cp->getDurata() + orario;
                    TimeLine.insert(std::make_pair(spegn, std::make_pair(0,d)));
                }
            }
            else
            {
                //Se la sua accensione comporterebbe un superamento della potenza non lo accendo
                if(potenzaResidua + pData->second->getPotenza() > limitePotenza)
                {
                    //Rimuovo eventuali timer di spegnimento nel caso in cui l'accensione sia stata chiamata da un timer
                    for(auto pTime = TimeLine.begin(); pTime != TimeLine.end(); pTime++)
                    {
                        if(pTime->second.second -> getNome() == disp && pTime->second.first==0 && pTime->first!=orario)
                        {
                            TimeLine.erase(pTime);
                        }
                        break; //tolgo solo il primo di spegnimento
                    }; 
                    
                    out << orario << " " << disp << " non acceso. Limite di potenza raggiunto." << std::endl; 
                }
                else
                {
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
                    out << orario << " Il dispositivo " << disp << " si e' acceso." << std::endl;
                }
            }
        }

        return out;
    }

    //setTimer
    std::ostream& SistemaDomotico::setTimer(std::ostream& out, std::string disp, Tempo& accensione)
    {
        auto  pData = DataBase.find(disp);
        if(pData == DataBase.end())
        {
            //se cerco di impostare un timer per un dispositivo inesistente mi avverte
            out << orario << " Il dispositivo " << disp << " non esiste. Impossibile impostare il timer desiderato." << std::endl;
        }
        else
        {
            if(accensione<orario || accensione.isNull()) //Non imposto il timer se gli orari non sono validi
            {
                out << orario << " L'orario di accensione inserito e' non valido. Timer non impostato." << std::endl;
            }
            else
            {
                //Cerco un timer di spegnimento per questo dispositivo
                auto pTime = TimeLine.begin();
                Tempo temp;
                while(pTime!=TimeLine.end()) 
                {
                    if(pTime->second.second -> getNome() == disp && pTime->second.first==0)
                    {
                        temp = pTime->first;
                        break;
                    }
                    pTime++;
                };
                if(temp > accensione) //Se è presente già un timer di spegnimento successivo all'eventuale accensione non lo imposto
                {
                    out << orario << " Gia' presente un timer con spegnimento successivo all'orario di accensione. Timer non impostato." << std::endl;
                }
                else
                {
                    if(accensione == orario)
                    {
                        out << orario << " L'orario di accensione del timer di " << disp << " corrisponde con l'orario attuale. Il dispositivo verra' acceso." << std::endl;
                        setOn(out, disp);
                    }
                    else if(TimeLine.find(accensione)!=TimeLine.end())
                    {
                        out << orario << " Gia' presente un timer per lo stesso orario. Timer non impostato" << std::endl;
                    }
                    else
                    {
                        //Il timer di accensione viene sempre messo, il timer di spegnimento per i CP viene inserito in setOn
                        TimeLine.insert(std::make_pair(accensione, std::make_pair(1, pData->second)));

                        //si potrebbe dividere il messaggio per cp e manuale, dicendo per i cp l'orario in cui si spegne
                        out << orario << " Impostato un timer per il dispositivo " << disp << " dalle ore " << accensione <<std::endl;
                        
                    }
                }
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
            if(accensione<orario || accensione.isNull() || spegnimento.isNull() || accensione >= spegnimento) //Non imposto il timer se gli orari non sono validi
            {
                out << orario << " L'orario inserito non è valido. Timer non settato." << std::endl;
            }
            
            else
            {
                Dispositivo* d = p -> second;
                //I dispositivi CP non hanno timer di spegnimento, viene lanciata un'eccezione
                if(isCP(d))
                {
                    out << orario << " Il dispositivo " << disp << " è un dispositivo a ciclo prefissato. Impossibile impostare un timer di spegnimento. Nessun timer impostato." << std::endl;
                }
                else
                {
                    //Cerco un timer di spegnimento per questo dispositivo
                    auto pTime = TimeLine.begin();
                    Tempo temp;
                    while(pTime!=TimeLine.end()) 
                    {
                        if(pTime->second.second -> getNome() == disp && pTime->second.first==0)
                        {
                            temp = pTime->first;
                            break;
                        }
                        pTime++;
                    };
                    if(temp > accensione) //Se è presente già un timer di spegnimento successivo all'eventuale accensione non lo imposto
                    {
                        out << orario << " Gia' presente un timer con spegnimento successivo all'orario di accensione. Timer non impostato." << std::endl;
                    }
                    else
                    {
                        if(accensione == orario)
                        {
                            out << orario << " L'orario di accensione del timer di " << disp << " corrisponde con l'orario attuale. Il dispositivo verra' acceso." << std::endl;
                            setOn(out, disp);
                            //Impostiamo comunque un timer di spegnimento
                            TimeLine.insert(std::make_pair(spegnimento, std::make_pair(0, d)));

                            out << orario << " Impostato un timer di spegnimento per il dispositivo " << disp << " alle ore" << spegnimento << "."<<std::endl;
                        }
                        else
                        {
                            TimeLine.insert(std::make_pair(accensione, std::make_pair(1, d)));
                            TimeLine.insert(std::make_pair(spegnimento, std::make_pair(0, d)));

                            out << orario << " Impostato un timer per il dispositivo " << disp << " dalle ore " << accensione << " alle ore" << spegnimento << "."<<std::endl;
                        }
                    }
                }
            }
        }
        return out;
    }

    //Rimozione del timer
    std::ostream& SistemaDomotico::rm(std::ostream& out, std::string disp)
    {
        auto pData = DataBase.find(disp);
        if(pData == DataBase.end())
        {
            //se cerco di eliminare un timer per un dispositivo inesistente mi avverte
            out << orario << " Il dispositivo " << disp << " non esiste. Impossibile eliminare il timer desiderato." << std::endl;
        }
        else
        {
            int cont = 0;
            //In questo modo rimuove tutti i timer dei dispositivi
            for(auto pTime = TimeLine.begin(); pTime != TimeLine.end(); pTime++)
            {
                if(pTime->second.second -> getNome() == disp)
                {
                    out << orario << " Rimosso il timer alle ore" << pTime->first <<  " dal dispositivo " << disp << " ." << std::endl;
                    TimeLine.erase(pTime);
                    cont++;
                }
            }; 

            if(cont==0)
            {
                out << orario << " Il dispositivo " << disp << " non ha timer impostati." << std::endl;
            }
        }
        return out;
    }

    //setTime
    std::ostream& SistemaDomotico::setTime(std::ostream& out, Tempo& t)
    {
        if(t<orario || t.isNull() || t>Tempo(23,59))
        {
            out << orario << " orario inserito non valido." << std::endl;
        }
        else
        {
            if(t == orario)
            {
                out << orario << " orario attuale." << std::endl;
            }
            //Se arrivo alla fine del programma spengo tutti i dispositivi
            else if(t==Tempo(23,59))
            {
                fineGiornata(out);
            }
            else
            {   
                auto  p = TimeLine.begin();
                while(p != TimeLine.end() && p->first<=t)
                {
                    // Debug output to check the values
                out << "Current time: " << p->first << ", Target time: " << t << std::endl;

                    //aggiorno l'ora del sistema
                    orario = p->first;
                    Dispositivo* d = p->second.second;
                    //Se devo accendere
                    if(p->second.first==1)
                    {
                        setOn(out, d->getNome());
                    }
                    else if(p->second.first==0) //uso un else if se in futuro ci saranno altri comandi
                    {
                        setOff(out, d->getNome());
                    }         
                    TimeLine.erase(p);
                    p++;

                    // Debug output to check the values
                out << "Current time: " << p->first << ", Target time: " << t << std::endl;

                }; 
                orario = t;
                out << orario << " orario impostato." << std::endl;
            }
        }

        return out;
    }

    std::ostream& SistemaDomotico::show(std::ostream& out){
        out << orario << " show." << std::endl;
        return out;
    }

    std::ostream& SistemaDomotico::show(std::ostream& out, std::string device){
        out << orario << " show " << device << "." << std::endl;
        return out;
    }

    std::ostream& SistemaDomotico::resetTime(std::ostream& out){
        out << orario << " resetTime." << std::endl;
        return out;
    }

    void SistemaDomotico::resetTimers(){
        std::cout << orario << " resetTimers." << std::endl;
    }

    void SistemaDomotico::resetAll(){
        std::cout << orario << " resetAll." << std::endl;
    }

/* FUNZIONI DI SUPPORTO */
    //Funzione per il sovraccarico
    void SistemaDomotico::sovraccarico(std::ostream& out)
    {
        while(potenzaResidua<0)
        {
            std::string name = OrdineAccensione.top();
            Dispositivo* d = DataBase.find(name)->second;
            if(d->getStato()==1)
            {
                setOff(out,name);
            }
            OrdineAccensione.pop();
        }
    }
    //DA RIVEDERE
    //Funzione per la fine della giornata
    void SistemaDomotico::fineGiornata(std::ostream& out)
    {
        while(!OrdineAccensione.empty())
        {
            std::string name = OrdineAccensione.top();
            Dispositivo* d = DataBase.find(name)->second;
            if(d->getStato()==1)
            {
                setOff(out,name);
            }
            OrdineAccensione.pop();
        }
    }

/* HELPER FUNCTION */

    //Funzioni per determinare il tipo di dispositivo
    bool isManuale(Dispositivo* d)
    {
        return d->getID()%2==0;
    }
    
    bool isCP(Dispositivo* d)
    {
        return d->getID()%2==1;
    }