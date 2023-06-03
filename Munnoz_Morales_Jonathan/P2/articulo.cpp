/**
 * @author Jonathan Muñoz Morales
 * @version 1.9
*/

#include <ostream>
#include "articulo.hpp"
using namespace std;

ostream& operator<<(ostream& os, const Articulo& a){
    os << "[" << a.referencia() << "] " << "\"" << a.titulo() << "\", " << a.f_publi().anno() << ". " << a.precio() << "€" ;
    
    return os ;    
}