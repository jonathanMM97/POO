/*
    * @author Jonathan Muñoz Morales
    * @version 1.0

*/
#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include <iomanip>
#include <iostream>

#include "cadena.hpp"
#include "fecha.hpp"


class Articulo{
private:// tiene cinco atributos privados
    Cadena codRef, title;
    Fecha PublDate;
    double price;
    unsigned nCopies;

public:

    //Constructor...
    inline Articulo(Cadena cod, Cadena tit, Fecha date, double p, size_t copies):codRef(cod), title(tit), PublDate(date), price(p), nCopies(copies){}

    //Observables...
    inline Cadena referencia() const{return codRef;}
    inline Cadena titulo() const{return title;}
    inline Fecha f_publi() const{return PublDate;}
    inline double precio() const{return price;}
    inline unsigned stock() const{return nCopies;}

    //Modificadores...
    inline double& precio(){return price;}
    inline unsigned& stock(){return nCopies;}
};

std::ostream& operator <<(std::ostream& os, const Articulo& a);

#endif//ARTICULO_HPP_