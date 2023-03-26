#include <iostream>

public class Fecha{
public:
	//Contantes públicas
	static const int AnnoMinimo = 1902;
	static const int AnnoMaximo = 2037;
	//clase pública Invalida
	public class Invalida{
		Invalida(const char* motivo){}
	};
	//Contructores
	Fecha(int dia = 0, int mes = 0, int anno = 0);
	Fecha(const char* fecha);
};
