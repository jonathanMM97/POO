/**
  * @author Jonathan Muñoz Morales
  * @version 29/03/2023
*/

#include "cadena.hpp"

Cadena::Cadena(size_t tam, char c): tam_(tam){

  s_ = new char[tam_ + 1];

  for(size_t i = 0; i < tam_; i++)
    s_[i] = c;

  s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena& cadena):tam_(cadena.tam_){
  
  s_ = new char[cadena.tam_ + 1];
  strcpy(s_, cadena.s_);
  s_[tam_] = '\0';
}

Cadena::Cadena(const char* cadena){
  
  tam_ = strlen(cadena);
  s_ = new char[tam_ + 1];
  strcpy(s_, cadena);
  s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena& cadena, const size_t indice, const size_t tam){
  
  if(indice > cadena.tam_)
    throw std::out_of_range("Error acceso: Indice fuera de rango.");
  tam_ = cadena.tam_ - indice;

  if(tam < tam_)
    tam_ = tam;

  s_ = new char[tam_ + 1];
  std::strncpy(s_, cadena.s_ + indice, tam_);
  s_[tam_] = 0;
}

Cadena::Cadena(Cadena&& cadena)
{
  
  char cadenaVacia = '\0';
  s_ = cadena.s_;
  tam_ = cadena.tam_;

  cadena.s_ = &cadenaVacia;
  cadena.tam_ = 0;
}

Cadena& Cadena::operator=(const Cadena& cadena){
  
  if(strcmp(s_, cadena.s_) != 0){
    delete[] s_;
    tam_ = 0;

    tam_ = cadena.tam_;
    s_ = new char[tam_ + 1];
    strcpy(s_, cadena.s_);
  }
  return *this;
}

Cadena& Cadena::operator=(const char* cadena){
  
  tam_ = strlen(cadena);
  s_ = new char[tam_ + 1];
  strcpy(s_, cadena);
  return *this;
}

Cadena& Cadena::operator=(Cadena&& cadena)
{
  char cadenaVacia = '\0';
  delete[] s_;
  s_ = cadena.s_;
  tam_ = cadena.tam_;

  cadena.s_ = &cadenaVacia;
  cadena.tam_ = 0;

  return *this;
}


Cadena& Cadena::operator+=(const Cadena& cadena){
  
  char* aux = new char[tam_ + 1];
  strcpy(aux, s_);
  delete[] s_;
  tam_ += cadena.tam_;
  s_ = new char[tam_ + 1];
  strcpy(s_, aux);
  delete[] aux;
  strcat(s_, cadena.s_);
  return *this;
}

Cadena operator+(const Cadena& a, const Cadena& b){
  
  Cadena aux = a;
  aux+=b;
  return aux;
}

const char& Cadena::at(size_t indice) const{
  
  if(indice >= tam_)
    throw std::out_of_range("Error at: indice fuera de rango.");
  return s_[indice];
}

char& Cadena::at(size_t indice){
  
  if(indice >= tam_)
    throw std::out_of_range("Error at: indice fuera de rango.");
  return s_[indice];
}

Cadena Cadena::substr(size_t indice, size_t tam) const{
  
  if(indice >= tam_ || tam > tam_ - indice)
    throw std::out_of_range("Error substr: Indice fuera de rango.");
  return Cadena(*this, indice, tam);
}


bool operator < (const Cadena& a, const Cadena& b){
 
  return strcmp(a.c_str(), b.c_str()) < 0;
}


bool operator > (const Cadena& a, const Cadena& b){
  
  return (b < a);
}

bool operator == (const Cadena& a, const Cadena& b){
  
  return strcmp(a.c_str(), b.c_str()) == 0;
}

bool operator != (const Cadena& a, const Cadena& b){
  
  return !(a == b);
}

bool operator <= (const Cadena& a, const Cadena& b){
  
  return !(b < a);
}

bool operator >= (const Cadena& a, const Cadena& b){
  
  return !(a < b);
}

std::istream& operator >> (std::istream& is, Cadena& cadena){
  char* aux = new char[33]{'\0'};
  aux[0] = '\0';
  is.width(33);
  is >> aux;
  cadena = aux;
  delete[] aux;
  return is;
}

std::ostream& operator << (std::ostream& os, const Cadena& cadena){
  os << cadena.c_str();
  return os;
}

Cadena::~Cadena(){
  
  if(tam_ > 0){
    delete[] s_;
    tam_ = 0;
    s_ = nullptr;
  }
}
