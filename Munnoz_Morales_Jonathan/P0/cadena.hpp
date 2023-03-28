#ifndef _CADENA_HPP_
#define _CADENA_HPP_

#include <iostream>

class Cadena{
public:
	//Constructores
	explicit Cadena(size_t tam = 0, char c = ' ');
	Cadena(const Cadena& c);
	Cadena(const char* cadena);
	
	//Operador de conversion y asignacion
	Cadena& operator =(const Cadena& cadena);
	operator const char*() const{return s_;}

	//Observadores
	inline size_t length() const{return tam_;}

	//Operadore concatenador de cadena
	Cadena& operator +=(const Cadena& cadena);

	//Funciones amigas
	friend Cadena operator +(const Cadena& cad, const Cadena& cad1);
	friend bool operator <(const Cadena& cad, const Cadena& cad1);
	friend bool operator <=(const Cadena& cad, const Cadena& cad1);
	friend bool operator >=(const Cadena& cad, const Cadena& cad2);
	friend bool operator >(const Cadena& cad, const Cadena& cad1);
	friend bool operator ==(const Cadena& cad, const Cadena& cad1);
	friend bool operator !=(const Cadena& cad, const Cadena& cad1);

	//Observadores
	char& operator [](size_t indice) noexcept{return s_[indice];}
	char& at(size_t indice);
	const char& operator [](size_t indice) const noexcept{return s_[indice];}
	const char& at(size_t indice) const;
	Cadena substr(size_t indice, size_t tam) const;

	//Destructor
	~Cadena();

private:
	char* s_;
	size_t tam_;
};
#endif//_CADENA_HPP_
