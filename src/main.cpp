#include "Tempo.h"

#include "DispManuale.h"
#include "DispCicloPrefissato.h"

int main() {
    Tempo t1(16, 0);
    Tempo t2(18, 0);
    Tempo t3(20, 0);
    Tempo t4(22, 0);

    DispManuale disp1(1, "Scaldabagno 1", DispManuale::DispDomotico::Scaldabagno, t1, t2);
    DispManuale disp2(2, "Scaldabagno 2", DispManuale::DispDomotico::Scaldabagno, t3, t4);

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

    DispCicloPrefissato disp3(3, "Microonde 1", DispCicloPrefissato::DispDomotico::Forno_a_microonde, t5);
    DispCicloPrefissato disp4(4, "Microonde 2", DispCicloPrefissato::DispDomotico::Forno_a_microonde, t6);

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
}