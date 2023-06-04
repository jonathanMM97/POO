/**
 * @author Jonathan Muñoz Morales
 * @version 1.9
*/

#include "usuario.hpp"
#include <unistd.h>  // for crypt
#include <cstring>   // for strlen
#include <random>

//Constructor
Clave::Clave(const char* cad)
{
    static char caracteres[65]{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789/."};
    static std::random_device gen;
    static std::uniform_int_distribution<std::size_t> dist(0, 63);

    if(strlen(cad)<5)
    {
        Clave::Incorrecta fallo{CORTA};
        throw fallo;
    }
    
    int a{};
    char sal[3]{};
    int i{0};
    while(i<2)
    {
        a=dist(gen);
        sal[i] = caracteres[a];
        i++;
    }
    sal[i]='\0';
    
    char * p = crypt(cad, sal); //crypt(cadena en claro, la sal)
    cifrada=p;
}

//Método verifica que devuelve true or false si la cadena que le paso es la clave almacenada
bool Clave::verifica(const char * cad) const
{
    char sal[3]{};
    int i;
    for (i = 0; i < 2; i++)
    {
        sal[i]=cifrada[i];
    }

    sal[i]='\0';
    
    char * p = crypt(cad, sal);
    if(p==nullptr)
    {
        Clave::Incorrecta fallo{ERROR_CRYPT};
        throw fallo;
    }

    return(strcmp(p, cifrada.c_str())==0);
}

//------------------------------------------------------USUARIO---------------------------------------------------------------------

unordered_set<Cadena> Usuario::conjunto_ids; //Como es static lo inicializo aquí

Usuario::Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& pass): id_{id}, name{nombre}, lastName{apellidos}, address{direccion}, pass{pass}
{
    if(!conjunto_ids.insert(id).second) //Si el id ya existe el segundo dato del par que devuelve el insert será falso
    {
        Usuario::Id_duplicado fail{id};
        throw fail;
    }
}

//Métodos de asociación con tarjeta
void Usuario::es_titular_de(const Tarjeta& t)
{
    if(t.titular()==this)
        tar[t.numero()]=const_cast<Tarjeta*>(&t);
}

void Usuario::no_es_titular_de(const Tarjeta& t)
{
    tar.erase(t.numero());
}

//Asociación con artículos
void Usuario::compra(const Articulo& a, unsigned int c)
{
    Articulos::iterator i=this->art.end();
    if (art.find(const_cast<Articulo*>(&a)) != i)
    {
        if(c==0)
        {
            art.erase(const_cast<Articulo*>(&a));
        }
        else
        {
            art[const_cast<Articulo*>(&a)]=c;
        }
    }   
    else
    {
        if(c!=0)
        {
            art.insert( std::pair<Articulo * const, unsigned int>(const_cast<Articulo*>(&a), c));
        }   
    }
}

void Usuario::vaciar_carro()
{
    art.clear();
}

//Número de elementos en el carrito
size_t Usuario::n_articulos() const noexcept
{
    return (art.size());
}

//El destructor deberá llamar a anula_titular PARA TODAS LAS TARJETAS
Usuario::~Usuario()
{
    Tarjetas::const_iterator i=tar.cbegin();
    while(i!=tar.cend())
    {
        i->second->anula_titular();
        i++;
    }  
    conjunto_ids.erase(id_);
}

std::ostream& operator <<(std::ostream& os, const Usuario& user) //Escritura de Usuario
{
    os << user.id() <<"["<<user.pass.clave().c_str()<<"]"<<user.nombre()<<user.apellidos()<<"\n"<<user.direccion()<<endl;
    os<<"Tarjetas:" ;
    for(auto &t: user.tar) 
        os<<*t.second<<endl;       
    return os;
}

std::ostream& mostrar_carro(std::ostream& os, const Usuario& u) //Escritura del carro
{
    os<<"Carrito de compra de "<<u.id()<<" [Artículos: "<<u.n_articulos()<<"]"<<"\n"<<" Cant. Artículo"<<endl;
    os<<"==========================================================="<<endl;
    int art=u.n_articulos();
    while( art > 0 )
        {
            for(auto i = u.compra().begin(); i != u.compra().end(); i++)
            {
                os <<setw(4) << i->second << "    "
                    << " [" << (*i->first).referencia() << "] " << "\""
                    << (*i->first).titulo() << "\", "
                    << (*i->first).f_publi().anno()
                    << ". " <<fixed <<setprecision(2) << (*i->first).precio() << " €" <<endl;

                --art;
            }
        }

        return os;
}

