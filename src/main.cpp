#include "Tempo.h"

#include "SistemaDomotico.h"
#include "DispManuale.h"
#include "DispCicloPrefissato.h"
#include <iostream>
#include <string>

int main() {
    
    /*Tempo t1(25, -2);
    Tempo t2(18, 0);
    Tempo t3(20, 0);
    Tempo t4(22, 0);*/

    //throw std::invalid_argument("Prova eccezioni");

    std::cout << "Prova";

    /*DispManuale disp1("Scaldabagno 1", DispManuale::DispDomotico::Scaldabagno, t1, t2);
    DispManuale disp2("Scaldabagno 2", DispManuale::DispDomotico::Scaldabagno, t3, t4);

    std::cout << "ID: " << disp1.getID() << std::endl;
    std::cout << "Nome: " << disp1.getNome() << std::endl;
    std::cout << "Potenza: " << disp1.getPotenza() << std::endl;
    std::cout << "Tempo accensione: " << disp1.getAccensione() << std::endl;
    std::cout << "Tempo spegnimento: " << disp1.getSpegnimento() << std::endl;

    std::cout << std::endl;

    std::cout << "ID: " << disp2.getID() << std::endl;
    std::cout << "Nome: " << disp2.getNome() << std::endl;
    std::cout << "Potenza: " << disp2.getPotenza() << std::endl;
    std::cout << "Tempo accensione: " << disp2.getAccensione() << std::endl;
    std::cout << "Tempo spegnimento: " << disp2.getSpegnimento() << std::endl;

    Tempo t5(10, 30);
    Tempo t6(12, 30);

    DispCicloPrefissato disp3("Microonde 1", DispCicloPrefissato::DispDomotico::Forno_a_microonde, t5);
    DispCicloPrefissato disp4("Microonde 2", DispCicloPrefissato::DispDomotico::Forno_a_microonde, t6);

    std::cout << std::endl;

    std::cout << "ID: " << disp3.getID() << std::endl;
    std::cout << "Nome: " << disp3.getNome() << std::endl;
    std::cout << "Potenza: " << disp3.getPotenza() << std::endl;
    std::cout << "Tempo accensione: " << disp3.getAccensione() << std::endl;
    std::cout << "Tempo spegnimento: " << disp3.getDurata() << std::endl;

    std::cout << std::endl;

    std::cout << "ID: " << disp4.getID() << std::endl;
    std::cout << "Nome: " << disp4.getNome() << std::endl;
    std::cout << "Potenza: " << disp4.getPotenza() << std::endl;
    std::cout << "Tempo accensione: " << disp4.getAccensione() << std::endl;
    std::cout << "Tempo spegnimento: " << disp4.getDurata() << std::endl;

    
    SistemaDomotico casa;
    casa.setOn(std::cout,"Lavastoviglie");
    casa.setOff(std::cout,"Lavatrice");*/

    return 0; 
}