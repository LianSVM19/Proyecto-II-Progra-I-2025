
#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include <string>
#include <sstream>
#include "Nodo.h" // Incluye la definición del Nodo que almacena Vehiculo*

using namespace std;

class ListaEnlazada {
private:
    Nodo* cabeza; // Puntero al primer nodo
    int tamano;

public:
    // Constructor
    ListaEnlazada();

    // Destructor (liberará toda la lista y los Vehiculos asociados)
    ~ListaEnlazada();

    // Métodos de gestión de la colección
    void agregarAlInicio(Vehiculo*);
    // Vehiculo* buscar(const string& placaBuscada) const; // Pendiente de implementar
    // bool eliminar(const string& placaEliminar); // Pendiente de implementar

    // Getters y utilidades
    int getTamano() ;
    bool estaVacia() ;

    // Función "to string"
    string toString();
};

#endif // LISTAENLAZADA_H
