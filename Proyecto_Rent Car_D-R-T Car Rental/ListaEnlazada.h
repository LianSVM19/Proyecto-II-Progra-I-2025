#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include <string>
#include <sstream>
#include "Nodo.h" // Incluye la definicion de NodoVehiculo y NodoCliente

using namespace std;

// =====================================
// DEFINICIoN DE LISTAVEHICULO
// =====================================
class ListaVehiculo {
private:
    NodoVehiculo* cabeza; // Puntero al primer nodo
    int tamano;

public:
    // Constructor
    ListaVehiculo();

    // Destructor (liberara toda la lista y los Vehiculos asociados)
    ~ListaVehiculo();

    // Metodos de gestion de la coleccion
    void agregarAlInicio(Vehiculo*);
    Vehiculo* buscar(string);

    // Getters y utilidades
    int getTamano();
    bool estaVacia();
    NodoVehiculo* getCabeza() { return cabeza; }
    void setCabeza(NodoVehiculo* nuevo) { cabeza = nuevo; }
    bool eliminarVehiculo(string);
    bool removerSinBorrar(string);

    // Funcion "to string"
    string toString();



};

// =====================================
// DEFINICIoN DE LISTACLIENTE
// =====================================
class ListaCliente {
private:
    NodoCliente* cab;
    int tamano;

public:
    // Constructor (inicia la lista vacia)
    ListaCliente();

    // Destructor (libera todos los nodos y sus clientes)
    ~ListaCliente();

    // Metodo para agregar un nuevo cliente al final de la lista
    void agregarCliente(Cliente* c);
    Cliente* buscar(string);
    bool eliminar(string);

    // Getters y utilidades
    Cliente* getCliente();
    int getTamano();
    bool estaVacia();
    NodoCliente* getCab();

    // Funcion "to string" para mostrar todos los clientes
    string toString();
};

// =====================================
// DEFINICIoN DE LISTACOLABORADOR
// =====================================
class ListaColaborador {
private:
    NodoColaborador* cab;
    int tamano;

public:
    // Constructor (inicia la lista vacia)
    ListaColaborador();

    // Destructor (libera todos los nodos y sus Colaboradores)
    ~ListaColaborador();

    // Metodo para agregar un nuevo cliente al final de la lista
    void agregarColaborador(Colaborador* c);
    Colaborador* buscar(string);
    bool eliminar(string);

    // Getters y utilidades
    int getTamano();
    bool estaVacia();
    Colaborador* getColaborador();
    NodoColaborador* getCab();

    // Funcion "to string" para mostrar todos los Colaboradores
    string toString();
};

// =====================================
// DEFINICIoN DE LISTASUCURSAL
// =====================================
class ListaSucursal {
private:
    NodoSucursal* cab;
    int tamano;

public:
    // Constructor (inicia la lista vacia)
    ListaSucursal();

    // Destructor (libera todos los nodos y sus sucursales)
    ~ListaSucursal();

    // Metodos de gestion de la coleccion
    void agregarSucursal(Sucursal*);
    Sucursal* buscar(string); // Busca una sucursal por su codigo
    bool eliminar(string); // Elimina una sucursal por su codigo

    // Getters y utilidades
    int getTamano();
    bool estaVacia();
    Sucursal* getSucursal();
    NodoSucursal* getCab();

    // Funcion "to string" para mostrar todas las sucursales
    string toString();
};



// =====================================
// DEFINICIoN DE LISTAPLANTEL
// =====================================
class ListaPlantel {
private:
    NodoPlantel* cab;
    int tamano;

public:
    // Constructor (inicia la lista vacia)
    ListaPlantel();

    // Destructor (libera todos los nodos y sus planteles)
    ~ListaPlantel();

    // Metodos de gestion de la coleccion
    void agregarPlantel(Plantel*);
    Plantel* buscar(string); // Busca un plantel por su codigo
    bool eliminar(string); // Elimina un plantel por su codigo

    // Getters y utilidades
    int getTamano();
    bool estaVacia();
    NodoPlantel* getCab();
    Plantel* buscarPorCodigo(string);
    void mostrarCodigos();

    // Funcion "to string" para mostrar todas los planteles
    string toString();
};

// =====================================
// DEFINICIoN DE LISTASOLICITUD
// =====================================
class ListaSolicitud {
private:
    NodoSolicitud* cab;
    int tamano;

public:
    // Constructor (inicia la lista vacia)
    ListaSolicitud();

    // Destructor (libera todos los nodos y sus planteles)
    ~ListaSolicitud();

    // Metodos de gestion de la coleccion
    void agregarSolicitud(SolicitudAlquiler*);
    SolicitudAlquiler* buscar(string); // Busca una Solicitud por su codigo
    bool eliminar(string); // Elimina una Solicitud por su codigo

    // Getters y utilidades
    int getTamano();
    bool estaVacia();
    NodoSolicitud* getCab();

    // Funcion "to string" para mostrar todas las solicitudes
    string toString();
};

// =====================================
// DEFINICIoN DE LISTACONTRATO
// =====================================
class ListaContrato {
private:
    NodoContrato* cab;
    int tamano;

public:
    // Constructor (inicia la lista vacia)
    ListaContrato();

    // Destructor (libera todos los nodos y sus planteles)
    ~ListaContrato();

    // Metodos de gestion de la coleccion
    void agregarContrato(ContratoAlquiler*);
    ContratoAlquiler* buscar(string); // Busca un Contrato por su codigo
    bool eliminar(string); // Elimina un Contrato por su codigo

    // Getters y utilidades
    int getTamano();
    bool estaVacia();
    NodoContrato* getCab();

    // Funcion "to string" para mostrar todas los Contratos
    string toString();
};







#endif