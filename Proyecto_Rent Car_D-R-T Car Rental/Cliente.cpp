#include "Cliente.h"

using namespace std;

// ----------------------
// Constructor
// ----------------------
// Llama al constructor de la clase base 'Persona' y luego asigna los atributos propios.
Cliente::Cliente(string ced, string nom, string corr, string tel, char s,
    string fNac, string fIns)
    : Persona(ced, nom, corr, tel, s) {

    // Asignacion de atributos propios
    fechaNacimiento = fNac;
    fechaInscripcion = fIns;
}

// ----------------------
// Destructor
// ----------------------
Cliente::~Cliente() {}

// ----------------------
// Getters 
// ----------------------
string Cliente::getFechaNacimiento() { return fechaNacimiento; }
string Cliente::getFechaInscripcion() { return fechaInscripcion; }

// ----------------------
// Setters 
// ----------------------
void Cliente::setFechaNacimiento(string fNac) { fechaNacimiento = fNac; }
void Cliente::setFechaInscripcion(string fIns) { fechaInscripcion = fIns; }


// ----------------------
// Funcion "to string" 
// ----------------------
string Cliente::toString() {
    stringstream s;

    s << "\t\t************************************************" << endl;
    s << "\t\t--- INFORMACION COMPLETA DEL CLIENTE (BASE) ---" << endl;

    // 1. Llama a la funcion toString de la clase base para incluir sus datos
    s << Persona::toString();

    s << "\t\tFecha Nacimiento Cliente: " << fechaNacimiento << endl;
    s << "\t\tFecha Inscripcion Cliente: " << fechaInscripcion << endl;

    s << "\t\t************************************************" << endl;

    return s.str();
}
