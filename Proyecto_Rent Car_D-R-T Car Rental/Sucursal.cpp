#include "Sucursal.h" 

#include "ListaEnlazada.h"
#include "Plantel.h"


using namespace std;

// ----------------------
// Constructor (Asignaci�n Din�mica)
// ----------------------
Sucursal::Sucursal(string cod, string nom, string dir, string tel) {
    codigoSucursal = cod;
    nombre = nom;
    direccion = dir;
    telefono = tel;

    // **ASIGNACI�N DIN�MICA DE LA LISTA ENLAZADA**
    clientes = new ListaCliente();   
    colaboradores = new ListaColaborador();


    plantel = NULL;
}

// ----------------------
// Destructor (Liberaci�n de Memoria)
// ----------------------
Sucursal::~Sucursal() {


    if (plantel != NULL) {
        delete plantel;
        plantel = NULL;
    }
    if (clientes != NULL) { // <-- LIBERACI�N DE CLIENTES
        delete clientes;
        clientes = NULL;
    }

    if (colaboradores != NULL) { // <-- LIBERACI�N DE COLABORADORES
        delete colaboradores;
        colaboradores = NULL;
    }
}

// ----------------------
// Getters
// ----------------------
string Sucursal::getCodigoSucursal() { return codigoSucursal; }
string Sucursal::getNombre() { return nombre; }
string Sucursal::getDireccion() { return direccion; }
string Sucursal::getTelefono() { return telefono; }
Plantel* Sucursal::getPlantel() { return plantel; }
ListaCliente* Sucursal::getClientes() { return clientes; }        // <-- GETTER DE CLIENTES
ListaColaborador* Sucursal::getColaboradores() { return colaboradores; } // <-- GETTER DE COLABORADORES

// ----------------------
// Setters
// ----------------------
void Sucursal::setNombre(string nom) { nombre = nom; }
void Sucursal::setDireccion(string dir) { direccion = dir; }
void Sucursal::setTelefono(string tel) { telefono = tel; }
void Sucursal::setPlantel(Plantel* p) {
    if (plantel != NULL) {
        delete plantel;  // liberamos el anterior si exist�a
    }
    plantel = p;
}

// ----------------------
// Funci�n "to string"
// ----------------------
string Sucursal::toString() {
    stringstream s;

    s << "\t\t================================================" << endl;
    s << "\t\t--- INFORMACI�N DE LA SUCURSAL ---" << endl;
    s << "\t\tC�digo: " << codigoSucursal << endl;
    s << "\t\tNombre Comercial: " << nombre << endl;
    s << "\t\tDirecci�n: " << direccion << endl;
    s << "\t\tTel�fono: " << telefono << endl;
    s << "\t\t================================================" << endl;

    s << "\t\t--- PLANTEL DE ESTACIONAMIENTOS ---\n";
    if (plantel != NULL) {
        s << plantel->toString();
    }
    else {
        s << "\t\tNo hay plantel asignado a esta sucursal.\n";
    }

    s << "\t\t=============================================\n";

    s << "\t\t--- CLIENTES ASIGNADOS ---" << endl;
    if (clientes != NULL) {
        s << clientes->toString();
    }
    else {
        s << "\t\tERROR: La colecci�n de clientes no fue inicializada." << endl;
    }
    s << "\t\t------------------------------------------------" << endl;

    s << "\t\t--- COLABORADORES ASIGNADOS ---" << endl;
    if (colaboradores != NULL) {
        s << colaboradores->toString();
    }
    else {
        s << "\t\tERROR: La colecci�n de colaboradores no fue inicializada." << endl;
    }
    s << "\t\t================================================" << endl;

    return s.str();
}