#include "SistemaDomotico.h"

/*COSTRUTTORI*/    

    //Costruttore parametrico
    SistemaDomotico::SistemaDomotico(Logger& log) : orario{0,0}, size{10}, potenzaResidua{limitePotenza}, logger{log}
    {
        //Grazie all'utilizzo di smart pointer la gestione della memoria è automatica

        //Creazione dei dispositivi manuali predefiniti
        std::shared_ptr<Dispositivo> Frigorifero = std::make_shared<DispManuale>("Frigorifero", DispManuale::DispDomotico::Frigorifero);
        
        std::shared_ptr<Dispositivo> ImpiantoFotovoltaico = std::make_shared<DispManuale>("Impianto fotovoltaico", DispManuale::DispDomotico::Impianto_Fotovoltaico);
        
        std::shared_ptr<Dispositivo> Pompa_di_calore_termostato = std::make_shared<DispManuale>("Pompa di calore + termostato", DispManuale::DispDomotico::Pompa_di_calore_termostato);
        
        std::shared_ptr<Dispositivo> Scaldabagno = std::make_shared<DispManuale>("Scaldabagno", DispManuale::DispDomotico::Scaldabagno);

        // Creazione dei dispositivi a ciclo prefissato predefiniti
        std::shared_ptr<Dispositivo> Asciugatrice = std::make_shared<DispCicloPrefissato>("Asciugatrice", DispCicloPrefissato::DispDomotico::Asciugatrice);
        
        std::shared_ptr<Dispositivo> Forno_a_microonde = std::make_shared<DispCicloPrefissato>("Forno a microonde", DispCicloPrefissato::DispDomotico::Forno_a_microonde);
        
        std::shared_ptr<Dispositivo> Lavastoviglie = std::make_shared<DispCicloPrefissato>("Lavastoviglie", DispCicloPrefissato::DispDomotico::Lavastoviglie);
        
        std::shared_ptr<Dispositivo> Lavatrice = std::make_shared<DispCicloPrefissato>("Lavatrice", DispCicloPrefissato::DispDomotico::Lavatrice);
        
        std::shared_ptr<Dispositivo> Tapparelle_elettriche = std::make_shared<DispCicloPrefissato>("Tapparelle elettriche", DispCicloPrefissato::DispDomotico::Tapparelle_elettriche);
        
        std::shared_ptr<Dispositivo> Televisore = std::make_shared<DispCicloPrefissato>("Televisore", DispCicloPrefissato::DispDomotico::Televisore);

        // Creazione del DataBase
        DataBase.insert({Frigorifero->getNome(), Frigorifero});
        DataBase.insert({ImpiantoFotovoltaico->getNome(), ImpiantoFotovoltaico});
        DataBase.insert({Pompa_di_calore_termostato->getNome(), Pompa_di_calore_termostato});
        DataBase.insert({Scaldabagno->getNome(), Scaldabagno});
        DataBase.insert({Asciugatrice->getNome(), Asciugatrice});
        DataBase.insert({Forno_a_microonde->getNome(), Forno_a_microonde});
        DataBase.insert({Lavastoviglie->getNome(), Lavastoviglie});
        DataBase.insert({Lavatrice->getNome(), Lavatrice});
        DataBase.insert({Tapparelle_elettriche->getNome(), Tapparelle_elettriche});
        DataBase.insert({Televisore->getNome(), Televisore});


    }

