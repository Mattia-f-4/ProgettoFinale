#include "Tempo.h"
#include "DispManuale.h"
#include "DispCicloPrefissato.h"
#include "SistemaDomotico.h"
#include <iostream>
#include <string>
#include <map>

/* ENUM CLASS */

// Enum class per i comandi
enum class Commands {
    set,
    rm,
    show,
    reset,
    add,
    erase,
    exit,
    unknown
};

/* MAPPE */

// Mappa per associare comando a enum class comandi
static std::map<std::string, Commands> mapCommands = {
    {"set", Commands::set},
    {"rm", Commands::rm},
    {"show", Commands::show},
    {"reset", Commands::reset},
    {"add", Commands::add},
    {"erase", Commands::erase},
    {"exit", Commands::exit}
};

/* FUNZIONI DI CONTROLLO */

// Funzione che controlla che il nome del dispositivo non abbia ':'
bool check_name(std::string device_name) {
    if(device_name.find(':') != std::string::npos)
        return false;
    return true;
}

// Funzione che controlla la correttezza del comando
bool check_command(Commands command, std::string input) {
    int pos;
    std::string pattern;
    std::string delimiter = " ";

    switch(command) {
        case Commands::set:
             pos = input.find_last_of(delimiter); // Posizione ultimo pattern
             pattern = input.substr(pos + 1); // Ultimo pattern
             // Se ultimo pattern non è un orario, o 'on' o 'off'
             if(pattern.find(':') == std::string::npos && pattern != "on" && pattern != "off") {
                return false;
             // Altrimenti se è un orario
             } else if(pattern.find(':') != std::string::npos) {
                input.erase(pos); // Cancello ultimo pattern
                pos = input.find_last_of(delimiter); // Posizione ultimo pattern
                pattern = input.substr(pos + 1); // Ultimo pattern

                pos = input.find(delimiter); // Posizione secondo pattern
                // Se comando set time e ci sono troppi pattern
                if(input.substr(0, pos) == "time" && input != pattern)
                    return false;
             }
            break;
        case Commands::reset:
            // Se pattern non è 'time', 'timers' o 'all'
            if(input != "time" && input != "timers" && input != "all")
                return false;
            break;
        case Commands::add:
            // Se oltre ad 'add' ci soo altri pattern
            if(input != "add")
                return false;
            break;
        case Commands::erase:
            // Se oltre a 'erase' non ci sono altri pattern (nome dispositivo)
            if(input == "erase")
                return false;
            break;
        case Commands::exit:
            // Se oltre a 'exit' ci sono altri pattern
            if(input != "exit")
                return false;
            break;
    }
    return true;
}

/* FUNZIONI PER SISTEMA DOMOTICO*/

// Funzione che chiama setOn di SistemaDomotico
void set_device_on(SistemaDomotico& sistemaDomotico, std::string device) {
    sistemaDomotico.setOn(device);
}

// Funzione che chiama setOff di SistemaDomotico
void set_device_off(SistemaDomotico& sistemaDomotico, std::string device) {
    sistemaDomotico.setOff(device);
}

// Funzione che chiama setTimer di SistemaDomotico con solo orarioAccensione
void set_device_start(SistemaDomotico& sistemaDomotico, std::string device, std::string start) {
    // Provo a creare un oggetto tempo con la stringa data
    // Se la conversione in int fallisce o il numero è fuori dal range tempo, gestisco l'eccezione
    try {
        Tempo t_start(start);
        sistemaDomotico.setTimer(device, t_start);
    } catch(std::invalid_argument& e) {
        sistemaDomotico.printTime();
        sistemaDomotico.getLogger().log(" ERROR: Tempo non valido\n");
    } catch(std::out_of_range& e) {
        sistemaDomotico.printTime();
        sistemaDomotico.getLogger().log(" ERROR: Tempo non valido\n");
    }
}

