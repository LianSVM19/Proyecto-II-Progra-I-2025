#include "Sucursal.h" 

#include "ListaEnlazada.h"
#include "Plantel.h"


using namespace std;

// ----------------------
// Constructor (Asignación Dinámica)
// ----------------------
Sucursal::Sucursal(string cod, string nom, string dir, string tel) {
    codigoSucursal = cod;
    nombre = nom;
    direccion = dir;
    telefono = tel;

    // **ASIGNACIÓN DINÁMICA DE LA LISTA ENLAZADA**
    clientes = new ListaCliente();   
    colaboradores = new ListaColaborador();
    plantel = new ListaPlantel();
    inventarioVehiculos = new ListaVehiculo();
    solicitudes = new ListaSolicitud();
    Contratos = new ListaContrato();
}

// ----------------------
// Destructor (Liberación de Memoria)
// ----------------------
Sucursal::~Sucursal() {


    if (plantel != NULL) {
        delete plantel;
        plantel = NULL;
    }
    if (clientes != NULL) { // <-- LIBERACIÓN DE CLIENTES
        delete clientes;
        clientes = NULL;
    }

    if (colaboradores != NULL) { // <-- LIBERACIÓN DE COLABORADORES
        delete colaboradores;
        colaboradores = NULL;

    }

     if (inventarioVehiculos != NULL) {
        delete inventarioVehiculos;
        inventarioVehiculos = NULL;
    }

     if (solicitudes != NULL) {
         delete solicitudes;
         solicitudes = NULL;
     }

     if (Contratos!= NULL) {
         delete Contratos;
         Contratos = NULL;
     }
}





// ----------------------
// Getters
// ----------------------
string Sucursal::getCodigoSucursal() { return codigoSucursal; }
string Sucursal::getNombre() { return nombre; }
string Sucursal::getDireccion() { return direccion; }
string Sucursal::getTelefono() { return telefono; }
ListaPlantel* Sucursal::getListaPlantel() { return plantel; }
ListaCliente* Sucursal::getClientes() { return clientes; }        // <-- GETTER DE CLIENTES
ListaColaborador* Sucursal::getColaboradores() { return colaboradores; } // <-- GETTER DE COLABORADORES
ListaVehiculo* Sucursal::getListaVehiculos() { return inventarioVehiculos; }

// ----------------------
// Setters
// ----------------------
void Sucursal::setNombre(string nom) { nombre = nom; }
void Sucursal::setDireccion(string dir) { direccion = dir; }
void Sucursal::setTelefono(string tel) { telefono = tel; }

// ----------------------
// Función "to string"
// ----------------------
string Sucursal::toString() {
    stringstream s;

    s << "\t\t================================================" << endl;
    s << "\t\t--- INFORMACIÓN DE LA SUCURSAL ---" << endl;
    s << "\t\tCodigo: " << codigoSucursal << endl;
    s << "\t\tNombre Comercial: " << nombre << endl;
    s << "\t\tDirección: " << direccion << endl;
    s << "\t\tTeléfono: " << telefono << endl;
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
        s << "\t\tERROR: La coleccion de clientes no fue inicializada." << endl;
    }
    s << "\t\t------------------------------------------------" << endl;

    s << "\t\t--- COLABORADORES ASIGNADOS ---" << endl;
    if (colaboradores != NULL) {
        s << colaboradores->toString();
    }
    else {
        s << "\t\tERROR: La coleccion de colaboradores no fue inicializada." << endl;
    }
    s << "\t\t================================================" << endl;

    return s.str();
}

ListaContrato* getListaContratos() { return Contratos; }

void setListaContratos(ListaContrato* lc) { Contratos = lc; }


ListaSolicitud* Sucursal::getListaSolicitudes() {
    return solicitudes;
}

void Sucursal::setListaSolicitudes(ListaSolicitud* ls) {
    solicitudes = ls;
}

