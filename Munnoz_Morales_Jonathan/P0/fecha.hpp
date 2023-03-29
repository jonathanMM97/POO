#ifndef FECHA_HPP_
#define FECHA_HPP_

/**
  * @author Jonathan Muñoz Morales
  * @version 29/03/2023
*/

#include <cstdio>
#include <ctime>
#include <clocale>

class Fecha{
public:

  // ------------------------- Clase pública dentro de Fecha ------------------------------------
  class Invalida{
  public:
    Invalida(const char* porque):porque_(porque){}
    inline const char* por_que() const{return porque_;}
  private:
    const char* porque_;
  };


  // ------------------------- Constructores ------------------------------------

  explicit Fecha(int dia = 0, int mes = 0, int anno = 0);
  Fecha(const char* cadena);

  // ------------------------- Variables constantes ------------------------------------

  static const int AnnoMinimo = 1902;
  static const int AnnoMaximo = 2037;

  // -------------------------- Observadores ----------------------------------------

  operator const char*() const;
  inline int dia() const noexcept{return dia_;}
  int mes() const noexcept{return mes_;}
  int anno() const noexcept{return anno_;}

  // ------------------------- Operadores aritmeticos ------------------------------------

  Fecha& operator +=(int dias);
  Fecha& operator -=(int dias);
  Fecha operator + (int dias) const;
  Fecha operator - (int dias) const;
  Fecha& operator ++();
  Fecha operator ++(int);
  Fecha& operator --();
  Fecha operator --(int);

  private:
    int dia_, mes_, anno_;//variables dia_ almacenará el dia de la fecha el mes_ el mes y el anno_ el año de la fecha

    void comprobarFecha() const;//comprueba si la fecha pasada cumple con todos los requisitos para ser considerada valida para este problema
    void comprobarRangoAnnos() const;//comprueba los rangos establecidos en las variables constantes
    bool comprobarAnnoBisiesto() const;//comprueba si el año evaluado es bisiesto
};

// ------------------------- Operadores externos lógicos ------------------------------------

bool operator > (const Fecha& a, const Fecha& b);
bool operator < (const Fecha& a, const Fecha& b);
bool operator == (const Fecha& a, const Fecha& b);
bool operator <= (const Fecha& a, const Fecha& b);
bool operator >= (const Fecha& a, const Fecha& b);
bool operator != (const Fecha& a, const Fecha& b);

#endif
