#include "Sucursal.h" 

#include "ListaEnlazada.h"

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
    planteles = new ListaVehiculo();
}

// ----------------------
// Destructor (Liberaci�n de Memoria)
// ----------------------
Sucursal::~Sucursal() {
    // Es CR�TICO liberar la memoria de la lista de planteles.
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

    s << "\t\t--- GESTI�N DE PLANTELES (Estacionamientos) ---" << endl;

    if (planteles != NULL) {
        
        s << planteles->toString();
    }
    else {
        s << "\t\tERROR: La colecci�n de planteles no fue inicializada." << endl;
    }

    s << "\t\t================================================" << endl;

    return s.str();
}