/*FUNZIONI MEMBRO*/

    //Getter
    int SistemaDomotico::getSize() const {return size;}
    double SistemaDomotico::getPotenzaResidua() const {return potenzaResidua;}
    double SistemaDomotico::getLimitePotenza() const {return limitePotenza;}
    Logger& SistemaDomotico::getLogger() const {return logger;}

    //Metodi per aggiunta di un dispositivo
    void SistemaDomotico::add(std::string disp, DispCicloPrefissato::DispDomotico t)
    {   
        //Controllo se il dispositivo è già presente
        auto p = DataBase.find(disp);
        if(p != DataBase.end())
        {
            logger.log(orario.toString() + " " + disp + " gia' presente nel Sistema Domotico.\n");
        }
        else
        {
            std::shared_ptr<Dispositivo> d = std::make_shared<DispCicloPrefissato>(disp, t);
            DataBase.insert({d->getNome(), d});
            size ++;
            logger.log(orario.toString() + " " + disp + " aggiunto al Sistema Domotico.\n");
        }
        debugDatabase();
    }

    void SistemaDomotico::add(std::string disp, DispManuale::DispDomotico t)
    {
        //Controllo se il dispositivo è già presente
        auto p = DataBase.find(disp);
        if(p != DataBase.end())
        {
            logger.log(orario.toString() + " " + disp + " gia' presente nel Sistema Domotico.\n");
        }
        else
        {
            std::shared_ptr<Dispositivo> d = std::make_shared<DispManuale>(disp, t);
            DataBase.insert({d->getNome(), d});
            size ++;
            logger.log(orario.toString() + " " + disp + " aggiunto al Sistema Domotico.\n");
        }
        debugDatabase();
    }

    //Metodo per la rimozione di un dispositivo
    void SistemaDomotico::erase(std::string disp)
    {
        if(size==0)
        {
           logger.log(orario.toString() + " Il Sistema Domotico e' vuoto. Impossibile rimuovere ulteriori dispositivi.\n");
        }
        else
        {
            //Controllo se il dispositivo è presente
            auto p = DataBase.find(disp);
            if(p == DataBase.end())
            {
                logger.log(orario.toString() + " " + disp + " non presente nel Sistema Domotico.\n");
            }
            else
            {
                //Controllo se il dispositivo è acceso, lo rimuovo solo se spento
                if(p->second->getStato()==1)
                {
                    logger.log(orario.toString() + " " + disp + " acceso. Impossibile rimuovere il dispositivo.\n");
                }
                else
                {
                    //Rimuovo dalla timeline eventuali timer di accensione e spegnimento
                    rm(disp);
                    DataBase.erase(disp);
                    size --;
                    logger.log(orario.toString() + " " + disp + " rimosso dal Sistema Domotico.\n");
                }
            }
        }
        debugDatabase();
    }

    //setOff
    void SistemaDomotico::setOff(std::string disp)
    {
        auto pData = DataBase.find(disp);
        if(pData == DataBase.end())
        {
            logger.log(orario.toString() + " " + disp + " non presente nel Sistema Domotico.\n");
        }
        else
        {
            std::shared_ptr<Dispositivo> d = pData->second;
            if(pData->second->getStato()==0)
            {
                logger.log(orario.toString() + " " + disp + " gia' spento.\n");
            }
            else
            {
                d->setStato(0); //spegniamo il dispositivo
                d->setSpegnimento(orario); //indichiamo l'ora di spegnimento
                potenzaResidua -= pData->second->getPotenza(); //aggiorniamo la potenza residua del sistema
                //Rimuovo eventuali timer di spegnimento se ho spento anticipatamente il dispositivo
                for(auto pTime = TimeLine.begin(); pTime != TimeLine.end(); pTime++)
                {
                    //Se incontro per primo un timer di accensione non devo più togliere nulla
                    if(pTime->second.second->getNome()==disp && pTime->second.first==1)
                    {
                        break;
                    }
                    if(pTime->second.second->getNome()==disp && pTime->second.first==0)
                    {
                        TimeLine.erase(pTime);
                        break; //tolgo solo il primo di spegnimento
                    }
                };
                //Mostriamo a schermo il messaggio
                logger.log(orario.toString() + " Il dispositivo " + disp + " si e' spento.\n");

                if(potenzaResidua<0)
                {
                    logger.log(orario.toString() + " Il sistema ha superato il limite di potenza. Verranno spenti dei dispositivi.\n");
                    sovraccarico();
                }
            }
        }
    }

    //setOffbyTimer
    void SistemaDomotico::setOffbyTimer(std::string disp)
    {
        //Nessun controllo su disp, controllo già effettuato da setTimer
        auto pData = DataBase.find(disp);
        //Condizione tenuta solo per precauzione VA TOLTA ALLA FINE
if(pData->second->getStato()==0)
{
    logger.log(orario.toString() + " " + disp + " gia' spento. QUESTO NON DOVREBBE ACCADERE, CONTROLLARE CHE PROBLEMI CI SONO\n");
}
        else
        {
            std::shared_ptr<Dispositivo> d = pData->second;
            d -> setStato(0); //spegniamo il dispositivo
            d->setSpegnimento(orario); //indichiamo l'ora di spegnimento
            //Non serve rimuovere eventuali timer di spegnimento
            //Mostriamo a schermo il messaggio
            logger.log(orario.toString() + " Il dispositivo " + disp + " si e' spento.\n");
            potenzaResidua -= pData -> second -> getPotenza(); //aggiorniamo la potenza residua del sistema

            //Non rimuovo dallo stack il dispositivo, in caso di sovraccarico controllerò se è ancora acceso
            if(potenzaResidua<0)
            {
                logger.log(orario.toString() + " Il sistema ha superato il limite di potenza. Verranno spenti dei dispositivi.\n");
                sovraccarico();
            }
        }
    }

    //setOn
    void SistemaDomotico::setOn(std::string disp)
    {
        //Se il dispositivo non è presente nel DataBase non faccio nulla
        auto pData = DataBase.find(disp);
        if(pData==DataBase.end())
        {
            logger.log(orario.toString() + " " + disp + " non presente nel Sistema Domotico.\n");
        }
        else
        {
            std::shared_ptr<Dispositivo> d = pData->second;
            //Se il dispositivo è gia acceso non faccio nulla
            if(pData->second->getStato()==1)
            {
                logger.log(orario.toString() + " " + disp + " gia' acceso.\n");
            }
            else
            {
                //Se la sua accensione comporterebbe un superamento della potenza non lo accendo
                if(potenzaResidua + d->getPotenza() < 0)
                {
                    logger.log(orario.toString() + " " + disp + " non acceso. Limite di potenza raggiunto.\n");
                    //Non devo rimuovere alcun timer in quanto questo comando viene chiamato dall'utente
                }
                else
                {
                    d-> setStato(1); //accendiamo il dispositivo
                    potenzaResidua += d -> getPotenza(); //aggiorniamo la potenza residua del sistema
                    d->setAccensione(orario); //indichiamo l'ora di accensione

                    //Mettiamo nello stack l'accensione in modo da poter gestire la politca di spegnimento
                    OrdineAccensione.push(disp);
                    //Mostriamo a schermo il messaggio
                    logger.log(orario.toString() + " Il dispositivo " + disp + " si e' acceso.\n");

                    if(isCP(d))
                    {
                        //Se è CP metto un timer di spegnimento, in caso di ulteriori timer di accensione questo verrà ignorato
                        std::shared_ptr<DispCicloPrefissato> cp = std::dynamic_pointer_cast<DispCicloPrefissato>(d);
                        Tempo spegnimento = orario + cp->getDurata();
                        TimeLine.insert(std::make_pair(spegnimento, std::make_pair(0, d)));
                    }
                }
            }
        }

        
    }

    //setOnbyTimer
    void SistemaDomotico::setOnbyTimer(std::string disp)
    {
        //Il controllo su disp è già stato fatto da setTimer
        auto pData = DataBase.find(disp);
        std::shared_ptr<Dispositivo> d = pData->second;

        //Se il dispositivo è gia acceso ignoro questo timer
        if(pData-> second -> getStato()==1)
        {
            if(isCP(d))
            {
                int count = 0;
                //Rimuovo il secondo timer di spegnimento, il primo sicuramente esiste e diventa prioritario rispetto al secondo
                for(auto pTime = TimeLine.begin(); pTime != TimeLine.end() && count <2; pTime++)
                {
                    if(pTime->second.second -> getNome() == disp && pTime->second.first==0)
                    {
                        if(count==1)
                        {
                            TimeLine.erase(pTime);
                            break; //tolgo solo il secondo di spegnimento
                        }
                        count++;
                    }
                };
                logger.log(orario.toString() + " " + disp + " gia' acceso. Il timer di spegnimento connesso e' stato rimosso.\n");
            }
            else
            {
                logger.log(orario.toString() + " " + disp + " gia' acceso. Timer di accensione ignorato, il timer di spegnimento verrà applicato.\n");
            }
        }
        else
        {
            //Se la sua accensione comporterebbe un superamento della potenza non lo accendo
            if(potenzaResidua + pData->second->getPotenza() > limitePotenza)
            {
                //Rimuovo eventuali timer di spegnimento in quanto l'accensione è stata chiamata da un timer
                for(auto pTime = TimeLine.begin(); pTime != TimeLine.end(); pTime++)
                {
                    if(pTime->second.second -> getNome() == disp && pTime->second.first==0)
                    {
                        TimeLine.erase(pTime);
                    }
                    break; //tolgo solo il primo di spegnimento, in un momento successivo magari riuscirò ad accenderlo
                };

                logger.log(orario.toString() + " " + disp + " non acceso. Limite di potenza raggiunto.\n");
            }
            else
            {
                d-> setStato(1); //accendiamo il dispositivo
                potenzaResidua += d -> getPotenza(); //aggiorniamo la potenza residua del sistema
                d->setAccensione(orario); //indichiamo l'ora di accensione

                //Non inseriamo nella timeline lo spegnimento in quanto è già presente
                //Mettiamo nello stack l'accensione in modo da poter gestire la politca di spegnimento
                OrdineAccensione.push(disp);
                //Mostriamo a schermo il messaggio
                logger.log(orario.toString() + " Il dispositivo " + disp + " si e' acceso.\n");
            }
        }


        
    }

    //setTimer
    void SistemaDomotico::setTimer(std::string disp, Tempo& accensione)
    {
        auto  pData = DataBase.find(disp);
        if(pData == DataBase.end())
        {
            //se cerco di impostare un timer per un dispositivo inesistente mi avverte
            logger.log(orario.toString() + " Il dispositivo " + disp + " non esiste. Impossibile impostare il timer desiderato.\n");
        }
        else
        {
            if(accensione<orario || accensione.isNull()) //Non imposto il timer se gli orari non sono validi
            {
                logger.log(orario.toString() + " L'orario di accensione inserito e' non valido. Timer non impostato.\n");
            }
            else
            {
                if(TimeLine.find(accensione)!=TimeLine.end() && TimeLine.find(accensione)->second.second->getNome()==disp) //Se è già presente un timer per lo stesso orario non lo imposto
                {
                    logger.log(orario.toString() + " Gia' presente un timer per lo stesso orario. Timer non impostato.\n");
                }
                else
                {
                    std::shared_ptr<Dispositivo> d = pData->second;

                    if(isCP(d))
                    {
                        Tempo spegnimento = accensione + std::dynamic_pointer_cast<DispCicloPrefissato>(d)->getDurata();
                        if(spegnimento < accensione)
                        {
                            spegnimento.setNull(); //se sforiamo la mezzanotte non impostiamo il timer di spegnimento
                        }
                        bool val = isTimerValido(accensione, spegnimento, disp, d);

                        if(accensione == orario && val==true)
                        {
                            logger.log(orario.toString() + " L'orario di accensione del timer di " + disp + " corrisponde con l'orario attuale. Il dispositivo verra' acceso.\n");
                            setOn(disp);
                            //Impostiamo comunque un timer di spegnimento
                            TimeLine.insert(std::make_pair(spegnimento, std::make_pair(0, d)));

                            logger.log(orario.toString() + " Impostato un timer di spegnimento per il dispositivo " + disp + " alle ore " + spegnimento.toString() + ".\n");
                        }
                        else
                        {
                            if(val==true)
                            {
                                TimeLine.insert(std::make_pair(accensione, std::make_pair(1, d)));
                                TimeLine.insert(std::make_pair(spegnimento, std::make_pair(0, d)));

                                logger.log(orario.toString() + " Impostato un timer per il dispositivo " + disp + " dalle ore " + accensione.toString() + " alle ore " + spegnimento.toString() + ".\n");
                            }
                            else
                            {
                                logger.log(orario.toString() + " Il timer inserito non e' valido. Timer non impostato.\n");
                            }
                        }

                    }
                    else
                    {
                        Tempo spegnimento;
                        spegnimento.setNull();
                        bool val = isTimerValido(accensione, spegnimento, disp, d);

                        if(accensione == orario && val==true)
                        {
                            logger.log(orario.toString() + " L'orario di accensione del timer di " + disp + " corrisponde con l'orario attuale. Il dispositivo verra' acceso.\n");
                            setOn(disp);
                        }
                        else
                        {
                            if(val==true)
                            {
                                TimeLine.insert(std::make_pair(accensione, std::make_pair(1, d)));
                                logger.log(orario.toString() + " Impostato un timer per il dispositivo " + disp + " dalle ore " + accensione.toString() + ".\n");
                            }
                            else
                            {
                                logger.log(orario.toString() + " Il timer inserito non e' valido. Timer non impostato.\n");
                            }
                        }
                    }
                }
            }
        }
        
    }

    //setTimer a due parametri
    void SistemaDomotico::setTimer(std::string disp, Tempo& accensione, Tempo& spegnimento)
    {
        auto p = DataBase.find(disp);
        if(p == DataBase.end())
        {
            //se cerco di impostare un timer per un dispositivo inesistente mi avverte
            logger.log(orario.toString() + " Il dispositivo " + disp + " non esiste. Impossibile impostare il timer desiderato.\n");
        }
        else
        {
            if(accensione<orario || accensione.isNull() || spegnimento.isNull() || accensione >= spegnimento) //Non imposto il timer se gli orari non sono validi
            {
                logger.log(orario.toString() + " L'orario inserito non e' valido. Timer non settato.\n");
            }

            else
            {
                std::shared_ptr<Dispositivo> d = p->second;
                //I dispositivi CP non hanno timer di spegnimento, viene lanciata un'eccezione
                if(isCP(d))
                {
                    logger.log(orario.toString() + " Il dispositivo " + disp + " e' un dispositivo a ciclo prefissato. Impossibile impostare un timer di spegnimento. Nessun timer impostato.\n");
                }
                else
                {
                    //Controllo se il timer è valido
                    bool val = isTimerValido(accensione, spegnimento, disp, d);
                    if(val==true)
                    {
                        if(accensione == orario)
                        {
                            logger.log(orario.toString() + " L'orario di accensione del timer di " + disp + " corrisponde con l'orario attuale. Il dispositivo verra' acceso.\n");
                            setOn(disp);
                            //Impostiamo comunque un timer di spegnimento
                            TimeLine.insert(std::make_pair(spegnimento, std::make_pair(0, d)));

                            logger.log(orario.toString() + " Impostato un timer di spegnimento per il dispositivo " + disp + " alle ore " + spegnimento.toString() + ".\n");
                        }
                        else
                        {
                            TimeLine.insert(std::make_pair(accensione, std::make_pair(1, d)));
                            TimeLine.insert(std::make_pair(spegnimento, std::make_pair(0, d)));

                            logger.log(orario.toString() + " Impostato un timer per il dispositivo " + disp + " dalle ore " + accensione.toString() + " alle ore " + spegnimento.toString() + ".\n");
                        }
                    }
                    else
                    {
                        logger.log(orario.toString() + " Il timer inserito non e' valido. Timer non impostato.\n");
                    }
                }
            }
        }
        
    }

    //Rimozione del timer
    void SistemaDomotico::rm(std::string disp)
    {
        auto pData = DataBase.find(disp);
        if(pData == DataBase.end())
        {
            //se cerco di eliminare un timer per un dispositivo inesistente mi avverte
            logger.log(orario.toString() + " Il dispositivo " + disp + " non esiste. Impossibile eliminare il timer desiderato.\n");
        }
        else
        {
            int cont = 0;
            //In questo modo rimuove tutti i timer dei dispositivi
            auto pTime = TimeLine.begin();
            while(pTime != TimeLine.end())
            {
                if(pTime->second.second -> getNome() == disp)
                {
                    logger.log(orario.toString() + " Rimosso il timer alle ore " + pTime->first.toString() +  " dal dispositivo " + disp + " .\n");
                    TimeLine.erase(pTime);
                    cont++;
                }
                else
                {
                    pTime++;
                }
            };

            if(cont==0)
            {
                logger.log(orario.toString() + " Il dispositivo " + disp + " non ha timer impostati.\n");
            }
        }
        
    }

    //setTime
    void SistemaDomotico::setTime(Tempo& t)
    {
        if(t<orario || t.isNull() || t>Tempo(23,59))
        {
            logger.log(orario.toString() + " orario inserito non valido.\n");
        }
        else
        {
            if(t == orario)
            {
                logger.log(orario.toString() + " orario attuale.\n");
            }
            else
            {
                auto  p = TimeLine.begin();
                while(p != TimeLine.end() && p->first<=t)
                {
                    //aggiorno l'ora del sistema
                    orario = p->first;
                    std::shared_ptr<Dispositivo> d = p->second.second;
                    //Se devo accendere
                    if(p->second.first==1)
                    {
                        setOnbyTimer(d->getNome());
                    }
                    else if(p->second.first==0) //uso un else if se in futuro ci saranno altri comandi
                    {
                        setOffbyTimer(d->getNome());
                    }
                    //Serve riassegnare p altrimenti cancellando un elemento si perde il riferimento
                    p = TimeLine.erase(p);

                };
                orario = t;
                logger.log(orario.toString() + " Orario impostato.\n");

                //Se arrivo alla fine del programma lancio un'eccezione per non permettere ulteriori operazioni
                if(orario==Tempo(23,59))
                {
                    throw std::runtime_error("Fine programma");
                }
            }
        }

        
    }

    void SistemaDomotico::show(){

        double produzione = 0;
        double consumo = 0;

        //Calcolo nel sistema la produzione e il consumo attuale totale
        for(auto& elemento : DataBase) {
            if(elemento.second->consumoEnergetico(orario) > 0) {
                //Consumo > 0
                consumo += elemento.second->consumoEnergetico(orario);
            } else {
                //Consumo < 0 (aka Produzione)
                produzione += elemento.second->consumoEnergetico(orario);
            }
        }

        logger.log(orario.toString() + " Attualmente il sistema ha prodotto " + std::to_string(produzione) + " kWh e consumato " + std::to_string(consumo) + " kWh. Nello specifico:\n");

        //Mostro i singoli dispositivi
        for(auto& elemento : DataBase) {
            logger.log("\t- Il dispositivo " + elemento.first + " ha ");
            if(elemento.second->consumoEnergetico(orario) >= 0) {
                logger.log("consumato ");
            } else {
                logger.log("prodotto ");
            }
            logger.log( std::to_string(fabs(elemento.second->consumoEnergetico(orario))) + " kWh\n");
        }


        
    }

    void SistemaDomotico::show(std::string disp)
    {
        auto p = DataBase.find(disp);
        if(p == DataBase.end())
        {
            //se cerco di mostrare il consumo di un dispositivo inesistente mi avverte
            logger.log(orario.toString() + " Il dispositivo " + disp + " non esiste. Impossibile mostrare il relativo consumo.\n");
        }
        else
        {
            logger.log(orario.toString() + " Il dispositivo " + disp + " ha consumato " + std::to_string(p->second->consumoEnergetico(orario)) + " kWh\n");
        }
        
    }

    void SistemaDomotico::resetTime(){

        logger.log(orario.toString() + " Il tempo e' stato resettato e tutti i dispositivi sono stati spenti.\n");

        /*resetTime:
            - riporta l'orario a 00:00
            - riporta i dispositivi alle condizioni iniziali
            - mantiene i timer
        */

        //Orario a 00:00
        orario = Tempo(0,0);

        //Condizioni iniziali (tutti i dispositivi spenti)
        for(auto& elemento : DataBase) {
            elemento.second->reset();

            //Controllo nella TimeLine se, per caso, ci sono dei timer di spegnimento
            for(auto pTime = TimeLine.begin(); pTime != TimeLine.end(); pTime++) {
                if(pTime->second.second -> getNome() == elemento.first && pTime->second.first==0)
                {
                    TimeLine.erase(pTime);
                }
                break; //tolgo solo il primo di spegnimento
            };
        }

        logger.log(orario.toString() + " Orario impostato.\n");

        
    }

    void SistemaDomotico::resetTimers(){
        logger.log(orario.toString() + " I timer sono stati resettati.\n");

        /*resetTimers:
            - rimuove tutti i timer dai dispositivi
            - non modifica lo stato dei dispositivi
            - se un timer è in corso di svolgimento in un Dispositivo CP, DEVO mantenere l'orario di termine (per mantenere il ciclo prefissato -> se cancello tutta la timeline il dispositivo rimane acceso per sempre)
        */

        //Multimap temporanea per conservare i timer di spegnimento da mantenere
        std::multimap<Tempo, std::pair<int, std::shared_ptr<Dispositivo>>> SoloSpegnimento;

        //Set per tracciare quali dispositivi CP sono già stati elaborati
        std::set<std::shared_ptr<Dispositivo>> dispositiviGestiti;

        for (auto it = TimeLine.begin(); it != TimeLine.end(); ++it) {
            //Mantieni solo i timer di spegnimento per dispositivi CP
            if (isCP(it->second.second) && it->second.first == 0) {
                // Controlla se il dispositivo è già stato gestito
                if (dispositiviGestiti.find(it->second.second) == dispositiviGestiti.end()) {
                    // Aggiungi il timer alla nuova multimap
                    SoloSpegnimento.insert(*it);
                    dispositiviGestiti.insert(it->second.second); // Segna il dispositivo come gestito
                }
            }
        }

        // Sostituisci la vecchia TimeLine con SoloSpegnimento
        TimeLine = std::move(SoloSpegnimento);

        
    }

    void SistemaDomotico::resetAll(){

        logger.log(orario.toString() + " Il tempo e' stato resettato, tutti i dispositivi sono stati spenti e i timer rimossi.\n");

        /*resetAll
            - riporta l'orario a 00:00
            - riporta i dispositivi alle condizioni iniziali
            - i timer vengono rimossi
        */

        //Orario a 00:00
        orario = Tempo(0,0);

        //Condizioni iniziali (tutti i dispositivi spenti)
        for(auto& elemento : DataBase) {
            elemento.second->reset();
        }

        //Rimuove i timer (svuoto la timeline)
        TimeLine.clear();

        logger.log(orario.toString() + " Orario impostato.\n");

        
    }

