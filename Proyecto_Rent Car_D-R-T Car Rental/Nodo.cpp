
#include "Nodo.h"
#include <sstream>

using namespace std; // Aplicado

// ----------------------
// Constructor
// ----------------------
Nodo::Nodo(Vehiculo* el, Nodo* s) {
    elem = el;
    sig = s;
}

// ----------------------
// Destructor (Manejo de Memoria Din�mica)
// ----------------------
Nodo::~Nodo() {
    // Esencial: El nodo es due�o de la memoria de su elemento, debe liberarla.
    if (elem != NULL) {
        delete elem;
        elem = NULL;
    }
}

// ----------------------
// Setters
// ----------------------

void Nodo::setElemento(Vehiculo* nuevoElem) {
    // Si ya existe un elemento, se libera su memoria antes de reasignar
    if (elem != NULL) {
        delete elem;
    }
    elem = nuevoElem;
}

void Nodo::setSig(Nodo* nuevoSig) {
    sig = nuevoSig;
}

// ----------------------
// Getters
// ----------------------

Vehiculo* Nodo::getElemento(){
    return elem;
}

Nodo* Nodo::getSig() {
    return sig;
}

// ----------------------
// Funci�n "to string" (siguiendo el estilo de tabulaci�n y endl)
// ----------------------
string Nodo::toStringNodo() {
    stringstream s;

    s << "\t\t***********************************" << endl;

    if (elem != NULL) {
        // Llama al toString() del objeto Vehiculo apuntado por elem
        s << elem->toString();
    }
    else {
        s << "\t\tEl elemento (Veh�culo) del Nodo es NULL." << endl;
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
