#include "Tempo.h"
#include "SistemaDomotico.h"
#include "DispManuale.h"
#include "DispCicloPrefissato.h"
#include <iostream>
#include <string>
#include <map>

enum class Commands {
    set,
    rm,
    show,
    reset,
    exit
};

static std::map<std::string, Commands> mapCommands = {
    {"set", Commands::set},
    {"rm", Commands::rm},
    {"show", Commands::show},
    {"reset", Commands::reset},
    {"exit", Commands::exit}
};

void set_device_on(SistemaDomotico sistemaDomotico, std::string device){
    sistemaDomotico.setOn(std::cout, device);
}

void set_device_off(SistemaDomotico sistemaDomotico, std::string device){
    sistemaDomotico.setOff(std::cout, device);
}

void set_device_start(SistemaDomotico sistemaDomotico, std::string device, std::string start){
    Tempo t_start(start);
    sistemaDomotico.setTimer(std::cout, device, t_start);
}

void set_device_start_stop(SistemaDomotico sistemaDomotico, std::string device, std::string start, std::string stop){
    Tempo t_start(start);
    Tempo t_stop(stop);

    sistemaDomotico.setTimer(SistemaDomotico sistemaDomotico, std::cout, device, t_start, t_stop);
}

void rm_device(SistemaDomotico sistemaDomotico, std::string device){
    sistemaDomotico.rm(std::cout, device);
}

void show(SistemaDomotico sistemaDomotico){
    sistemaDomotico.show(std::cout);
}

void show_device(SistemaDomotico sistemaDomotico, std::string device){
    sistemaDomotico.show(std::cout, device);
}

void set_time(SistemaDomotico sistemaDomotico, std::string time){
    Tempo t(time);

    sistemaDomotico.setTime(std::cout, t);
}

void reset_time(SistemaDomotico sistemaDomotico){
    sistemaDomotico.resetTime(std::cout);
}

void reset_timers(SistemaDomotico sistemaDomotico){
    sistemaDomotico.resetTimers(std::cout);
}

void reset_all(SistemaDomotico sistemaDomotico){
    sistemaDomotico.resetAll(std::cout);
}

bool check_command(Commands command, std::string input){
    std::string delimiter = " ";
    switch(command){
        case Commands::set:
             std::string pattern = answer.substr(answer.find_last_of(delimiter) + 1);
             if(pattern.find(':') == std::string::npos && pattern != "on" && pattern != "off"){
                return false;
             } else if(pattern.find(':') != std::string::npos){
                try {
                    delimiter = ":";

                    int h = stoi(pattern.substr(0, pattern.find(delimiter)));
                    pattern.erase(0, pattern.find(delimiter) + delimiter.length());
                    int m = stoi(pattern.substr(0, pattern.find(delimiter)));

                    input.erase(input.find_last_of(delimiter));
                    pattern = answer.substr(answer.find_last_of(delimiter) + 1);

                    if(pattern.find(':') != std::string::npos){
                        h = stoi(pattern.substr(0, pattern.find(delimiter)));
                        pattern.erase(0, pattern.find(delimiter) + delimiter.length());
                        m = stoi(pattern.substr(0, pattern.find(delimiter)));
                    }
                } catch(std::invalid_argument& e) {
                    return false;
                } catch(std::out_of_range& e) {
                    return false;
                }
             }
            break;
        case Commands::reset:
            if(input != "")
                return false;
            break;
        case Commands::exit:
            if(input != "")
                return false;
            break;
    }
    return true;
}

int main() {  
    SistemaDomotico sistemaDomotico;

    std::string answer;
    std::string delimiter = " ";

    std::cout << std::endl;
    std::cout << "-----------------------------------------------------------------------------" << std::endl;
    std::cout << "------------------------------ SISTEMA DOMOTICO ----------------------------- " << std::endl;
    std::cout << "----------------------------------------------------------------------------- " << std::endl << std::endl;
    
    std::cout << "Le operazioni che puoi eseguire con il tuo sistema domotico sono le seguenti: " << std::endl;
    std::cout << "# set ${DEVICENAME} on" << std::endl;
    std::cout << "# set ${DEVICENAME} off" << std::endl;
    std::cout << "# set ${DEVICENAME} ${START} [${STOP}]" << std::endl;
    std::cout << "# rm ${DEVICENAME}" << std::endl;
    std::cout << "# show" << std::endl;
    std::cout << "# show ${DEVICENAME}" << std::endl;
    std::cout << "# set time ${TIME}" << std::endl;
    std::cout << "# reset time" << std::endl;
    std::cout << "# reset timers" << std::endl;
    std::cout << "# reset all" << std::endl << std::endl;
    std::cout << "Per uscire digitare: exit" << std::endl;

    while(true){
        answer = "";

        std::cout << std::endl << "Cosa vuoi fare?" << std::endl;
        std::getline(std::cin, answer);

        std::string command = answer.substr(0, answer.find(delimiter));
        answer.erase(0, answer.find(delimiter) + delimiter.length());

        std::string device;
        std::string pattern;
        
        switch(mapCommands[command]){
            case Commands::set:
                if(!check_command(mapCommands[command], answer)){
                    std::cout << "Errore di sintassi nel comando"
                    break;
                }
                if(answer.substr(0, answer.find(delimiter)) == "time"){
                    std::string time = answer.substr(answer.find_last_of(delimiter) + 1);
                    set_time(sistemaDomotico, time);

                } else {
                    pattern = answer.substr(answer.find_last_of(delimiter) + 1); 

                    if(pattern == "on" || pattern == "off") {
                        answer.erase(answer.find_last_of(delimiter));
                        device = answer;

                        if(pattern == "on")
                            set_device_on(device);
                        else if ( pattern == "off")
                            set_device_off(sistemaDomotico, device);
                    }
                    else {
                        answer.erase(answer.find_last_of(delimiter));
                        if(answer.find_last_of(':') == std::string::npos){
                            std::string start = pattern;
                            device = answer;

                            set_device_start(sistemaDomotico, device, start);
                        } else {
                            std::string stop = pattern;
                            std::string start = answer.substr(answer.find_last_of(delimiter) + 1);

                            answer.erase(answer.find_last_of(delimiter));
                            device = answer;

                            set_device_start_stop(sistemaDomotico, device, start, stop);
                        }
                    }
                }
                break;

            case Commands::rm:
                device = answer;
                std::cout << device << std::endl;
                rm_device(sistemaDomotico, device);
                break;

            case Commands::show:
                if(answer == "show")
                    show();
                else{
                    device = answer;
                    std::cout << device << std::endl;
                    show_device(sistemaDomotico, device);
                }
                break;

            case Commands::reset:
                if(!check_command(mapCommands[command], answer)){
                    std::cout << "Errore di sintassi nel comando"
                    break;
                }
                pattern = answer.substr(0, answer.find(delimiter));
                if(pattern == "time")
                    reset_time(sistemaDomotico);
                else if(pattern == "timers")
                    reset_timers(sistemaDomotico);
                else
                    reset_all(sistemaDomotico);
                break;

            case Commands::exit:
                if(!check_command(mapCommands[command], answer)){
                    std::cout << "Errore di sintassi nel comando"
                    break;
                }
                exit(0);
                break;

            default:
                std::cout << "Comando '" << command << "' non esistente!" << std::endl;
        }
    }

    return 0; 
}