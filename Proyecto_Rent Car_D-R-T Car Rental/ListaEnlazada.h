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

    // Getters y utilidades
    int getTamano();
    bool estaVacia();

    // Función "to string" para mostrar todos los clientes
    string toString();
};

#endif