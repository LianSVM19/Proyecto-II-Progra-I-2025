#include "ListaEnlazada.h"

using namespace std;

ListaEnlazada::ListaEnlazada() : cabeza(nullptr), tamano(0) {}

// ----------------------
// Destructor (CRÍTICO: Liberación total de memoria dinámica)
// ----------------------
ListaEnlazada::~ListaEnlazada() {
    Nodo* actual = cabeza;
    Nodo* siguiente = nullptr;

    while (actual != nullptr) {
        siguiente = actual->getSig();
        // El destructor de Nodo libera el Vehiculo* y el puntero actual
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    tamano = 0;
}

// ----------------------
// Agregar (Al inicio, por simplicidad en el recorrido)
// ----------------------
void ListaEnlazada::agregarAlInicio(Vehiculo* nuevoDato) {
    // Se crea un nuevo Nodo con el puntero a Vehiculo
    Nodo* nuevoNodo = new Nodo(nuevoDato);

    // Enlace de punteros
    nuevoNodo->setSig(cabeza);
    cabeza = nuevoNodo;
    tamano++;
}

// ----------------------
// Getters y Utilidades
// ----------------------
int ListaEnlazada::getTamano() {
    return tamano;
}

bool ListaEnlazada::estaVacia() {
    return cabeza == nullptr;
}

// ----------------------
// Función "to string" (siguiendo el estilo solicitado)
// ----------------------
string ListaEnlazada::toString() {
    stringstream s;
    s << "\t\t=====================================" << endl;
    s << "\t\tLISTA ENLAZADA: INVENTARIO DE VEHÍCULOS" << endl;
    s << "\t\tTamaño actual de la lista: " << tamano << endl;
    s << "\t\t=====================================" << endl;

    if (cabeza == nullptr) {
        s << "\t\tLa lista está vacía." << endl;
        return s.str();
    }

    Nodo* actual = cabeza;
    int contador = 1;
    while (actual != nullptr) {
        s << "\t\t[POSICIÓN #" << contador << "]:" << endl;
        // Llama al toStringNodo del Nodo para mostrar su contenido
        s << actual->toStringNodo();
        actual = actual->getSig();
        contador++;
    }

    s << "\t\tFIN DE LA LISTA." << endl;
    return s.str();
}