/* FUNZIONI DI SUPPORTO */
    //Funzione per il sovraccarico
    void SistemaDomotico::sovraccarico()
    {
        while(potenzaResidua<0)
        {
            std::string name = OrdineAccensione.top();

            //Controllo che il dispositivo sia ancora presente e non sia stato eliminato
            if(DataBase.find(name)!=DataBase.end())
            {
                std::shared_ptr<Dispositivo> d = DataBase.find(name)->second;
                if(d->getStato()==1)
                {
                    setOff(name);
                }
            }
            OrdineAccensione.pop();
        }
    }

/* HELPER FUNCTION */

    //Funzioni per determinare il tipo di dispositivo
    bool isManuale(std::shared_ptr<Dispositivo> d)
    {
        return d->getID()%2==0;
    }

    bool isCP(std::shared_ptr<Dispositivo> d)
    {
        return d->getID()%2==1;
    }

    //Funzione helper per setTimer

    bool SistemaDomotico::isTimerValido(Tempo& accensione, Tempo& spegnimento, std::string disp, std::shared_ptr<Dispositivo> d)
    {
        //Non ho diviso quanto segue in due funzioni per evitare la copia dei contenitori

        //Trovo tutti i timer di spegnimento per un dispositivo, che sono chiaramente già in ordine di orario
        //p è un iteratore che punta al primo timer di spegnimento per il dispositivo
        auto p = TimeLine.begin();
        std::queue<std::unique_ptr<Tempo>> tempiSpegnimento;
        while(p!=TimeLine.end())
        {
            if(p->second.second->getNome() == disp && p->second.first==0)
            {
                tempiSpegnimento.push(std::make_unique<Tempo>(p->first));
            }
            p++;
        };

        //Trovo tutti i timer di accensione per un dispositivo, che sono chiaramente già in ordine di orario
        //p è un iteratore che punta al primo timer di spegnimento per il dispositivo

        p = TimeLine.begin();
        std::queue<std::unique_ptr<Tempo>> tempiAccensione;
        while(p!=TimeLine.end())
        {
            if(p->second.second->getNome() == disp && p->second.first==1)
            {
                tempiAccensione.push(std::make_unique<Tempo>(p->first));
            }
            p++;
        };

        if(d->getStato()==0 && tempiSpegnimento.empty() && tempiAccensione.empty())
        {
            return true;
        }
        else
        {

            if(isCP(d))
            {
                if(spegnimento.isNull()) //Necessario nel caso in cui lo spegnimento superi la mezzanotte
                {
                    int k = tempiSpegnimento.size();
                    for(int j = 0; j<k; j++)
                    {
                        if(accensione < *tempiSpegnimento.front())
                        {
                            return false;
                        }
                        tempiSpegnimento.pop();
                    }
                    return true;
                }
                if(d->getStato()==1)
                {
                    //Se il dispositivo è acceso controllo a parte il primo timer di spegnimento
                    if(accensione < *tempiSpegnimento.front())
                    {
                        return false;
                    }
                    tempiSpegnimento.pop(); //lo tolgo comunque in quanto ho già considerato il primo

                }
                                if(tempiAccensione.size()!=tempiSpegnimento.size())
                                {
                                    throw std::runtime_error("Errore nella gestione dei timer."); //TOGLIERE DOPO MA NON DOVREBBE ACCADERE
                                    //VA GESTITO IL FINE GIORNATA IN CUI NON CI SONO SPEGNIMENTI
                                }
                    int i = tempiAccensione.size(); //timer di accensione e spegnimento sono in numero uguale

                for(int j = 0; j<i; j++)
                {
                    if( (accensione < *tempiAccensione.front() && spegnimento < *tempiAccensione.front()) || (accensione > *tempiSpegnimento.front() && spegnimento > *tempiSpegnimento.front()) )
                    {
                        tempiAccensione.pop();
                        tempiSpegnimento.pop();
                    }
                    else
                    {
                        return false;
                    }
                }
                return true;
            }
            else if(isManuale(d)) //Scritto così per maggiore chiarezza
            {
                if(d->getStato()==1)
                {
                    //Se il dispositivo è acceso controllo a parte il primo timer di spegnimento
                    if(!tempiSpegnimento.empty() && accensione < *tempiSpegnimento.front())
                    {
                        return false;
                    }

                    if(tempiSpegnimento.empty())
                    {
                        return false;
                    }
                }

                if(spegnimento.isNull()) //Necessario in quanto questo metodo viene usato da entrambi i setTimer
                {
                    if(tempiSpegnimento.empty()) //Se non ci sono timer di spegnimento quello  è un timer che dura tutta la giornata, verifico non lo intrecci
                    {
                        if(accensione < *tempiAccensione.front())
                        {
                            return false;
                        }
                        else
                        {
                            return true;
                        }
                    }
                    //Altrimenti verifico che il timer che voglio inserire, che è un timer di sola accensione, non vada a intrecciarsi con altri timer
                    int i = tempiSpegnimento.size();
                    for(int j = 0;j<i;j++)
                    {
                        if(accensione < *tempiSpegnimento.front())
                        {
                            return false;
                        }
                        tempiSpegnimento.pop();
                    }
                }
                else
                {
                    int j = tempiSpegnimento.size();
                    for(int k = 0; k<j; k++)
                    {
                        if( (accensione < *tempiAccensione.front() && spegnimento < *tempiAccensione.front()) || (accensione > *tempiSpegnimento.front() && spegnimento > *tempiAccensione.front()) )
                        {
                            tempiAccensione.pop();
                            tempiSpegnimento.pop();
                        }
                        else
                        {
                            return false;
                        }
                    }
                    //Nel caso ci sia un ultimo timer di accensione lo verifico a parte successivamente
                    if(!tempiAccensione.empty())
                    {
                        if(accensione < *tempiAccensione.front())
                        {
                            return false;
                        }
                        return true;
                    }
                    else
                    {
                        return true;
                    }
                }
            }
        }
        throw std::runtime_error("Situazione non considerata."); //TOGLIERE DOPO MA NON DOVREBBE ACCADERE
    }

    //Funzione di stampa della TimeLine
    void SistemaDomotico::printTimeLine()
    {
        logger.log("TimeLine:\n");
        for(auto p = TimeLine.begin(); p != TimeLine.end(); p++)
        {
            logger.log(p->first.toString() + " " + std::to_string(p->second.first) + p->second.second->getNome() + "\n");
        }
        
    }

    void SistemaDomotico::debugDatabase() {
        if (DataBase.empty()) {
            logger.log("DEBUG: Il DataBase e' vuoto.\n");
        } else {
            logger.log("DEBUG: Contenuto del DataBase:\n");
            for (const auto& entry : DataBase) {
                // Ottieni la chiave (nome del dispositivo) e il puntatore condiviso all'oggetto
                const std::string& nome = entry.first;
                const std::shared_ptr<Dispositivo>& dispositivo = entry.second;

                // Stampa il nome e altre informazioni
                logger.log("- Nome: " + nome
                    + ", Stato: " + (dispositivo->getStato() ? "Acceso" : "Spento")
                    + ", Potenza: " + std::to_string(dispositivo->getPotenza())
                    + "\n");
            }
        }

        
    }

    void SistemaDomotico::printTime() {
        logger.log(orario);
    }