#include "ListaEnlazada.h"

using namespace std;

ListaVehiculo::ListaVehiculo() : cabeza(NULL), tamano(0) {}

// ----------------------
// Destructor (CRiTICO: Liberacion total de memoria dinamica)
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

Vehiculo* ListaVehiculo::buscar(string placa) {
    NodoVehiculo* actual = cabeza;
    while (actual != NULL) {
        if (actual->getElemento()->getPlaca() == placa) {
            return actual->getElemento();
        }
        actual = actual->getSig();
    }
    return NULL;
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

bool ListaVehiculo::eliminarVehiculo(string placa) {
    if (cabeza == NULL) {
        return false; // Lista vacia
    }

    NodoVehiculo* actual = cabeza;
    NodoVehiculo* anterior = NULL;

    // Buscar el vehiculo con la placa dada
    while (actual != NULL) {
        Vehiculo* v = actual->getElemento();
        if (v != NULL && v->getPlaca() == placa) {
            // Caso 1: el nodo a eliminar es la cabeza
            if (anterior == NULL) {
                cabeza = actual->getSig();
            }
            else {
                anterior->setSig(actual->getSig());
            }

            // Liberar memoria
            delete actual;
            tamano--;
            return true;
        }

        anterior = actual;
        actual = actual->getSig();
    }

    return false; // No se encontro
}

bool ListaVehiculo::removerSinBorrar(string placa) {
    NodoVehiculo* actual = cabeza;
    NodoVehiculo* anterior = NULL;

    while (actual != NULL) {
        Vehiculo* v = actual->getElemento();
        if (v != NULL && v->getPlaca() == placa) {
            if (anterior == NULL)
                cabeza = actual->getSig();
            else
                anterior->setSig(actual->getSig());

            // ? No hacemos delete v; porque se movera a otra sucursal
            delete actual;
            tamano--;
            return true;
        }
        anterior = actual;
        actual = actual->getSig();
    }
    return false;
}



// ----------------------
// Funcion "to string" (siguiendo el estilo solicitado)
// ----------------------
string ListaVehiculo::toString() {
    stringstream s;
    s << "\t\t=====================================" << endl;
    s << "\t\tLISTA ENLAZADA: INVENTARIO DE VEHICULOS" << endl;
    s << "\t\tTama"<<char(164)<<"o actual de la lista : " << tamano << endl;
    s << "\t\t=====================================" << endl;

    if (cabeza == NULL) {
        s << "\t\tLa lista esta vacia." << endl;
        return s.str();
    }

    NodoVehiculo* actual = cabeza;
    int contador = 1;
    while (actual != NULL) {
        s << "\t\t[POSICION #" << contador << "]:" << endl;
        // Llama al toStringNodo del Nodo para mostrar su contenido
        s << actual->toStringNodo();
        actual = actual->getSig();
        contador++;
    }

    s << "\t\tFIN DE LA LISTA." << endl;
    return s.str();
}


// =====================================
// IMPLEMENTACIoN DE LISTACLIENTE
// =====================================

// ----------------------
// Constructor (Inicializacion)
// ----------------------
ListaCliente::ListaCliente() : cab(NULL), tamano(0) {} // Usando inicializador de lista

// ----------------------
// Destructor (Liberacion de memoria de Nodos y Clientes)
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

    // 2. Si la lista esta vacia, el nuevo nodo es la cabecera
    if (cab == NULL) {
        cab = nuevoNodo;
    }
    else {
        // 3. Buscar el ultimo nodo
        NodoCliente* actual = cab;
        while (actual->getSiguiente() != NULL) {
            actual = actual->getSiguiente();
        }
        // 4. Enlazar el nuevo nodo al final
        actual->setSiguiente(nuevoNodo);
    }
    tamano++;
}
Cliente* ListaCliente::buscar(string cedula) {
    NodoCliente* actual = cab;
    while (actual != NULL) {
        // Accedemos al Cliente* y luego a su metodo getCedula()
        if (actual->getDato()->getCedula() == cedula) {
            return actual->getDato();
        }
        actual = actual->getSiguiente();
    }
    return NULL; // Retorna NULL si no se encuentra
}

