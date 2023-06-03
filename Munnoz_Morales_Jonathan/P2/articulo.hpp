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
        double price_;
        int stock_;

    public:

        Articulo(Cadena reference, Cadena title, Fecha date, double price, int stock): 
        reference(reference), title(title), release(date), price_(price), stock_(stock){};

        Cadena referencia() const{return reference;};
        Cadena titulo() const{return title;};
        Fecha f_publi() const{return release;};
        double precio() const{return price_;};
        int stock() const{return stock_;};
        double& precio(){return price_;};
        int& stock(){return stock_;};
        
};

ostream& operator<<(ostream& os, const Articulo& art);

#endif