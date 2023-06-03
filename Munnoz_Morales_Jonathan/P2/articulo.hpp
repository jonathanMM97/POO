//PRACTICA 2
//VIOLETA AI NAHARRO ZALDIVAR

#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

using namespace std;

class Articulo
{
    public:
        Articulo(Cadena ref, Cadena tit, Fecha rel, double price, int stock): 
        reference(ref), title(tit), release(rel), price_(price), stock_(stock){};

        Cadena referencia() const{return reference;};
        Cadena titulo() const{return title;};
        Fecha f_publi() const{return release;};
        double precio() const{return price_;};
        int stock() const{return stock_;};
        double& precio(){return price_;};
        int& stock(){return stock_;};

    private:
        const Cadena reference;
        const Cadena title;
        const Fecha release;
        double price_;
        int stock_;
};

ostream& operator<<(ostream& os, const Articulo& art);

#endif