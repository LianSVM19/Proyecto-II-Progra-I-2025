#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include <string>
#include <sstream>
#include "Nodo.h" // Incluye la definici�n de NodoVehiculo y NodoCliente

using namespace std;

// =====================================
// DEFINICI�N DE LISTAVEHICULO
// =====================================
class ListaVehiculo {
private:
    NodoVehiculo* cabeza; // Puntero al primer nodo
    int tamano;

public:
    // Constructor
    ListaVehiculo();

    // Destructor (liberar� toda la lista y los Vehiculos asociados)
    ~ListaVehiculo();

    // M�todos de gesti�n de la colecci�n
    void agregarAlInicio(Vehiculo*);

    // Getters y utilidades
    int getTamano();
    bool estaVacia();

    // Funci�n "to string"
    string toString();
};

// =====================================
// DEFINICI�N DE LISTACLIENTE
// =====================================
class ListaCliente {
private:
    NodoCliente* cab;
    int tamano;

public:
    // Constructor (inicia la lista vac�a)
    ListaCliente();

    // Destructor (libera todos los nodos y sus clientes)
    ~ListaCliente();

    // M�todo para agregar un nuevo cliente al final de la lista
    void agregarCliente(Cliente* c);
    Cliente* buscar(string);
    bool eliminar(string);

    // Getters y utilidades
    Cliente* getCliente();
    int getTamano();
    bool estaVacia();

    // Funci�n "to string" para mostrar todos los clientes
    string toString();
};

// =====================================
// DEFINICI�N DE LISTACOLABORADOR
// =====================================
class ListaColaborador {
private:
    NodoColaborador* cab;
    int tamano;

public:
    // Constructor (inicia la lista vac�a)
    ListaColaborador();

    // Destructor (libera todos los nodos y sus Colaboradores)
    ~ListaColaborador();

    // M�todo para agregar un nuevo cliente al final de la lista
    void agregarColaborador(Colaborador* c);
    Colaborador* buscar(string);
    bool eliminar(string);

    // Getters y utilidades
    int getTamano();
    bool estaVacia();

    // Funci�n "to string" para mostrar todos los Colaboradores
    string toString();
};

// =====================================
// DEFINICI�N DE LISTASUCURSAL (NUEVO)
// =====================================
class ListaSucursal {
private:
    NodoSucursal* cab;
    int tamano;

public:
    // Constructor (inicia la lista vac�a)
    ListaSucursal();

    // Destructor (libera todos los nodos y sus sucursales)
    ~ListaSucursal();

    // M�todos de gesti�n de la colecci�n
    void agregarSucursal(Sucursal*);
    Sucursal* buscar(string); // Busca una sucursal por su c�digo
    bool eliminar(string); // Elimina una sucursal por su c�digo

    // Getters y utilidades
    int getTamano();
    bool estaVacia();

    // Funci�n "to string" para mostrar todas las sucursales
    string toString();
};
#endif