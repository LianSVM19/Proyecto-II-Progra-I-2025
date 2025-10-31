
#ifndef NODO_H
#define NODO_H

#include <string>
#include "Vehiculo.h" 

using namespace std;

class Nodo {
private:
    // Puntero para la asignación dinámica de memoria (requisito del proyecto)
    Vehiculo* elem;
    Nodo* sig;

public:
    // Constructor
    Nodo(Vehiculo* , Nodo* = NULL);

    // Destructor (CRÍTICO para liberar la memoria de 'elem')
    ~Nodo();

    // Setters
    void setElemento(Vehiculo*);
    void setSig(Nodo*);

    // Getters
    Vehiculo* getElemento(); // Retorna el puntero
    Nodo* getSig();

    // Función "to string"
    string toStringNodo();
};

#endif