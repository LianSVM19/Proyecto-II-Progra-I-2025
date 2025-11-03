#include "Colaborador.h"

using namespace std;

// ----------------------
// Constructor
// ----------------------
// Llama al constructor de la clase base 'Persona' y luego asigna los atributos propios.
Colaborador::Colaborador(string ced, string nom, string corr, string tel, char s,
    string fIng, string pto)
    : Persona(ced, nom, corr, tel, s) {

    // Asignacion de atributos propios
    fechaIngreso = fIng;
    puesto = pto;
}

// ----------------------
// Destructor
// ----------------------
Colaborador::~Colaborador() {
}

// ----------------------
// Getters 
// ----------------------
string Colaborador::getFechaIngreso() { return fechaIngreso; }
string Colaborador::getPuesto() { return puesto; }

// ----------------------
// Setters 
// ----------------------
void Colaborador::setFechaIngreso(string fIng) { fechaIngreso = fIng; }
void Colaborador::setPuesto(string pto) { puesto = pto; }


// ----------------------
// Funcion "to string"
// ----------------------
string Colaborador::toString() {
    stringstream s;

    s << "\t\t************************************************" << endl;
    s << "\t\t--- INFORMACIoN DEL COLABORADOR ---" << endl;

    // 1. Llama a la funcion toString de la clase base para incluir sus datos
    s << Persona::toString();

    // 2. Agrega los atributos especificos del Colaborador
    s << "\t\tPuesto Ocupado: " << puesto << endl;
    s << "\t\tFecha de Ingreso: " << fechaIngreso << endl;

    s << "\t\t************************************************" << endl;

    return s.str();
}