// Funzione che chiama setTimer di SistemaDomotico con orarioAccensione e orarioSpegnimento
void set_device_start_stop(SistemaDomotico& sistemaDomotico, std::string device, std::string start, std::string stop) {
    // Provo a creare due oggetti tempo con le stringhe date
    // Se la conversione in int fallisce o il numero è fuori dal range tempo, gestisco l'eccezione
    try {
        Tempo t_start(start);
        Tempo t_stop(stop);
        sistemaDomotico.setTimer(device, t_start, t_stop);
    } catch(std::invalid_argument& e) {
        sistemaDomotico.printTime();
        sistemaDomotico.getLogger().log(" ERROR: Tempo non valido\n");
    } catch(std::out_of_range& e) {
        sistemaDomotico.printTime();
        sistemaDomotico.getLogger().log(" ERROR: Tempo non valido\n");
    }
}

// Funzione che chiama rm di SistemaDomotico
void rm_device(SistemaDomotico& sistemaDomotico, std::string device) {
    sistemaDomotico.rm(device);
}

// Funzione che chiama show di SistemaDomotico di tutti i dispositivi
void show(SistemaDomotico& sistemaDomotico) {
    sistemaDomotico.show();
}

// Funzione che chiama show di SistemaDomotico per un dispositivo
void show_device(SistemaDomotico& sistemaDomotico, std::string device) {
    sistemaDomotico.show(device);
}

// Funzione che chiama setTime di SistemaDomotico
void set_time(SistemaDomotico& sistemaDomotico, std::string time) {
    // Provo a creare un oggetto tempo con la stringa data
    // Se la conversione in int fallisce o il numero è fuori dal range tempo, gestisco l'eccezione
    try {
        Tempo t(time);
        sistemaDomotico.setTime(t);
    } catch(std::invalid_argument& e) {
        sistemaDomotico.printTime();
        sistemaDomotico.getLogger().log(" ERROR: Tempo non valido\n");
    } catch(std::out_of_range& e) {
        sistemaDomotico.printTime();
        sistemaDomotico.getLogger().log(" ERROR: Tempo non valido\n");
    } catch (std::runtime_error& e) {
        // Se il tempo settato è 23.59 gestisco la relativa eccezione di fine programma
        sistemaDomotico.printTime();
        sistemaDomotico.getLogger().log(" Giornata conclusa, arrivederci!\n");
        sistemaDomotico.getLogger().~Logger();
        exit(0);
    }
}

// Funzione che chiama resetTime di SistemaDomotico
void reset_time(SistemaDomotico& sistemaDomotico) {
    sistemaDomotico.resetTime();
}

// Funzione che chiama resetTimers di SistemaDomotico
void reset_timers(SistemaDomotico& sistemaDomotico) {
    sistemaDomotico.resetTimers();
}

// Funzione che chiama resetAll di SistemaDomotico
void reset_all(SistemaDomotico& sistemaDomotico) {
    sistemaDomotico.resetAll();
}

