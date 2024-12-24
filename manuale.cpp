#include "manuale.h"

enum class manuale::dispositivoDomotico
{
    Impianto_Fotovoltaico,
    Pompa_di_calore_termostato,
    Scaldabagno,
    Frigorifero
};

class manuale::caratteristiche
{
    private:

    std::string nome;
    double potenza;

    public:
    caratteristiche(std::string n, double p) : nome{n} , potenza{p} {};
};

const std::unordered_map<manuale::dispositivoDomotico, manuale::caratteristiche> manuale::tipiDispositivi = {
    {manuale::dispositivoDomotico::Impianto_Fotovoltaico, {"Impianto Fotovoltaico", 1.5}},
    {manuale::dispositivoDomotico::Pompa_di_calore_termostato, {"Pompa di Calore + Termostato", -2.0}},
    {manuale::dispositivoDomotico::Scaldabagno, {"Scaldabagno", -1.0}},
    {manuale::dispositivoDomotico::Frigorifero, {"Frigorifero", -0.4}}
};