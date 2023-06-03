#include "articulo.hpp"

std::ostream& operator<<(std::ostream& os, const Articulo& a)
{
    Fecha f = a.f_publi();
    int y =  f.anno();
    os<< "[" <<a.referencia() << "] \"" << a.titulo() << "\", " << y << ". " << std::fixed << std::setprecision(2) << a.precio() << " €" << std::endl;

    return os;
}