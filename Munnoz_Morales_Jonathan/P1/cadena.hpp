#ifndef CADENA_HPP
#define CADENA_HPP
/**
  * @author Jonathan Muñoz Morales
  * @version 29/03/2023
*/

#include <cstring>
#include <iomanip>
#include <stdexcept>
#include <iterator>
#include <functional>
#include <string>


class Cadena{
public:
  // ------------------------- Iteradores --> P1 ------------------------------------
  typedef char* iterator;
  typedef const char* const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  // ------------------------- Constructores ------------------------------------

  explicit Cadena(size_t tam = 0, char c = ' ');
  Cadena(const Cadena& cadena);
  Cadena(const char* cadena);
  Cadena(const Cadena& cadena, const size_t indice, const size_t tam);
  Cadena(Cadena&& cadena);//Añadido para la P1

  // ------------------------- Operadores de asignación y conversion ------------------------------------

  Cadena& operator=(const Cadena& cadena);
  Cadena& operator=(const char* cadena);
  Cadena& operator=(Cadena&& cadena);//Añadido para la P1
  explicit operator const char*() const{return s_;}
  inline const char* c_str() const noexcept{return s_;}

  // ------------------------- Observadores ------------------------------------

  inline size_t length() const noexcept{return tam_;}
  inline const char& operator[] (unsigned indice) const noexcept{return s_[indice];}
  const char& at(size_t indice) const;
  Cadena substr(size_t indice, size_t tam) const;

  // ------------------------- Observadores añadidos para la practica P1 ------------------------------------

  inline iterator begin() const{return s_;}
  inline iterator end() const{return s_ + tam_;}
  inline const_iterator cbegin() const{return begin();}
  inline const_iterator cend() const{return end();}
  inline const_reverse_iterator rbegin() const{return const_reverse_iterator(end());}
  inline const_reverse_iterator rend() const{return const_reverse_iterator(begin());}
  inline const_reverse_iterator crbegin() const{return const_reverse_iterator(end());}
  inline const_reverse_iterator crend() const{return const_reverse_iterator(begin());}

  // ------------------------- Metodo concatenador de cadenas ------------------------------------

  Cadena& operator+=(const Cadena& cadena);

  // ------------------------- Modificadores ------------------------------------

  inline char& operator[] (unsigned indice) noexcept{return s_[indice];}
  char& at(size_t indice);

  // ------------------------- Modificadores añadidos para la practica P1 ------------------------------------
  inline reverse_iterator rbegin(){return reverse_iterator(end());}
  inline reverse_iterator rend(){return reverse_iterator(begin());}

  // ------------------------- Destructor ------------------------------------
  ~Cadena();

// ------------------------- PARTE PRIVADA ------------------------------------
private:
  char* s_;
  size_t tam_;

};


// ------------------------- Sobrecarga operadores entrada/salida ------------------------------------
std::istream& operator >> (std::istream& os, Cadena& a);
std::ostream& operator << (std::ostream& os, const Cadena& a);


// ------------------------- Operadores externos logicos ------------------------------------

bool operator ==(const Cadena& a, const Cadena& b);
bool operator !=(const Cadena& a, const Cadena& b);
bool operator >(const Cadena& a, const Cadena& b);
bool operator <(const Cadena& a, const Cadena& b);
bool operator >= (const Cadena& a, const Cadena& b);
bool operator <= (const Cadena& a, const Cadena& b);

// ------------------------- Metodo externo para concatenar cadenas ------------------------------------
Cadena operator+(const Cadena& a, const Cadena& b);

#endif
