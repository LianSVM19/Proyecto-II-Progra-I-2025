
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
    Nodo(Vehiculo* elem, Nodo* sig = nullptr);

    // Destructor (CRÍTICO para liberar la memoria de 'elem')
    ~Nodo();

    // Setters
    void setElemento(Vehiculo* nuevoElem);
    void setSig(Nodo* nuevoSig);

    // Getters
    Vehiculo* getElemento() const; // Retorna el puntero
    Nodo* getSig() const;

    // Función "to string"
    string toStringNodo() const;
};

#endif