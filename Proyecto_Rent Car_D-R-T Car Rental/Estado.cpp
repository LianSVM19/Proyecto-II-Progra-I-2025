#include "Estado.h"

using namespace std;

Estado::Estado(string f, string d, string u) {
    fecha = f;
    descripcion = d;
    ubicacion = u;
}

// ----------------------
// Getters
// ----------------------
string Estado::getFecha() { return fecha; }
string Estado::getDescripcion() { return descripcion; }
string Estado::getUbicacion() { return ubicacion; }

// ----------------------
// Setters
// ----------------------
void Estado::setFecha(string f) { fecha = f; }
void Estado::setDescripcion(string d) { descripcion = d; }
void Estado::setUbicacion(string u) { ubicacion = u; }

// ----------------------
// Función "to string" 
// ----------------------
string Estado::toString() {
    stringstream s;
    s << "\t\t\t[ " << fecha << " ] - " << descripcion << " (Ubicación: " << ubicacion << ")" << endl;
    return s.str();
}