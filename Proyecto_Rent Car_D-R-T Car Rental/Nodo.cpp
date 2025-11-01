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

// =====================================
// IMPLEMENTACIÓN DE NODOCLIENTE
// =====================================

NodoCliente::NodoCliente(Cliente* c, NodoCliente* sig) {
    dato = c;
    siguiente = sig;
}

NodoCliente::~NodoCliente() {
    // Si el dato no es nulo, liberamos el objeto Cliente (sea Físico o Jurídico)
    if (dato != NULL) {
        delete dato;
        dato = NULL;
    }
}

Cliente* NodoCliente::getDato() {
    return dato;
}

NodoCliente* NodoCliente::getSiguiente() {
    return siguiente;
}

void NodoCliente::setDato(Cliente* nuevoDato) {
    // Liberar la memoria antigua antes de reasignar
    if (dato != NULL) {
        delete dato;
    }
    dato = nuevoDato;
}

void NodoCliente::setSiguiente(NodoCliente* sig) {
    siguiente = sig;
}

string NodoCliente::toStringNodo() {
    stringstream s;
    s << "\t\t***********************************" << endl;
    if (dato != NULL) {
        // Llama al toString() del objeto Cliente (polimórfico)
        s << dato->toString();
    }else {
        s << "\t\tEl elemento (Cliente) del Nodo es NULL." << endl;
    }
    s << "\t\tPuntero Siguiente (siguiente): ";
    if (siguiente != NULL) {
        s << "ENLAZADO A OTRO NODO." << endl;
    }
    else {
        s << "NULL (Fin de la Lista)." << endl;
    }
    s << "\t\t***********************************" << endl;
    return s.str();
}
// =====================================
// IMPLEMENTACIÓN DE NODOCOLABORADOR
// =====================================

NodoColaborador::NodoColaborador(Colaborador* c, NodoColaborador* sig) {
    dato = c;
    siguiente = sig;
}

NodoColaborador::~NodoColaborador() {
    // Si el dato no es nulo, liberamos el objeto Cliente (sea Físico o Jurídico)
    if (dato != NULL) {
        delete dato;
        dato = NULL;
    }
}

Colaborador* NodoColaborador::getDato() {
    return dato;
}

NodoColaborador* NodoColaborador::getSiguiente() {
    return siguiente;
}

void NodoColaborador::setDato(Colaborador* nuevoDato) {
    // Liberar la memoria antigua antes de reasignar
    if (dato != NULL) {
        delete dato;
    }
    dato = nuevoDato;
}

void NodoColaborador::setSiguiente(NodoColaborador* sig) {
    siguiente = sig;
}

string NodoColaborador::toStringNodo() {
    stringstream s;
    s << "\t\t***********************************" << endl;
    if (dato != NULL) {
        // Llama al toString() del objeto Cliente (polimórfico)
        s << dato->toString();
    }
    else {
        s << "\t\tEl elemento (Cliente) del Nodo es NULL." << endl;
    }
    s << "\t\tPuntero Siguiente (siguiente): ";
    if (siguiente != NULL) {
        s << "ENLAZADO A OTRO NODO." << endl;
    }
    else {
        s << "NULL (Fin de la Lista)." << endl;
    }
    s << "\t\t***********************************" << endl;
    return s.str();
}

// =====================================
// IMPLEMENTACIÓN DE NODOSUCURSAL (NUEVO)
// =====================================

NodoSucursal::NodoSucursal(Sucursal* s, NodoSucursal* sig) {
    dato = s;
    siguiente = sig;
}

NodoSucursal::~NodoSucursal() {
    // CRÍTICO: El nodo es dueño de la memoria de la Sucursal, debe liberarla.
    if (dato != NULL) {
        delete dato;
        dato = NULL;
    }
}

Sucursal* NodoSucursal::getDato() {
    return dato;
}

NodoSucursal* NodoSucursal::getSiguiente() {
    return siguiente;
}

void NodoSucursal::setDato(Sucursal* nuevoDato) {
    // Si ya existe un elemento, liberamos la memoria antes de reasignar
    if (dato != NULL) {
        delete dato;
    }
    dato = nuevoDato;
}

void NodoSucursal::setSiguiente(NodoSucursal* sig) {
    siguiente = sig;
}

string NodoSucursal::toStringNodo() {
    stringstream s;
    s << "\t\t***********************************" << endl;
    if (dato != NULL) {
        // Llama al toString() del objeto Sucursal
        s << dato->toString();
    }
    else {
        s << "\t\tEl elemento (Sucursal) del Nodo es NULL." << endl;
    }
    s << "\t\tPuntero Siguiente (siguiente): ";
    if (siguiente != NULL) {
        s << "ENLAZADO A OTRO NODO." << endl;
    }
    else {
        s << "NULL (Fin de la Lista)." << endl;
    }
    s << "\t\t***********************************" << endl;
    return s.str();
}