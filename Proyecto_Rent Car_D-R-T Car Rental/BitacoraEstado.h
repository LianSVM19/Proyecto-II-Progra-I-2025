#ifndef BITACORAESTADO_H
#define BITACORAESTADO_H

#include <string>
#include <sstream>
#include "Estado.h" 

using namespace std;

// Clase Auxiliar para el Enlace de Nodos
class NodoEstado {
private:
    Estado* dato;
    NodoEstado* siguiente;
public:
    NodoEstado(Estado*, NodoEstado* = NULL);
    ~NodoEstado();
    Estado* getDato();
    NodoEstado* getSiguiente();
    void setSiguiente(NodoEstado* );
};


class BitacoraEstado {
private:
    NodoEstado* cab;

public:
    // Constructor
    BitacoraEstado();

    // Destructor 
    ~BitacoraEstado();

    // Getters
    NodoEstado* getCab();

    // Setters (Sin const - Opcional, para reemplazar toda la lista si es necesario)
    void setCab(NodoEstado*);

    // M�todo para agregar un nuevo estado
    void agregarEstado(Estado*);

    // Funci�n "to string"
    string toString();
};

#endif