// ----------------------
// Eliminar Cliente por cedula
// ----------------------
bool ListaCliente::eliminar(string cedula) {
    if (cab == NULL) {
        return false;
    }

    NodoCliente* actual = cab;
    NodoCliente* anterior = NULL;

    // Caso 1: El nodo a eliminar es la cabeza
    if (actual != NULL && actual->getDato()->getCedula() == cedula) {
        cab = actual->getSiguiente();
        delete actual; // Llama al destructor de NodoCliente, liberando el Cliente*
        tamano--;
        return true;
    }

    // Caso 2: Buscar el nodo en el resto de la lista
    while (actual != NULL && actual->getDato()->getCedula() != cedula) {
        anterior = actual;
        actual = actual->getSiguiente();
    }

    // Si el nodo no se encontro
    if (actual == NULL) {
        return false;
    }

    // Desenlazar el nodo encontrado
    anterior->setSiguiente(actual->getSiguiente());
    delete actual; // Llama al destructor de NodoCliente, liberando el Cliente*
    tamano--;
    return true;
}

// ----------------------
// Getters y Utilidades
// ----------------------
int ListaCliente::getTamano() {
    return tamano;
}

Cliente* ListaCliente::getCliente() { //getCliente devuelve el Ultimo Cliente añadido.
    NodoCliente* actual = cab;
    while (actual != NULL) {
        // Accedemos al Cliente*
        if (actual->getSiguiente() == NULL) {
            return actual->getDato();
        }
        actual = actual->getSiguiente();
    }
    return NULL; // Retorna NULL si no se encuentra
}

bool ListaCliente::estaVacia() {
    return cab == NULL; // o return tamano == 0;
}

NodoCliente* ListaCliente::getCab() {
    return cab;
}


