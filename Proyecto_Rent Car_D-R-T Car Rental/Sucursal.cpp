#include "Sucursal.h" 

#include "ListaEnlazada.h"

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
    planteles = new ListaVehiculo();
}

// ----------------------
// Destructor (Liberación de Memoria)
// ----------------------
Sucursal::~Sucursal() {
    // Es CRÍTICO liberar la memoria de la lista de planteles.
    if (planteles != NULL) {
        delete planteles;
        planteles = NULL;
    }
}

// ----------------------
// Getters
// ----------------------
string Sucursal::getCodigoSucursal() { return codigoSucursal; }
string Sucursal::getNombre() { return nombre; }
string Sucursal::getDireccion() { return direccion; }
string Sucursal::getTelefono() { return telefono; }
ListaVehiculo* Sucursal::getPlanteles() { return planteles; }

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
    s << "\t\tCódigo: " << codigoSucursal << endl;
    s << "\t\tNombre Comercial: " << nombre << endl;
    s << "\t\tDirección: " << direccion << endl;
    s << "\t\tTeléfono: " << telefono << endl;

    s << "\t\t--- GESTIÓN DE PLANTELES (Estacionamientos) ---" << endl;

    if (planteles != NULL) {
        
        s << planteles->toString();
    }
    else {
        s << "\t\tERROR: La colección de planteles no fue inicializada." << endl;
    }

    s << "\t\t================================================" << endl;

    return s.str();
}