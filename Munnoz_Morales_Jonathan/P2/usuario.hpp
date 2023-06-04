#ifndef USUARIO_HPP_
#define USUARIO_HPP_

/**
 * @author Jonathan Muñoz Morales
 * @version 1.9
*/

#include <map>
#include <unordered_map>
#include <unordered_set>
#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"

class Tarjeta;
class Numero;

class Clave 
{
private:
    Cadena cifrada;
public:
    //Constructor
    Clave(const char* cad);

    //Tipo enumerado para los tipos de excepciones
    enum Razon{CORTA, ERROR_CRYPT};

    //Clase Incorrecta para excepciones
    class Incorrecta
    {
        private:
            Razon razon_;
        public:
            Incorrecta(Razon r): razon_{r} {} //Constructor
            Razon razon() const noexcept{return razon_;}
    };

    //Método observador que devuelve la contraseña cifrada
    Cadena clave() const noexcept{return cifrada;}

    //Método verifica
    bool verifica(const char *) const;
};

class Usuario 
{
public:
    //Contenedores públicos
    typedef std::map<Numero, Tarjeta*> Tarjetas;
    typedef std::unordered_map<Articulo*, unsigned int> Articulos;

    //Constructor
    Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& pass);

    //Clase de excepción Id_duplicado
    class Id_duplicado
    {
        private:
            const Cadena idd_;
        public:
            Id_duplicado(const Cadena& id):idd_{id}{};
            const Cadena idd() const{return(idd_);}
    };

    //Constructor de copia anulado
    Usuario(const Usuario&) = delete;
    //Operador de asignación anulado
    Usuario& operator=(const Usuario& cad) = delete;

    //Observadores
    const Cadena& id() const noexcept {return id_;}
    const Cadena& nombre() const noexcept { return(name);}
    const Cadena& apellidos() const noexcept {return(lastName);}
    const Cadena& direccion() const noexcept {return(address);}
    const Tarjetas& tarjetas()const noexcept{return(tar);}
    const Articulos& compra()const noexcept{return(art);}

    //Asociación con la clase tarjeta 
    void es_titular_de(const Tarjeta& t);
    void no_es_titular_de(const Tarjeta& t);

    //Asociación con artículo
    void compra(const Articulo& a, unsigned int c=1);
    void vaciar_carro();

    //Número de elementos en el carrito
    size_t n_articulos() const noexcept;

    //El destructor deberá llamar a anula_titular TODO
    ~Usuario();

    friend std::ostream& operator <<(std::ostream& os, const Usuario& u); //Escritura de Usuario
        
	friend std::ostream& mostrar_carro(std::ostream& os, const Usuario& u); //Escritura del carro

private:
    const Cadena id_, name, lastName, address;
    const Clave pass;
    Tarjetas tar;
    Articulos art;

    unordered_set<Cadena> conjunto_ids;
};




#endif
