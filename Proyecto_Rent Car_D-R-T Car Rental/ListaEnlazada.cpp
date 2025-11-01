#include "ListaEnlazada.h"

using namespace std;

ListaVehiculo::ListaVehiculo() : cabeza(NULL), tamano(0) {}

// ----------------------
// Destructor (CRÍTICO: Liberación total de memoria dinámica)
// ----------------------
ListaVehiculo::~ListaVehiculo() {
    NodoVehiculo* actual = cabeza;
    NodoVehiculo* siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->getSig();
        // El destructor de Nodo libera el Vehiculo* y el puntero actual
        delete actual;
        actual = siguiente;
    }
    cabeza = NULL;
    tamano = 0;
}

// ----------------------
// Agregar (Al inicio, por simplicidad en el recorrido)
// ----------------------
void ListaVehiculo::agregarAlInicio(Vehiculo* nuevoDato) {
    // Se crea un nuevo Nodo con el puntero a Vehiculo
    NodoVehiculo* nuevoNodo = new NodoVehiculo(nuevoDato);

    // Enlace de punteros
    nuevoNodo->setSig(cabeza);
    cabeza = nuevoNodo;
    tamano++;
}

// ----------------------
// Getters y Utilidades
// ----------------------
int ListaVehiculo::getTamano() {
    return tamano;
}

bool ListaVehiculo::estaVacia() {
    return cabeza == NULL;
}

// ----------------------
// Función "to string" (siguiendo el estilo solicitado)
// ----------------------
string ListaVehiculo::toString() {
    stringstream s;
    s << "\t\t=====================================" << endl;
    s << "\t\tLISTA ENLAZADA: INVENTARIO DE VEHÍCULOS" << endl;
    s << "\t\tTamaño actual de la lista: " << tamano << endl;
    s << "\t\t=====================================" << endl;

    if (cabeza == NULL) {
        s << "\t\tLa lista está vacía." << endl;
        return s.str();
    }

    NodoVehiculo* actual = cabeza;
    int contador = 1;
    while (actual != NULL) {
        s << "\t\t[POSICIÓN #" << contador << "]:" << endl;
        // Llama al toStringNodo del Nodo para mostrar su contenido
        s << actual->toStringNodo();
        actual = actual->getSig();
        contador++;
    }

    s << "\t\tFIN DE LA LISTA." << endl;
    return s.str();
}
