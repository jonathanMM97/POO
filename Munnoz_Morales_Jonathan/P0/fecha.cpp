#include "fecha.hpp"
#include <iostream>
#include <ctime>
#include <cstdio>
#include <locale>

Fecha::Fecha(int dia, int mes, int anno):dia_(dia), mes_(mes), anno_(anno)
{
	std::time_t tiempo_calendario = std::time(nullptr);
	std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);

	if(anno_ == 0)
		anno_ = tiempo_descompuesto->tm_year + 1900;

	if(mes_ == 0)
		mes_ = tiempo_descompuesto->tm_mon +1;

	if(dia_ == 0)
		dia_ = tiempo_descompuesto->tm_mday;

	if(dia != 0 || mes != 0 || anno != 0)
		esValida();
}

Fecha::Fecha(const char* fecha)
{
	int dia, mes, anno;
	if(sscanf(fecha, "%d/%d/%d",&dia, &mes, &anno) != 3)
	{
		Fecha::Invalida format("Formato incorrecto por parte de la cadena recibida.");
		throw format;
	}

	Fecha f(dia, mes, anno);
	*this = f;
}

Fecha::operator const char*() const
{
	std::locale::global(std::locale("es_ES.utf8"));
	char* aux = new char[100];

	std::time_t tiempo_calendario = std::time(nullptr);
	std::tm* f = std::localtime(&tiempo_calendario);

	f->tm_mday = dia_;
	f->tm_mon = mes_ -1;
	f->tm_year = anno_ - 1900;
	mktime(f);
	strftime(aux, 100, "%A %e de %B de %Y", f);
	return aux;
}

Fecha& Fecha::operator +=(int dias)
{
	std::tm f{};
	f.tm_mday = dia_+dias;
	f.tm_mon = mes_ - 1;
	f.tm_year = anno_ - 1900;
	std::mktime(&f);

	dia_ = f.tm_mday;
	mes_ = f.tm_mon + 1;
	anno_ = f.tm_year + 1900;

	esValida();
	return *this;
}

Fecha& Fecha::operator -=(int dias)
{
	*this += -dias;
	return *this;
}

Fecha& Fecha::operator ++()
{
	*this += 1;
	return *this;
}

Fecha& Fecha::operator ++(int)
{
	Fecha *f = new Fecha(*this);

	*this += 1;
	return *f;
}

Fecha& Fecha::operator --()
{
	*this += -1;
	return *this;
}

Fecha& Fecha::operator --(int)
{
	Fecha *f = new Fecha(*this);

	*this += -1;
	return *f;
}

Fecha Fecha::operator +(int dias) const
{
	Fecha f(*this);
	return f += dias;
}

Fecha Fecha::operator -(int dias) const
{
	Fecha f(*this);
	return f += -dias;
}

bool operator ==(const Fecha& f, const Fecha& g)
{
	return (f.dia_ == g.dia_ && f.mes_ == g.mes_ && f.anno_ == g.anno_);
}

bool operator !=(const Fecha& f, const Fecha& g)
{
	return !(f == g);
}

bool operator <(const Fecha& f, const Fecha& g)
{
	return (f.anno_ < g.anno_ || (f.anno_ == g.anno_ && f.mes_ < g.mes_ || (f.mes_ == g.mes_ && f.dia_ < g.dia_)));
}


bool operator >(const Fecha& f, const Fecha& g)
{
	return g < f;
}

bool operator <=(const Fecha& f, const Fecha& g)
{
	return !(g < f);
}

bool operator >=(const Fecha& f, const Fecha& g)
{
	return !(f < g);
}
