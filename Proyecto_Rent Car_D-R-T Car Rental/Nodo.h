#ifndef NODO_H
#define NODO_H

#include <string>
#include "Vehiculo.h" 
#include "Cliente.h"

using namespace std;

class NodoVehiculo {
private:
    // Puntero para la asignación dinámica de memoria (requisito del proyecto)
    Vehiculo* elem;
    NodoVehiculo* sig;

public:
    // Constructor
    NodoVehiculo(Vehiculo* , NodoVehiculo* = NULL);

    // Destructor (CRÍTICO para liberar la memoria de 'elem')
    ~NodoVehiculo();

    // Setters
    void setElemento(Vehiculo*);
    void setSig(NodoVehiculo*);

    // Getters
    Vehiculo* getElemento(); // Retorna el puntero
    NodoVehiculo* getSig();

    // Función "to string"
    string toStringNodo();
};

class NodoCliente {
private:
    Cliente* dato;
    NodoCliente* siguiente;
public:
    // Constructor (recibe el cliente a almacenar y el puntero al siguiente nodo)
    NodoCliente(Cliente* c, NodoCliente* sig = NULL);

    // Destructor (debe liberar la memoria del cliente almacenado)
    ~NodoCliente();

    // Getters
    Cliente* getDato();
    NodoCliente* getSiguiente();

    // Setters
    void setSiguiente(NodoCliente* sig);
    void setDato(Cliente* nuevoDato);

    // Función "to string"
    string toStringNodo();
};


#endif