// ----------------------
// Funcion "to string"
// ----------------------
string ListaCliente::toString() {
    stringstream s;
    s << "\t\t=====================================" << endl;
    s << "\t\tLISTA ENLAZADA: REGISTRO DE CLIENTES" << endl;
 s << "\t\tTama"<<char(164)<<"o actual de la lista : " << tamano << endl;
    s << "\t\t=====================================" << endl;

    if (cab == NULL) {
        s << "\t\tLa lista de clientes esta vacia." << endl;
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

// =====================================
// IMPLEMENTACIoN DE LISTACOLABORADORES
// =====================================

// ----------------------
// Constructor (Inicializacion)
// ----------------------
ListaColaborador::ListaColaborador() : cab(NULL), tamano(0) {} // Usando inicializador de lista

// ----------------------
// Destructor (Liberacion de memoria de Nodos y Colaboradores)
// ----------------------
ListaColaborador::~ListaColaborador() {
    NodoColaborador* actual = cab;
    NodoColaborador* siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->getSiguiente();
        // El destructor de NodoColaborador se encarga de liberar el objeto Colaborador*
        delete actual;
        actual = siguiente;
    }
    cab = NULL;
    tamano = 0;
}

// ----------------------
// Agregar Colaborador (Al final de la lista)
// ----------------------
void ListaColaborador::agregarColaborador(Colaborador* c) {
    // 1. Crear el nuevo nodo
    NodoColaborador* nuevoNodo = new NodoColaborador(c);

    // 2. Si la lista esta vacia, el nuevo nodo es la cabecera
    if (cab == NULL) {
        cab = nuevoNodo;
    }
    else {
        // 3. Buscar el ultimo nodo
        NodoColaborador* actual = cab;
        while (actual->getSiguiente() != NULL) {
            actual = actual->getSiguiente();
        }
        // 4. Enlazar el nuevo nodo al final
        actual->setSiguiente(nuevoNodo);
    }
    tamano++;
}
// ----------------------
// Buscar Colaborador por ID
// ----------------------
Colaborador* ListaColaborador::buscar(string idColaborador) {
    NodoColaborador* actual = cab;
    while (actual != NULL) {
        // Accedemos al Colaborador* y luego a su metodo getId()
        if (actual->getDato()->getCedula() == idColaborador) {
            return actual->getDato();
        }
        actual = actual->getSiguiente();
    }
    return NULL; // Retorna NULL si no se encuentra
}
// ----------------------
// Eliminar Colaborador por ID
// ----------------------
bool ListaColaborador::eliminar(string idColaborador) {
    if (cab == NULL) {
        return false;
    }

    NodoColaborador* actual = cab;
    NodoColaborador* anterior = NULL;

    // Caso 1: El nodo a eliminar es la cabeza
    if (actual != NULL && actual->getDato()->getCedula() == idColaborador) {
        cab = actual->getSiguiente();
        delete actual; // Llama al destructor de NodoColaborador, liberando el Colaborador*
        tamano--;
        return true;
    }

    // Caso 2: Buscar el nodo en el resto de la lista
    while (actual != NULL && actual->getDato()->getCedula() != idColaborador) {
        anterior = actual;
        actual = actual->getSiguiente();
    }

    // Si el nodo no se encontro
    if (actual == NULL) {
        return false;
    }

    // Desenlazar el nodo encontrado
    anterior->setSiguiente(actual->getSiguiente());
    delete actual; // Llama al destructor de NodoColaborador, liberando el Colaborador*
    tamano--;
    return true;
}


// ----------------------
// Getters y Utilidades
// ----------------------
int ListaColaborador::getTamano() {
    return tamano;
}

bool ListaColaborador::estaVacia() {
    return cab == NULL; // o return tamano == 0;
}

Colaborador* ListaColaborador::getColaborador() {
    NodoColaborador* actual = cab;
    if (actual == NULL) return NULL;

    while (actual->getSiguiente() != NULL) {
        actual = actual->getSiguiente();
    }
    return actual->getDato();
}

NodoColaborador* ListaColaborador::getCab() {
    return cab;
}


// ----------------------
// Funcion "to string"
// ----------------------
string ListaColaborador::toString() {
    stringstream s;
    s << "\t\t=====================================" << endl;
    s << "\t\tLISTA ENLAZADA: REGISTRO DE COLABORADORES" << endl;
    s << "\t\tTama" << char(164) << "o actual de la lista : " << tamano << endl;
    s << "\t\t=====================================" << endl;

    if (cab == NULL) {
        s << "\t\tLa lista de colaboradores esta vacia." << endl;
        return s.str();
    }

    NodoColaborador* actual = cab;
    int contador = 1;
    while (actual != NULL) {
        s << "\t\t[COLABORADOR #" << contador << "]:" << endl;
        // Llama al toStringNodo del Nodo para mostrar su contenido
        s << actual->toStringNodo();
        actual = actual->getSiguiente();
        contador++;
    }

    s << "\t\tFIN DE LA LISTA." << endl;
    return s.str();
}
// =====================================
// IMPLEMENTACIoN DE LISTASUCURSAL
// =====================================

// ----------------------
// Constructor
// ----------------------
ListaSucursal::ListaSucursal() : cab(NULL), tamano(0) {}

// ----------------------
// Destructor (Liberacion de memoria de Nodos y Sucursales)
// ----------------------
ListaSucursal::~ListaSucursal() {
    NodoSucursal* actual = cab;
    NodoSucursal* siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->getSiguiente();
        // El destructor de NodoSucursal se encarga de liberar la Sucursal* y sus listas internas
        delete actual;
        actual = siguiente;
    }
    cab = NULL;
    tamano = 0;
}

NodoSucursal* ListaSucursal::getCab() {
    return cab;
}

