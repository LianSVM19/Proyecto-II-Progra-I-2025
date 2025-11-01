
#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include <string>
#include <sstream>
#include "Nodo.h" // Incluye la definici�n del Nodo que almacena Vehiculo*

using namespace std;

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
    // Vehiculo* buscar(const string& placaBuscada) const; // Pendiente de implementar
    // bool eliminar(const string& placaEliminar); // Pendiente de implementar

    // Getters y utilidades
    int getTamano() ;
    bool estaVacia() ;

    // Funci�n "to string"
    string toString();
};

#endif // LISTAENLAZADA_H
