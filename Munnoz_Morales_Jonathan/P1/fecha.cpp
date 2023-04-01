/**
  * @author Jonathan Muñoz Morales
  * @version 29/03/2023
*/

#include "fecha.hpp"


Fecha::Fecha(int dia, int mes, int anno): dia_(dia), mes_(mes), anno_(anno)
{		//Constructor predeterminado y de conversion

    std::time_t tiempo_cal = std::time(nullptr);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_cal);

    if(dia_ == 0)
      dia_ = tiempo_descompuesto->tm_mday;
    if(mes_ == 0)
      mes_ = tiempo_descompuesto->tm_mon + 1;
    if(anno_ == 0)
      anno_ = tiempo_descompuesto->tm_year + 1900;

    comprobarFecha();
}


Fecha::Fecha(const char* cadena)
{			//Contructor de conversion

  if(sscanf(cadena, "%d/%d/%d", &dia_, &mes_, &anno_) == 3)
    *this = Fecha(dia_,mes_,anno_);

  else
    throw Invalida("Error de conversion: Fecha introducida incorrecta.");
}

const char* Fecha::cadena() const
{

  
  static char aux[36];

  tm t = {};
  t.tm_mday = dia_;
  t.tm_mon = mes_ - 1;
  t.tm_year = anno_ - 1900;

  static const char* semana[7] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};
  static const char* mes[13] = {"", "enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};

  mktime(&t);
  int diasem = t.tm_wday;

  sprintf(aux, "%s %d de %s de %d", semana[diasem], dia_, mes[mes_], anno_);

  return aux;
}

/*
Fecha::operator const char*() const
{			//Operador de conversion a cadena de caracteres

  static char* fechaCad = new char[36];//variable a devolver con un tamaño establecido

  tm t = {0, 0, 0, dia_, mes_ - 1, anno_ - 1900, 0, 0, 0};

  mktime(&t);//actualizamos la hora del sistema

  setlocale(LC_ALL, "es_ES");
  strftime(fechaCad, 36, "%A %d de %B de %Y", &t);//rellenamos en la cadena a devolver el formato pedido
  return fechaCad;
}

*/

Fecha& Fecha::operator += (int dias)
{			//Operador aritmetico

  std::time_t tiempo_cal = std::time(nullptr);
  std::tm* tiempoOper = std::localtime(&tiempo_cal);

  tiempoOper->tm_mday = dia_ + dias;
  tiempoOper->tm_mon = mes_ - 1;
  tiempoOper->tm_year = anno_ - 1900;

  mktime(tiempoOper);//Actualizamos la hora

  dia_ = tiempoOper->tm_mday;
  mes_ = tiempoOper->tm_mon + 1;
  anno_ = tiempoOper->tm_year + 1900;

  comprobarFecha();
  return *this;
}

Fecha& Fecha::operator -=(int dias)
{			//Operador aritmetico

  *this += -dias;
  return *this;
}

Fecha Fecha::operator +(int dias) const
{			//Operador aritmetico

  Fecha tmp = *this;
  tmp += dias;
  return tmp;
}

Fecha Fecha::operator -(int dias) const
{			//Operador aritmetico

  Fecha t = *this;
  t += -dias;
  return t;
}

Fecha& Fecha::operator++()
{			//Operador aritmetico de incremento

  *this+=1;
  return *this;
}


Fecha Fecha::operator++(int)
{			//Operador aritmetico de incremento pero antes de incrementar devuelve el estado original

  Fecha t(*this);
  *this += 1;
  return t;
}

Fecha& Fecha::operator--()
{			//Operador aritmetico de decremento

  *this += -1;
  return *this;
}

Fecha Fecha::operator--(int)
{			//Operador aritmetico de decremento pero antes de decrementar devuelve el estado original

  Fecha t(*this);
  *this += -1;
  return t;
}
void Fecha::comprobarFecha() const
{			//Lanza una excepción en caso de que se cumpla alguna de las condiciones escritas

  if(anno_ < AnnoMinimo || anno_ > AnnoMaximo)
    throw Invalida("Error Anno: Año incorrecto.");
  if(mes_ < 1 || mes_ > 12)
    throw Invalida("Error mes: Mes incorrecto.");
  if(dia_ < 1 || dia_ > 31)
    throw Invalida("Error dia: Dia incorrecto.");
  if(dia_ == 29 && mes_ == 2 && !comprobarAnnoBisiesto())
    throw Invalida("Error dia: Dia incorrecto.");
  if(dia_ > 29 && mes_ == 2)
    throw Invalida("Error dia: Dia incorrecto");
  if((mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11) && dia_ > 30)
    throw Invalida("Erro mes: Mes incorrecto.");
}

bool Fecha::comprobarAnnoBisiesto() const
{			//Devuelve si el año a evaluar es bisiesto o no.

  return (anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0));
}

void Fecha::comprobarRangoAnnos() const
{			//Comprueba si el año a evaluar esta en los límites establecidos por el documento(Requisitos)

  if(anno_ < AnnoMinimo || anno_ > AnnoMaximo)
    throw Invalida("Error anno: Demasiado antiguo o demasiado hacia el futuro.");
}

bool operator < (const Fecha& a, const Fecha& b)
{			//Operador logico que junto al operador "==" los demás solo hacen uso de llamadas a estos así evitamos codigo redundante

  if(a.anno() < b.anno())
    return true;
  else if(a.mes() < b.mes())
    return true;
  else if(a.dia() < b.dia())
    return true;
  else
    return false;
}

bool operator == (const Fecha& a, const Fecha& b)
{			//Operador logico que junto al operador "<" los demás solo hacen uso de llamadas a estos así evitamos codigo redundante

  return ((a.dia() == b.dia()) && (a.mes() == b.mes()) && (a.anno() == b.anno()));
}

bool operator > (const Fecha& a, const Fecha& b)
{			//Operador logico

    return (b < a);
}

bool operator <= (const Fecha& a, const Fecha& b)
{			//Operador logico

  return (a < b || a == b);
}

bool operator >= (const Fecha& a, const Fecha& b)
{			//Operador logico

  return (b < a || a == b);
}

bool operator != (const Fecha& a, const Fecha& b)
{			//Operador logico

  return !(a == b);
}

// ------------------------- Sobrecarga del operador << ------------------------------------
std::ostream& operator <<(std::ostream& os, const Fecha& f)
{

  os << f.cadena();
  return os;
}

// ------------------------- Sobrecarga del operador >> ------------------------------------
std::istream& operator >>(std::istream& is, Fecha& f)
{

  char* cadena = new char[11];
  
  is.getline(cadena, 11);
  
  try{
  
    f = Fecha(cadena);
  
  }catch(Fecha::Invalida& e){
  
    is.setstate(std::ios::failbit);
  
    throw;
  
  }

  return is;
}