// ----------------------
// Agregar Sucursal (Al final de la lista)
// ----------------------
void ListaSucursal::agregarSucursal(Sucursal* s) {
    NodoSucursal* nuevoNodo = new NodoSucursal(s);

    if (cab == NULL) {
        cab = nuevoNodo;
    }
    else {
        NodoSucursal* actual = cab;
        while (actual->getSiguiente() != NULL) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevoNodo);
    }
    tamano++;
}

// ----------------------
// Buscar Sucursal por codigo
// ----------------------
Sucursal* ListaSucursal::buscar(string codigo) {
    NodoSucursal* actual = cab;
    while (actual != NULL) {
        if (actual->getDato()->getCodigoSucursal() == codigo) {
            return actual->getDato();
        }
        actual = actual->getSiguiente();
    }
    return NULL;
}


// ----------------------
// Eliminar Sucursal por codigo
// ----------------------
bool ListaSucursal::eliminar(string codigo) {
    if (cab == NULL) {
        return false;
    }

    NodoSucursal* actual = cab;
    NodoSucursal* anterior = NULL;

    // Caso 1: El nodo a eliminar es la cabeza
    if (actual != NULL && actual->getDato()->getCodigoSucursal() == codigo) {
        cab = actual->getSiguiente();
        delete actual; // Se llama al destructor del NodoSucursal, liberando la Sucursal*
        tamano--;
        return true;
    }

    // Caso 2: Buscar el nodo en el resto de la lista
    while (actual != NULL && actual->getDato()->getCodigoSucursal() != codigo) {
        anterior = actual;
        actual = actual->getSiguiente();
    }

    // Si el nodo no se encontro
    if (actual == NULL) {
        return false;
    }

    // Desenlazar el nodo encontrado
    anterior->setSiguiente(actual->getSiguiente());
    delete actual; // Se llama al destructor del NodoSucursal, liberando la Sucursal*
    tamano--;
    return true;
}


// ----------------------
// Getters y Utilidades
// ----------------------
int ListaSucursal::getTamano() {
    return tamano;
}

bool ListaSucursal::estaVacia() {
    return cab == NULL;
}

// ----------------------
// Funcion "to string"
// ----------------------
string ListaSucursal::toString() {
    stringstream s;
    s << "\t\t=====================================" << endl;
    s << "\t\tLISTA ENLAZADA: REGISTRO DE SUCURSALES" << endl;
    s << "\t\tTama" << char(164) << "o actual de la lista : " << tamano << endl;
    s << "\t\t=====================================" << endl;

    if (cab == NULL) {
        s << "\t\tLa lista de sucursales esta vacia." << endl;
        return s.str();
    }

    NodoSucursal* actual = cab;
    int contador = 1;
    while (actual != NULL) {
        s << "\t\t[SUCURSAL #" << contador << "]:" << endl;
        // Llama al toStringNodo del Nodo para mostrar su contenido
        s << actual->toStringNodo();
        actual = actual->getSiguiente();
        contador++;
    }

    s << "\t\tFIN DE LA LISTA." << endl;
    return s.str();
}


// =====================================
// IMPLEMENTACIoN DE LISTAPLANTEL
// =====================================

// ----------------------
// Constructor
// ----------------------
ListaPlantel::ListaPlantel() : cab(NULL), tamano(0) {}

// ----------------------
// Destructor (Liberacion de memoria de Nodos yPlanteles)
// ----------------------
ListaPlantel::~ListaPlantel() {
    NodoPlantel* actual = cab;
    NodoPlantel* siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->getSiguiente();
        // El destructor de NodoSucursal se encarga de liberar el Plantel* y sus listas internas
        delete actual;
        actual = siguiente;
    }
    cab = NULL;
    tamano = 0;
}

