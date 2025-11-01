#ifndef NODO_H
#define NODO_H

#include <string>
#include "Vehiculo.h" 

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

#endif