// Funzione che chiama add di SistemaDomotico per un dispositivo manuale
void add_manuale(SistemaDomotico& sistemaDomotico) {
    std::string answer;
    int number;

    // Menu' dispositivi manuali disponibili
    sistemaDomotico.printTime();
    sistemaDomotico.getLogger().log(" Digita il corrispettivo numero per il dispositivo desiderato: \n");
    sistemaDomotico.getLogger().log("         0) Impianto fotovoltaico\n");
    sistemaDomotico.getLogger().log("         1) Pompa di calore + termostato\n");
    sistemaDomotico.getLogger().log("         2) Scaldabagno\n");
    sistemaDomotico.getLogger().log("         3) Frigorifero\n\n");

    // Acquisisco numero menu'
    sistemaDomotico.printTime();
    sistemaDomotico.getLogger().log(" Numero: ");
    std::getline(std::cin, answer);
    sistemaDomotico.getLogger().logInput(answer);

    enum DispManuale::DispDomotico device;

    // Provo a convertire la stringa in numero ed a settare tipo dispositivo
    // Se la conversione in int fallisce, gestisco l'eccezione
    // Se numero fuori dal menu', stampo a video l'errore
    try {
        number = stoi(answer);

        switch(number) {
            case 0:
                device = DispManuale::DispDomotico::Impianto_Fotovoltaico;
                break;
            case 1:
                device = DispManuale::DispDomotico::Pompa_di_calore_termostato;
                break;
            case 2:
                device = DispManuale::DispDomotico::Scaldabagno;
                break;
            case 3:
                device = DispManuale::DispDomotico::Frigorifero;
                break;
            default:
                sistemaDomotico.printTime();
                sistemaDomotico.getLogger().log(" ERROR: Numero non valido\n");
                return;
        }
    } catch(std::invalid_argument& e) {
        sistemaDomotico.printTime();
        sistemaDomotico.getLogger().log(" ERROR: Numero non valido\n");
        return;
    } catch(std::out_of_range& e) {
        sistemaDomotico.printTime();
        sistemaDomotico.getLogger().log(" ERROR: Numero non valido\n");
        return;
    }

    // Acquisisco nome dispositivo
    sistemaDomotico.printTime();
    sistemaDomotico.getLogger().log(" Nome dispositivo: ");
    std::getline(std::cin, answer);
    sistemaDomotico.getLogger().logInput(answer);

    // Controllo se nel nome e' presente ':', in caso stampo a video l'errore
    if(!check_name(answer)) {
        sistemaDomotico.printTime();
        sistemaDomotico.getLogger().log(" ERROR: Carattere ':' non consentito\n");
    } else
        sistemaDomotico.add(answer, device);
}

// Funzione che chiama add di SistemaDomotico per un dispositivo a ciclo prefissato
void add_CP(SistemaDomotico& sistemaDomotico) {
    std::string answer;
    int number;

    // Menu' dispositivi a ciclo prefissato disponibili
    sistemaDomotico.printTime();
    sistemaDomotico.getLogger().log(" Digita il corrispettivo numero per il dispositivo desiderato: \n");
    sistemaDomotico.getLogger().log("         0) Lavatrice\n");
    sistemaDomotico.getLogger().log("         1) Lavastoviglie\n");
    sistemaDomotico.getLogger().log("         2) Tapparelle elettriche\n");
    sistemaDomotico.getLogger().log("         3) Forno a microonde\n");
    sistemaDomotico.getLogger().log("         4) Asciugatrice\n");
    sistemaDomotico.getLogger().log("         5) Televisore\n");

    // Acquisisco numero menu'
    sistemaDomotico.printTime();
    sistemaDomotico.getLogger().log(" Numero: ");
    std::getline(std::cin, answer);
    sistemaDomotico.getLogger().logInput(answer);

    enum DispCicloPrefissato::DispDomotico device;

    // Provo a convertire la stringa in numero ed a settare tipo dispositivo
    // Se la conversione in int fallisce, gestisco l'eccezione
    // Se numero fuori dal menu', stampo a video l'errore
    try {
        number = stoi(answer);

        switch(number) {
            case 0:
                device = DispCicloPrefissato::DispDomotico::Lavatrice;
                break;
            case 1:
                device = DispCicloPrefissato::DispDomotico::Lavastoviglie;
                break;
            case 2:
                device = DispCicloPrefissato::DispDomotico::Tapparelle_elettriche;
                break;
            case 3:
                device = DispCicloPrefissato::DispDomotico::Forno_a_microonde;
                break;
            case 4:
                device = DispCicloPrefissato::DispDomotico::Asciugatrice;
                break;
            case 5:
                device = DispCicloPrefissato::DispDomotico::Televisore;
                break;
            default:
                sistemaDomotico.printTime();
                sistemaDomotico.getLogger().log(" ERROR: Numero non valido\n");
                return;
        }
    } catch(std::invalid_argument& e) {
        sistemaDomotico.printTime();
        sistemaDomotico.getLogger().log(" ERROR: Numero non valido\n");
        return;
    } catch(std::out_of_range& e) {
        sistemaDomotico.printTime();
        sistemaDomotico.getLogger().log(" ERROR: Numero non valido\n");
        return;
    }

    // Acquisisco nome dispositivo
    sistemaDomotico.printTime();
    sistemaDomotico.getLogger().log(" Nome dispositivo: ");
    std::getline(std::cin, answer);
    sistemaDomotico.getLogger().logInput(answer);

    // Controllo se nel nome e' presente ':', in caso stampo a video l'errore
    if(!check_name(answer)) {
        sistemaDomotico.printTime();
        sistemaDomotico.getLogger().log(" ERROR: Carattere ':' non consentito\n");
    } else
        sistemaDomotico.add(answer, device);
}