// ----------------------
// Agregar Plantel (Al final de la lista)
// ----------------------
void ListaPlantel::agregarPlantel(Plantel* s) {
    NodoPlantel* nuevoNodo = new NodoPlantel(s);

    if (cab == NULL) {
        cab = nuevoNodo;
    }
    else {
        NodoPlantel* actual = cab;
        while (actual->getSiguiente() != NULL) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevoNodo);
    }
    tamano++;
}

// ----------------------
// Buscar Plantel por codigo
// ----------------------
Plantel* ListaPlantel::buscar(string codigo) {
    NodoPlantel* actual = cab;
    while (actual != NULL) {
        if (actual->getDato()->getCodigoPlantel() == codigo) {
            return actual->getDato();
        }
        actual = actual->getSiguiente();
    }
    return NULL;
}


// ----------------------
// Eliminar Plantel por codigo
// ----------------------
bool ListaPlantel::eliminar(string codigo) {
    if (cab == NULL) {
        return false;
    }

    NodoPlantel* actual = cab;
    NodoPlantel* anterior = NULL;

    // Caso 1: El nodo a eliminar es la cabeza
    if (actual != NULL && actual->getDato()->getCodigoPlantel() == codigo) {
        cab = actual->getSiguiente();
        delete actual; // Se llama al destructor del NodoPlantel, liberando el Plantel*
        tamano--;
        return true;
    }

    // Caso 2: Buscar el nodo en el resto de la lista
    while (actual != NULL && actual->getDato()->getCodigoPlantel() != codigo) {
        anterior = actual;
        actual = actual->getSiguiente();
    }

    // Si el nodo no se encontro
    if (actual == NULL) {
        return false;
    }

    // Desenlazar el nodo encontrado
    anterior->setSiguiente(actual->getSiguiente());
    delete actual; // Se llama al destructor del NodoPlantel, liberando el Plantel*
    tamano--;
    return true;
}


// ----------------------
// Getters y Utilidades
// ----------------------
int ListaPlantel::getTamano() {
    return tamano;
}

bool ListaPlantel::estaVacia() {
    return cab == NULL;
}

    NodoPlantel* ListaPlantel::getCab() {
        return cab;
    }

Sucursal* ListaSucursal::getSucursal() {
    NodoSucursal* actual = cab;
    while (actual != NULL) {
        // Accedemos al Sucursal* y luego a su metodo getId()
        if (actual->getSiguiente() == NULL) {
            return actual->getDato();
        }
    }
    return NULL; // Retorna NULL si no se encuentra
}

Plantel* ListaPlantel::buscarPorCodigo(string cod) {
    NodoPlantel* actual = cab;
    while (actual != NULL) {
        if (actual->getDato()->getCodigoPlantel() == cod)
            return actual->getDato();
        actual = actual->getSiguiente();
    }
    return NULL;
}

void ListaPlantel::mostrarCodigos() {
    NodoPlantel* actual = cab;
    while (actual != NULL) {
        Plantel* p = actual->getDato();
        cout << "\t\t- " << p->getCodigoPlantel() << " ("
            << p->getTipoPlantel() << ", "
            << p->getCapacidadFilas() << "x" << p->getCapacidadColumnas() << ")" << endl;
        actual = actual->getSiguiente();
    }
}


// ----------------------
// Funcion "to string"
// ----------------------
string ListaPlantel::toString() {
    stringstream s;
    s << "\t\t=====================================" << endl;
    s << "\t\tLISTA ENLAZADA: REGISTRO DE PLANTELES" << endl;
    s << "\t\tTama" << char(164) << "o actual de la lista : " << tamano << endl;
    s << "\t\t=====================================" << endl;

    if (cab == NULL) {
        s << "\t\tLa lista de planteles esta vacia." << endl;
        return s.str();
    }

    NodoPlantel* actual = cab;
    int contador = 1;
    while (actual != NULL) {
        s << "\t\t[PLANTEL #" << contador << "]:" << endl;
        // Llama al toStringNodo del Nodo para mostrar su contenido
        s << actual->toStringNodo();
        actual = actual->getSiguiente();
        contador++;
    }

    s << "\t\tFIN DE LA LISTA." << endl;
    return s.str();
}

