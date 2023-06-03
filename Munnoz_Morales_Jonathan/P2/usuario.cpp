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
    clave_=p;
}

//Método verifica que devuelve true or false si la cadena que le paso es la clave almacenada
bool Clave::verifica(const char * cad) const
{
    char sal[3]{};
    int i;
    for (i = 0; i < 2; i++)
    {
        sal[i]=clave_[i];
    }

    sal[i]='\0';
    
    char * p = crypt(cad, sal);
    if(p==nullptr)
    {
        Clave::Incorrecta fallo{ERROR_CRYPT};
        throw fallo;
    }

    return(strcmp(p, clave_.c_str())==0);
}

//------------------------------------------------------USUARIO---------------------------------------------------------------------

unordered_set<Cadena> Usuario::conjunto_ids; //Como es static lo inicializo aquí

Usuario::Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& pass): id_{id}, nombre_{nombre}, apellidos_{apellidos}, direccion_{direccion}, pass_{pass}
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
        tarjetas_[t.numero()]=const_cast<Tarjeta*>(&t);
}

void Usuario::no_es_titular_de(const Tarjeta& t)
{
    tarjetas_.erase(t.numero());
}

//Asociación con artículos
void Usuario::compra(const Articulo& a, unsigned int c)
{
    Articulos::iterator i=this->articulos_.end();
    if (articulos_.find(const_cast<Articulo*>(&a)) != i)
    {
        if(c==0)
        {
            articulos_.erase(const_cast<Articulo*>(&a));
        }
        else
        {
            articulos_[const_cast<Articulo*>(&a)]=c;
        }
    }   
    else
    {
        if(c!=0)
        {
            articulos_.insert( std::pair<Articulo * const, unsigned int>(const_cast<Articulo*>(&a), c));
        }   
    }
}

//Número de elementos en el carrito
size_t Usuario::n_articulos() const noexcept
{
    return (articulos_.size());
}

//El destructor deberá llamar a anula_titular PARA TODAS LAS TARJETAS
Usuario::~Usuario()
{
    Tarjetas::const_iterator i=tarjetas_.cbegin();
    while(i!=tarjetas_.cend())
    {
        i->second->anula_titular();
        i++;
    }  
    conjunto_ids.erase(id_);
}

std::ostream& operator <<(std::ostream& os, const Usuario& user) //Escritura de Usuario
{
    os<< user.id()<<"["<<user.pass_.clave().c_str()<<"]"<<user.nombre()<<user.apellidos()<<"\n"<<user.direccion()<<endl;
    os<<"Tarjetas:" ;
    for(auto &t: user.tarjetas_) 
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

