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

    // Getters y utilidades
    int getTamano();
    bool estaVacia();

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

    // Función "to string" para mostrar todos los Colaboradores
    string toString();
};

// =====================================
// DEFINICIÓN DE LISTASUCURSAL (NUEVO)
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

    // Función "to string" para mostrar todas las sucursales
    string toString();
};
#endif