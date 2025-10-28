
#ifndef NODO_H
#define NODO_H

#include <string>
#include "Vehiculo.h" 

using namespace std;

class Nodo {
private:
    // Puntero para la asignaci�n din�mica de memoria (requisito del proyecto)
    Vehiculo* elem;
    Nodo* sig;

public:
    // Constructor
    Nodo(Vehiculo* elem, Nodo* sig = nullptr);

    // Destructor (CR�TICO para liberar la memoria de 'elem')
    ~Nodo();

    // Setters
    void setElemento(Vehiculo* nuevoElem);
    void setSig(Nodo* nuevoSig);

    // Getters
    Vehiculo* getElemento() const; // Retorna el puntero
    Nodo* getSig() const;

    // Funci�n "to string"
    string toStringNodo() const;
};

#endif