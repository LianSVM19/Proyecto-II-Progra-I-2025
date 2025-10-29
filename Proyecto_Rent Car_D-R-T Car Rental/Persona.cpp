// Persona.cpp
#include "Persona.h"
#include <iostream> 

using namespace std;

// ----------------------
// Constructor
// ----------------------
Persona::Persona(string ced, string nom, string corr, string tel, char s) {
    // Las variables miembro se asignan una por una
    cedula = ced;
    nombre = nom;
    correo = corr;
    telefono = tel;
    sexo = s;
}

// ----------------------
// Destructor 
// ----------------------
Persona::~Persona() {}

// ----------------------
// Getters 
// ----------------------
string Persona::getCedula() { return cedula; }
string Persona::getNombre() { return nombre; }
string Persona::getCorreo() { return correo; }
string Persona::getTelefono() { return telefono; }
char Persona::getSexo() { return sexo; }

// ----------------------
// Setters 
// ----------------------
void Persona::setNombre(string nom) { nombre = nom; }
void Persona::setCorreo(string corr) { correo = corr; }
void Persona::setTelefono(string tel) { telefono = tel; }
void Persona::setSexo(char s) { sexo = s; }


// ----------------------
// Función "to string" 
// ----------------------
string Persona::toString() {
    stringstream s;

    s << "\t\t--- Datos de la Persona (Clase Base) ---" << endl;
    s << "\t\tCedula: " << cedula << endl;
    s << "\t\tNombre: " << nombre << endl;
    s << "\t\tCorreo: " << correo << endl;
    s << "\t\tTelefono de Contacto: " << telefono << endl;

    s << "\t\tSexo: ";

    if (sexo == 'm' || sexo == 'M') {
        s << "Masculino" << endl;
    }
    else if (sexo == 'f' || sexo == 'F') {
        s << "Femenino" << endl;
    }
    else {
        s << "El Sexo fue ingresado de manera incorrecta." << endl;
    }

    return s.str();
}
