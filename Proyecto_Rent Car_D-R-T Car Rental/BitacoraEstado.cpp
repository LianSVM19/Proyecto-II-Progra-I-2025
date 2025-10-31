#include "BitacoraEstado.h"
#include <iostream>

using namespace std;

// =====================================
// IMPLEMENTACIÓN DE NODOESTADO
// =====================================

NodoEstado::NodoEstado(Estado* e, NodoEstado* sig) {
    dato = e;
    siguiente = sig;
}

NodoEstado::~NodoEstado() {
    if (dato != NULL) {
        delete dato;
        dato = NULL;
    }
}

Estado* NodoEstado::getDato() { return dato; }
NodoEstado* NodoEstado::getSiguiente() { return siguiente; }
void NodoEstado::setSiguiente(NodoEstado* sig) { siguiente = sig; }


// =====================================
// IMPLEMENTACIÓN DE BITACORAESTADO (LISTA ENLAZADA)
// =====================================

// ----------------------
// Constructor 
// ----------------------
BitacoraEstado::BitacoraEstado() {
    cab = NULL;
}

// ----------------------
// Destructor 
// ----------------------
BitacoraEstado::~BitacoraEstado() {
    NodoEstado* actual = cab;
    NodoEstado* siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
    cab = NULL;
}

// ----------------------
// Getters y Setters de BitacoraEstado
// ----------------------

NodoEstado* BitacoraEstado::getCab() {
    return cab;
}

void BitacoraEstado::setCab(NodoEstado* nuevaCab) {
    cab = nuevaCab;
}

// ----------------------
// Agregar Estado 
// ----------------------
void BitacoraEstado::agregarEstado(Estado* nuevoEstado) {

    NodoEstado* nuevo = new NodoEstado(nuevoEstado);

    if (cab == NULL) {
        cab = nuevo;
    }
    else {
        NodoEstado* actual = cab;
        while (actual->getSiguiente() != NULL) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevo);
    }
}

// ----------------------
// Función "to string" 
// ----------------------
string BitacoraEstado::toString() {
    stringstream s;
    NodoEstado* actual = cab;
    int contador = 1;

    s << "\t\t--- BITÁCORA DE ESTADOS (Crecimiento Indefinido) ---" << endl;

    if (actual == NULL) {
        s << "\t\tLa Bitácora está vacía." << endl;
    }
    else {
        while (actual != NULL) {
            s << "\t\t" << contador << ". ";
            s << actual->getDato()->toString();

            actual = actual->getSiguiente();
            contador++;
        }
    }
    s << "\t\t-----------------------------------------------------" << endl;
    return s.str();
}
