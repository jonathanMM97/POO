#ifndef CADENA_HPP
#define CADENA_HPP
/**
  * @author Jonathan Muñoz Morales
  * @version 29/03/2023
*/

#include <cstring>
#include <stdexcept>


class Cadena{
public:

  // ------------------------- Constructores ------------------------------------

  explicit Cadena(size_t tam = 0, char c = ' ');
  Cadena(const Cadena& cadena);
  Cadena(const char* cadena);
  Cadena(const Cadena& cadena, const size_t indice, const size_t tam);

  // ------------------------- Operadores de asignación y conversion ------------------------------------

  Cadena& operator=(const Cadena& cadena);
  Cadena& operator=(const char* cadena);
  explicit operator const char*() const;
  inline const char* c_str() const noexcept{return s_;}

  // ------------------------- Observadores ------------------------------------

  inline size_t length() const noexcept{return tam_;}
  inline const char& operator[] (unsigned indice) const noexcept{return s_[indice];}
  const char& at(size_t indice) const;
  Cadena substr(size_t indice, size_t tam) const;

  // ------------------------- Metodo concatenador de cadenas ------------------------------------

  Cadena& operator+=(const Cadena& cadena);

  // ------------------------- Modificadores ------------------------------------

  inline char& operator[] (unsigned indice) noexcept{return s_[indice];}
  char& at(size_t indice);

  // ------------------------- Destructor ------------------------------------
  ~Cadena();

// ------------------------- PARTE PRIVADA ------------------------------------
private:
  char* s_;
  size_t tam_;

};

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