// =====================================
// IMPLEMENTACIoN DE LISTASOLICITUD
// =====================================

// ----------------------
// Constructor
// ----------------------
ListaSolicitud::ListaSolicitud() : cab(NULL), tamano(0) {}

// ----------------------
// Destructor (Liberacion de memoria de Nodos y Solicitudes)
// ----------------------
ListaSolicitud::~ListaSolicitud() {
    NodoSolicitud* actual = cab;
    NodoSolicitud* siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->getSiguiente();
        // El destructor de NodoSolicitud se encarga de liberar la Solicitud* y sus listas internas
        delete actual;
        actual = siguiente;
    }
    cab = NULL;
    tamano = 0;
}

// ----------------------
// Agregar Solicitud (Al final de la lista)
// ----------------------
void ListaSolicitud::agregarSolicitud(SolicitudAlquiler* s) {
    NodoSolicitud* nuevoNodo = new NodoSolicitud(s);

    if (cab == NULL) {
        cab = nuevoNodo;
    }
    else {
        NodoSolicitud* actual = cab;
        while (actual->getSiguiente() != NULL) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevoNodo);
    }
    tamano++;
}

// ----------------------
// Buscar Solicitud por codigo
// ----------------------
SolicitudAlquiler* ListaSolicitud::buscar(string codigo) {
    NodoSolicitud* actual = cab;
    while (actual != NULL) {
        if (actual->getDato()->getCodigoSoli() == codigo) {
            return actual->getDato();
        }
        actual = actual->getSiguiente();
    }
    return NULL;
}


// ----------------------
// Eliminar Solicitud por codigo
// ----------------------
bool ListaSolicitud::eliminar(string codigo) {
    if (cab == NULL) {
        return false;
    }

    NodoSolicitud* actual = cab;
    NodoSolicitud* anterior = NULL;

    // Caso 1: El nodo a eliminar es la cabeza
    if (actual != NULL && actual->getDato()->getCodigoSoli() == codigo) {
        cab = actual->getSiguiente();
        delete actual; // Se llama al destructor del NodoSolicitud, liberando la Solicitud*
        tamano--;
        return true;
    }

    // Caso 2: Buscar el nodo en el resto de la lista
    while (actual != NULL && actual->getDato()->getCodigoSoli() != codigo) {
        anterior = actual;
        actual = actual->getSiguiente();
    }

    // Si el nodo no se encontro
    if (actual == NULL) {
        return false;
    }

    // Desenlazar el nodo encontrado
    anterior->setSiguiente(actual->getSiguiente());
    delete actual; // Se llama al destructor del NodoSolicitud, liberando la Solicitud*
    tamano--;
    return true;
}


// ----------------------
// Getters y Utilidades
// ----------------------
int ListaSolicitud::getTamano() {
    return tamano;
}

bool ListaSolicitud::estaVacia() {
    return cab == NULL;
}

NodoSolicitud* ListaSolicitud::getCab() {
    return cab;
}

// ----------------------
// Funcion "to string"
// ----------------------
string ListaSolicitud::toString() {
    stringstream s;
    s << "\t\t=====================================" << endl;
    s << "\t\tLISTA ENLAZADA: REGISTRO DE SOLICITUDES" << endl;
    s << "\t\tTama" << char(164) << "o actual de la lista : " << tamano << endl;
    s << "\t\t=====================================" << endl;

    if (cab == NULL) {
        s << "\t\tLa lista de solicitudes esta vacia." << endl;
        return s.str();
    }

    NodoSolicitud* actual = cab;
    int contador = 1;
    while (actual != NULL) {
        s << "\t\t[SOLICITUD #" << contador << "]:" << endl;
        // Llama al toStringNodo del Nodo para mostrar su contenido
        s << actual->toStringNodo();
        actual = actual->getSiguiente();
        contador++;
    }

    s << "\t\tFIN DE LA LISTA." << endl;
    return s.str();
}


