#include "ListaEnlazada.h"

using namespace std;

ListaVehiculo::ListaVehiculo() : cabeza(NULL), tamano(0) {}

// ----------------------
// Destructor (CR�TICO: Liberaci�n total de memoria din�mica)
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
// Funci�n "to string" (siguiendo el estilo solicitado)
// ----------------------
string ListaVehiculo::toString() {
    stringstream s;
    s << "\t\t=====================================" << endl;
    s << "\t\tLISTA ENLAZADA: INVENTARIO DE VEH�CULOS" << endl;
    s << "\t\tTama�o actual de la lista: " << tamano << endl;
    s << "\t\t=====================================" << endl;

    if (cabeza == NULL) {
        s << "\t\tLa lista est� vac�a." << endl;
        return s.str();
    }

    NodoVehiculo* actual = cabeza;
    int contador = 1;
    while (actual != NULL) {
        s << "\t\t[POSICI�N #" << contador << "]:" << endl;
        // Llama al toStringNodo del Nodo para mostrar su contenido
        s << actual->toStringNodo();
        actual = actual->getSig();
        contador++;
    }

    s << "\t\tFIN DE LA LISTA." << endl;
    return s.str();
}


// =====================================
// IMPLEMENTACI�N DE LISTACLIENTE
// =====================================

// ----------------------
// Constructor (Inicializaci�n)
// ----------------------
ListaCliente::ListaCliente() : cab(NULL), tamano(0) {} // Usando inicializador de lista

// ----------------------
// Destructor (Liberaci�n de memoria de Nodos y Clientes)
// ----------------------
ListaCliente::~ListaCliente() {
    NodoCliente* actual = cab;
    NodoCliente* siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->getSiguiente();
        // El destructor de NodoCliente se encarga de liberar el objeto Cliente*
        delete actual;
        actual = siguiente;
    }
    cab = NULL;
    tamano = 0;
}

// ----------------------
// Agregar Cliente (Al final de la lista)
// ----------------------
void ListaCliente::agregarCliente(Cliente* c) {
    // 1. Crear el nuevo nodo
    NodoCliente* nuevoNodo = new NodoCliente(c);

    // 2. Si la lista est� vac�a, el nuevo nodo es la cabecera
    if (cab == NULL) {
        cab = nuevoNodo;
    }
    else {
        // 3. Buscar el �ltimo nodo
        NodoCliente* actual = cab;
        while (actual->getSiguiente() != NULL) {
            actual = actual->getSiguiente();
        }
        // 4. Enlazar el nuevo nodo al final
        actual->setSiguiente(nuevoNodo);
    }
    tamano++;
}

// ----------------------
// Getters y Utilidades
// ----------------------
int ListaCliente::getTamano() {
    return tamano;
}

bool ListaCliente::estaVacia() {
    return cab == NULL; // o return tamano == 0;
}

// ----------------------
// Funci�n "to string"
// ----------------------
string ListaCliente::toString() {
    stringstream s;
    s << "\t\t=====================================" << endl;
    s << "\t\tLISTA ENLAZADA: REGISTRO DE CLIENTES" << endl;
    s << "\t\tTama�o actual de la lista: " << tamano << endl;
    s << "\t\t=====================================" << endl;

    if (cab == NULL) {
        s << "\t\tLa lista de clientes est� vac�a." << endl;
        return s.str();
    }

    NodoCliente* actual = cab;
    int contador = 1;
    while (actual != NULL) {
        s << "\t\t[CLIENTE #" << contador << "]:" << endl;
        // Llama al toStringNodo del Nodo para mostrar su contenido
        s << actual->toStringNodo();
        actual = actual->getSiguiente();
        contador++;
    }

    s << "\t\tFIN DE LA LISTA." << endl;
    return s.str();
}