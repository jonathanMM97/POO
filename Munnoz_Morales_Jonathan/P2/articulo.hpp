/**
 * @author Jonathan Muñoz Morales
 * @version 1.9
*/

#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

using namespace std;

class Articulo
{
private:

    const Cadena reference;
    const Cadena title;
    const Fecha release;
    double price;
    int copies;

public:
    //Constructor...
    Articulo(Cadena reference, Cadena title, Fecha date, double price, int stock): 
    reference(reference), title(title), release(date), price(price), copies(stock){};

    //Observables...
    Cadena referencia() const{return reference;};
    Cadena titulo() const{return title;};
    Fecha f_publi() const{return release;};
    double precio() const{return price;};
    int stock() const{return copies;};

    //Modificadores...
    double& precio(){return price;};
    int& stock(){return copies;};
        
};

//Metodos externos...x
ostream& operator<<(ostream& os, const Articulo& art);

#endif