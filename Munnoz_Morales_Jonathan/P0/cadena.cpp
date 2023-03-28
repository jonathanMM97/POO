#include "cadena.hpp"
#include <iostream>
#include <stdexcept>

Cadena::Cadena(size_t tam, char c):s_(new char[tam + 1]), tam_(tam)
{
	for(size_t i = 0 ; i < tam ; i++)
		s_[i] = c;
	s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena& cadena):s_(new char[cadena.tam_ + 1]), tam_(cadena.tam_)
{
	strcpy(s_, cadena.s_);
}

Cadena::Cadena(const char* cadena):s_(new char[strlen(cadena)+1]), tam_(strlen(cadena))
{
	strcpy(s_, cadena);
}

Cadena& Cadena::operator =(const Cadena& cadena)
{
	if(this != &cadena)
	{
		delete[] s_;
		s_ = new char[cadena.tam_ + 1];
		tam_ = cadena.tam_;
		strcpy(s_, cadena.s_);
	}

	return *this;
}

Cadena& Cadena::operator +=(const Cadena& cadena)
{
	char* aux = new char[tam_+1];
	strcpy(aux, s_);

	tam_ += cadena.tam_;

	delete[] s_;
	s_ new char[tam_ + 1];
	strcpy(s_, aux);
	strcat(s_, cadena.s_);

	delete[] aux;
	return *this;
}

Cadena operator +(const Cadena& cad, const Cadena& cad1)
{
	Cadena aux(cad);
	return aux += cad1;
}

bool operator ==(const Cadena& cad, const Cadena& cad1)
{
	return !strcmp(cad, cad1);
}

bool operator !=(const Cadena& cad, const Cadena& cad1)
{
	return strcmp(cad, cad1);
}

bool operator <(const Cadena& cad, const Cadena& cad1)
{
	return (strcmp(cad, cad1) < 0); 
}

bool operator >(const Cadena& cad, const Cadena& cad1)
{
	return cad1 < cad;
}

bool operator <=(const Cadena& cad, const Cadena& cad1)
{
	return !(cad1 < cad);
}

bool operator >=(const Cadena& cad, const Cadena& cad1)
{
	return !(cad < cad1);
}

char& Cadena::at(size_t indice)
{
	if(indice < tam_)
		return s_[indice];
	else
		throw std::out_of_range("Funcion at(): fuera de limites.");
}

const char& Cadena::at(size_t indice) const
{
        if(indice < tam_)
                return s_[indice];
        else 
                throw std::out_of_range("Funcion at(): fuera de limites.");
}

Cadena Cadena::substr(size_t indice, size_t tam) const
{
	if(indice + tam > tam_ || tam > tam_ || indice > tam_)
		throw std::out_of_range("Funcion substr(): fuera de limites.");
	else{
		Cadena aux(tam);
		strncpy(aux.s_, s_ + i, tam);
		aux.s_[tam] = '\0';
		return aux;
	}
}

Cadena::~Cadena()
{
	delete[] s_;
	tam_ = 0;
}
