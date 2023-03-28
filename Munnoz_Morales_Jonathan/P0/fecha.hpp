#ifndef _FECHA_HPP_
#define _FECHA_HPP_

public class Fecha{
public:

	//Contantes públicas
	static const int AnnoMinimo = 1902;
	static const int AnnoMaximo = 2037;

	//clase pública Invalida
	public class Invalida{
	public:
		Invalida(const char* porque){std::strcpy(porque_, porque);}
		inline const char* por_que(){return porque_;}
	private:
		char* porque_;
	};

	//Contructores
	Fecha(int dia = 0, int mes = 0, int anno = 0);
	Fecha(const char* fecha);
	Fecha(const Fecha& f) = default;

	//Observadores
	inline int dia() const noexcept{return dia_;}
	inline int mes() const noexcept{return mes_;}
	inline int anno() const noexcept{return anno_;}

	//Operadores no modificadores
	Fecha operator +(int dias) const;
	Fecha operator -(int dias) const;

	//Operadores modificadores
	operator const char*() const;
	Fecha& operator ++();
	Fecha& operator ++(int);
	Fecha& operator --();
	Fecha& operator --(int);
	Fecha& operator +=(int dias);
	Fecha& operator -=(int dias);

	//Metodos amigos(friend)
	friend Fecha& operator <(const Fecha& f, const Fecha& g);
	friend Fecha& operator <=(const Fecha& f, const Fecha& g);
	friend Fecha& operator ==(const Fecha& f, const Fecha& g);
	friend Fecha& operator !=(const Fecha& f, const Fecha& g);
	friend Fecha& operator >(const Fecha& f, const Fecha& g);
	friend Fecha& operator <=(const Fecha& f, const Fecha& g);

	//Destructor
	~Fecha() = default;
private:
	int dia_, mes_, anno_;
	void esValida() const;
	bool esBisiesto() const;
};

#endif//_FECHA_HPP_