// Funzione che chiama erase di SistemaDomotico
void erase(SistemaDomotico& sistemaDomotico, std::string device) {
    sistemaDomotico.erase(device);
}

/* MAIN */

int main() {  
    
    try {
        
        //File di output
        Logger logger("output.txt");

        SistemaDomotico sistemaDomotico(logger);

        std::string answer;
        std::string delimiter = " ";

        // Log di introduzione con legenda comandi

        logger.log("\n");
        logger.log("-----------------------------------------------------------------------------\n");
        logger.log("------------------------------ SISTEMA DOMOTICO -----------------------------\n");
        logger.log("-----------------------------------------------------------------------------\n");
        
        logger.log("Le operazioni che puoi eseguire con il tuo sistema domotico sono le seguenti: \n");
        logger.log("  # set ${DEVICENAME} on\n");
        logger.log("  # set ${DEVICENAME} off\n");
        logger.log("  # set ${DEVICENAME} ${START} [${STOP}]\n");
        logger.log("  # rm ${DEVICENAME}\n");
        logger.log("  # show\n");
        logger.log("  # show ${DEVICENAME}\n");
        logger.log("  # set time ${TIME}\n");
        logger.log("  # reset time\n");
        logger.log("  # reset timers\n");
        logger.log("  # reset all\n");
        logger.log("  # add\n");
        logger.log("  # erase ${DEVICENAME}\n");
        logger.log("Per uscire digitare: exit\n");

        // Ciclo per emulare l'interfaccia utente
        while(true) {
            

            
            int pos;
            answer = "";

            // Acquisisco riga di comando
            logger.log("\n");
            sistemaDomotico.printTime();
            logger.log(" ");
            std::getline(std::cin, answer);
            logger.logInput(answer + "\n");

            
            // Acquisisco l'input ed estraggo il comando
            pos = answer.find(delimiter);
            std::string command = answer.substr(0, pos);
            answer.erase(0, pos + delimiter.length());

            std::string device;
            std::string pattern;

            Commands cmd;

            // Controllo se esiste o meno il comando
            if(mapCommands.find(command) != mapCommands.end())
                cmd = mapCommands[command];
            else
                cmd = Commands::unknown;

            // Switch statement per confrontare comando in input con quelli presenti nella mappa
            switch(cmd) {
                case Commands::set:
                    // Controllo sintassi comando
                    if(!check_command(mapCommands[command], answer)) {
                        sistemaDomotico.printTime();
                        logger.log(" ERROR: Sintassi comando\n");
                        break;
    
                    }
                    pos = answer.find(delimiter); // Posizione secondo pattern
                    // Se comando set time ${TIME}
                    if(answer.substr(0, pos) == "time") {
                        pos = answer.find_last_of(delimiter); // Posizione ultimo pattern
                        std::string time = answer.substr(pos + 1); // Ultimo pattern
                        set_time(sistemaDomotico, time);

                    } else {
                        pos = answer.find_last_of(delimiter); // Posizione ultimo pattern
                        pattern = answer.substr(pos + 1); // Ultimo pattern

                        // Se comando set ${DEVICENAME} on oppure set ${DEVICENAME} off
                        if(pattern == "on" || pattern == "off") {
                            answer.erase(pos); // Cancello ultimo pattern
                            device = answer; // Nome dispositivo

                            if(pattern == "on")
                                set_device_on(sistemaDomotico, device);
                            else if ( pattern == "off")
                                set_device_off(sistemaDomotico, device);
                        }
                        else {
                            answer.erase(pos); // Cancello ultimo pattern
                            pos = answer.find_last_of(delimiter); // Posizione ultimo pattern
                            // Se comando set ${DEVICENAME} ${START}
                            if(answer.find_last_of(':') == std::string::npos) {
                                std::string start = pattern; // Orario accensione
                                device = answer; // Nome dispositivo

                                set_device_start(sistemaDomotico, device, start);
                            // Se comando set ${DEVICENAME} ${START} [${STOP}]
                            } else if (answer.substr(pos + 1).find(":") != std::string::npos) {
                                std::string stop = pattern; // Orario spegnimento
                                std::string start = answer.substr(pos + 1); // Orario accensione

                                answer.erase(pos); // Cancello ultimo pattern
                                device = answer; // Nome dispositivo

                                set_device_start_stop(sistemaDomotico, device, start, stop);
                            // Altrimenti comando errato
                            } else {
                                sistemaDomotico.printTime();
                                logger.log(" ERROR: Sintassi comando\n");
                            }
                        }
                    }
                    break;

                case Commands::rm:
                    device = answer;
                    rm_device(sistemaDomotico, device);
                    break;

                case Commands::show:
                    // Se comando show
                    if(answer == "show")
                        show(sistemaDomotico);
                    // Altrimenti comando show ${DEVICENAME}
                    else{
                        device = answer;
                        show_device(sistemaDomotico, device);
                    }
                    break;

                case Commands::reset:
                    // Controllo sintassi comando
                    if(!check_command(mapCommands[command], answer)) {
                        sistemaDomotico.printTime();
                        logger.log(" ERROR: Sintassi comando\n");
                        break;
                    }
                    pos = answer.find(delimiter);
                    pattern = answer.substr(0, pos);
                    // Se comando reset time
                    if(pattern == "time")
                        reset_time(sistemaDomotico);
                    // Se comando reset timers
                    else if(pattern == "timers")
                        reset_timers(sistemaDomotico);
                    // Altrimenti comando reset all
                    else
                        reset_all(sistemaDomotico);
                    break;

                case Commands::add:
                    // Controllo sintassi comando
                    if(!check_command(mapCommands[command], answer)) {
                        sistemaDomotico.printTime();
                        logger.log(" ERROR: Sintassi comando\n");
                        break;
                    }
                    // Chiedo se si vuole aggiungere un dispositivo manuale o CP
                    sistemaDomotico.printTime();
                    logger.log(" Digita M (manuale) o CP (ciclo prefissato): ");
                    std::getline(std::cin, answer);
                    logger.logInput(answer + "\n");
                    logger.log("\n");
                    // Se dispositivo manuale
                    if(answer == "M")
                        add_manuale(sistemaDomotico);
                    // Se dispositivo a ciclo prefissato
                    else if(answer == "CP")
                        add_CP(sistemaDomotico);
                    else {
                        sistemaDomotico.printTime();
                        logger.log(" ERROR: Risposta non valida\n");
                    }
                    break;

                case Commands::erase:
                    // Controllo sintassi comando
                    if(!check_command(mapCommands[command], answer)) {
                        sistemaDomotico.printTime();
                        logger.log(" ERROR: Nome dispositivo mancante\n");
                        break;
                    }
                    device = answer;
                    erase(sistemaDomotico, device);
                    break;

                case Commands::exit:
                    // Controllo sintassi comando
                    if(!check_command(mapCommands[command], answer)) {
                        sistemaDomotico.printTime();
                        logger.log(" ERROR: Sintassi comando\n");
                        break;
                    }
                    logger.~Logger();
                    exit(0);
                    break;

                default:
                    sistemaDomotico.printTime();
                    logger.log(" ERROR: Comando '" + command + "' non esistente!\n");
            }
        }
    
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    
    return 0; 
}