// =====================================
// IMPLEMENTACIoN DE LISTACONTRATO
// =====================================

// ----------------------
// Constructor
// ----------------------
ListaContrato::ListaContrato() : cab(NULL), tamano(0) {}

// ----------------------
// Destructor (Liberacion de memoria de Nodos y Contratos)
// ----------------------
ListaContrato::~ListaContrato() {
    NodoContrato* actual = cab;
    NodoContrato* siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->getSiguiente();
        // El destructor de NodoContrato se encarga de liberar la Contrato* y sus listas internas
        delete actual;
        actual = siguiente;
    }
    cab = NULL;
    tamano = 0;
}

// ----------------------
// Agregar Contrato (Al final de la lista)
// ----------------------
void ListaContrato::agregarContrato(ContratoAlquiler* s) {
    NodoContrato* nuevoNodo = new NodoContrato(s);

    if (cab == NULL) {
        cab = nuevoNodo;
    }
    else {
        NodoContrato* actual = cab;
        while (actual->getSiguiente() != NULL) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevoNodo);
    }
    tamano++;
}

// ----------------------
// Buscar Contratopor codigo
// ----------------------
ContratoAlquiler* ListaContrato::buscar(string codigo) {
    NodoContrato* actual = cab;
    while (actual != NULL) {
        if (actual->getDato()->getCodigoContrato() == codigo) {
            return actual->getDato();
        }
        actual = actual->getSiguiente();
    }
    return NULL;
}


// ----------------------
// Eliminar Contrato por codigo
// ----------------------
bool ListaContrato::eliminar(string codigo) {
    if (cab == NULL) {
        return false;
    }

    NodoContrato* actual = cab;
    NodoContrato* anterior = NULL;

    // Caso 1: El nodo a eliminar es la cabeza
    if (actual != NULL && actual->getDato()->getCodigoContrato() == codigo) {
        cab = actual->getSiguiente();
        delete actual; // Se llama al destructor del NodoContrato, liberando la Contrato*
        tamano--;
        return true;
    }

    // Caso 2: Buscar el nodo en el resto de la lista
    while (actual != NULL && actual->getDato()->getCodigoContrato() != codigo) {
        anterior = actual;
        actual = actual->getSiguiente();
    }

    // Si el nodo no se encontro
    if (actual == NULL) {
        return false;
    }

    // Desenlazar el nodo encontrado
    anterior->setSiguiente(actual->getSiguiente());
    delete actual; // Se llama al destructor del NodoContrato, liberando laContrato*
    tamano--;
    return true;
}


// ----------------------
// Getters y Utilidades
// ----------------------
int ListaContrato::getTamano() {
    return tamano;
}

bool ListaContrato::estaVacia() {
    return cab == NULL;
}

NodoContrato* ListaContrato::getCab() {
    return cab;
}

// ----------------------
// Funcion "to string"
// ----------------------
string ListaContrato::toString() {
    stringstream s;
    s << "\t\t=====================================" << endl;
    s << "\t\tLISTA ENLAZADA: REGISTRO DE CONTRATOS" << endl;
    s << "\t\tTama" << char(164) << "o actual de la lista : " << tamano << endl;
    s << "\t\t=====================================" << endl;

    if (cab == NULL) {
        s << "\t\tLa lista de Contratos esta vacia." << endl;
        return s.str();
    }

    NodoContrato* actual = cab;
    int contador = 1;
    while (actual != NULL) {
        s << "\t\t[CONTRATO #" << contador << "]:" << endl;
        // Llama al toStringNodo del Nodo para mostrar su contenido
        s << actual->toStringNodo();
        actual = actual->getSiguiente();
        contador++;
    }

    s << "\t\tFIN DE LA LISTA." << endl;
    return s.str();
}
