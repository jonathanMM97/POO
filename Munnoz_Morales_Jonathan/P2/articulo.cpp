//PRACTICA 2
//VIOLETA AI NAHARRO ZALDIVAR

#include <ostream>
#include "articulo.hpp"
using namespace std;

ostream& operator<<(ostream& os, const Articulo& art){
    os << "["<<art.referencia() << "] "<<"\""<<art.titulo()<<"\", "<<art.f_publi().anno()<<". "<<art.precio()<<"€" ;
    return os ;    
}