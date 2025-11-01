
#include "Nodo.h"
#include <sstream>

using namespace std; // Aplicado

// ----------------------
// Constructor
// ----------------------
NodoVehiculo::NodoVehiculo(Vehiculo* el, NodoVehiculo* s) {
    elem = el;
    sig = s;
}

// ----------------------
// Destructor (Manejo de Memoria Dinámica)
// ----------------------
NodoVehiculo::~NodoVehiculo() {
    // Esencial: El nodo es dueño de la memoria de su elemento, debe liberarla.
    if (elem != NULL) {
        delete elem;
        elem = NULL;
    }
}

// ----------------------
// Setters
// ----------------------

void NodoVehiculo::setElemento(Vehiculo* nuevoElem) {
    // Si ya existe un elemento, se libera su memoria antes de reasignar
    if (elem != NULL) {
        delete elem;
    }
    elem = nuevoElem;
}

void NodoVehiculo::setSig(NodoVehiculo* nuevoSig) {
    sig = nuevoSig;
}

// ----------------------
// Getters
// ----------------------

Vehiculo* NodoVehiculo::getElemento(){
    return elem;
}

NodoVehiculo* NodoVehiculo::getSig() {
    return sig;
}

// ----------------------
// Función "to string" (siguiendo el estilo de tabulación y endl)
// ----------------------
string NodoVehiculo::toStringNodo() {
    stringstream s;

    s << "\t\t***********************************" << endl;

    if (elem != NULL) {
        // Llama al toString() del objeto Vehiculo apuntado por elem
        s << elem->toString();
    }
    else {
        s << "\t\tEl elemento (Vehículo) del Nodo es NULL." << endl;
    }

    s << "\t\tPuntero Siguiente (sig): ";
    if (sig != NULL) {
        s << "ENLAZADO A OTRO NODO." << endl;
    }
    else {
        s << "NULL (Fin de la Lista)." << endl;
    }

    s << "\t\t***********************************" << endl;

    return s.str();
}
