#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include <string>
#include <sstream>
#include "Nodo.h" // Incluye la definición de NodoVehiculo y NodoCliente

using namespace std;

// =====================================
// DEFINICIÓN DE LISTAVEHICULO
// =====================================
class ListaVehiculo {
private:
    NodoVehiculo* cabeza; // Puntero al primer nodo
    int tamano;

public:
    // Constructor
    ListaVehiculo();

    // Destructor (liberará toda la lista y los Vehiculos asociados)
    ~ListaVehiculo();

    // Métodos de gestión de la colección
    void agregarAlInicio(Vehiculo*);
    Vehiculo* buscar(string);

    // Getters y utilidades
    int getTamano();
    bool estaVacia();
    NodoVehiculo* getCabeza() { return cabeza; }
    void setCabeza(NodoVehiculo* nuevo) { cabeza = nuevo; }
    bool eliminarVehiculo(string);
    bool removerSinBorrar(string);

    // Función "to string"
    string toString();



};

// =====================================
// DEFINICIÓN DE LISTACLIENTE
// =====================================
class ListaCliente {
private:
    NodoCliente* cab;
    int tamano;

public:
    // Constructor (inicia la lista vacía)
    ListaCliente();

    // Destructor (libera todos los nodos y sus clientes)
    ~ListaCliente();

    // Método para agregar un nuevo cliente al final de la lista
    void agregarCliente(Cliente* c);
    Cliente* buscar(string);
    bool eliminar(string);

    // Getters y utilidades
    Cliente* getCliente();
    int getTamano();
    bool estaVacia();
    NodoCliente* getCab();

    // Función "to string" para mostrar todos los clientes
    string toString();
};

// =====================================
// DEFINICIÓN DE LISTACOLABORADOR
// =====================================
class ListaColaborador {
private:
    NodoColaborador* cab;
    int tamano;

public:
    // Constructor (inicia la lista vacía)
    ListaColaborador();

    // Destructor (libera todos los nodos y sus Colaboradores)
    ~ListaColaborador();

    // Método para agregar un nuevo cliente al final de la lista
    void agregarColaborador(Colaborador* c);
    Colaborador* buscar(string);
    bool eliminar(string);

    // Getters y utilidades
    int getTamano();
    bool estaVacia();
    Colaborador* getColaborador();
    NodoColaborador* getCab();

    // Función "to string" para mostrar todos los Colaboradores
    string toString();
};

// =====================================
// DEFINICIÓN DE LISTASUCURSAL
// =====================================
class ListaSucursal {
private:
    NodoSucursal* cab;
    int tamano;

public:
    // Constructor (inicia la lista vacía)
    ListaSucursal();

    // Destructor (libera todos los nodos y sus sucursales)
    ~ListaSucursal();

    // Métodos de gestión de la colección
    void agregarSucursal(Sucursal*);
    Sucursal* buscar(string); // Busca una sucursal por su código
    bool eliminar(string); // Elimina una sucursal por su código

    // Getters y utilidades
    int getTamano();
    bool estaVacia();
    Sucursal* getSucursal();
    NodoSucursal* getCab();

    // Función "to string" para mostrar todas las sucursales
    string toString();
};



// =====================================
// DEFINICIÓN DE LISTAPLANTEL
// =====================================
class ListaPlantel {
private:
    NodoPlantel* cab;
    int tamano;

public:
    // Constructor (inicia la lista vacía)
    ListaPlantel();

    // Destructor (libera todos los nodos y sus planteles)
    ~ListaPlantel();

    // Métodos de gestión de la colección
    void agregarPlantel(Plantel*);
    Plantel* buscar(string); // Busca un plantel por su código
    bool eliminar(string); // Elimina un plantel por su código

    // Getters y utilidades
    int getTamano();
    bool estaVacia();
    NodoPlantel* getCab();
    Plantel* buscarPorCodigo(string);
    void mostrarCodigos();

    // Función "to string" para mostrar todas los planteles
    string toString();
};

// =====================================
// DEFINICIÓN DE LISTASOLICITUD
// =====================================
class ListaSolicitud {
private:
    NodoSolicitud* cab;
    int tamano;

public:
    // Constructor (inicia la lista vacía)
    ListaSolicitud();

    // Destructor (libera todos los nodos y sus planteles)
    ~ListaSolicitud();

    // Métodos de gestión de la colección
    void agregarSolicitud(SolicitudAlquiler*);
    SolicitudAlquiler* buscar(string); // Busca una Solicitud por su código
    bool eliminar(string); // Elimina una Solicitud por su código

    // Getters y utilidades
    int getTamano();
    bool estaVacia();
    NodoSolicitud* getCab();

    // Función "to string" para mostrar todas las solicitudes
    string toString();
};

// =====================================
// DEFINICIÓN DE LISTACONTRATO
// =====================================
class ListaContrato {
private:
    NodoContrato* cab;
    int tamano;

public:
    // Constructor (inicia la lista vacía)
    ListaContrato();

    // Destructor (libera todos los nodos y sus planteles)
    ~ListaContrato();

    // Métodos de gestión de la colección
    void agregarContrato(ContratoAlquiler*);
    ContratoAlquiler* buscar(string); // Busca un Contrato por su código
    bool eliminar(string); // Elimina un Contrato por su código

    // Getters y utilidades
    int getTamano();
    bool estaVacia();
    NodoContrato* getCab();

    // Función "to string" para mostrar todas los Contratos
    string toString();
};







#endif