#include "Estacionamiento.h"

using namespace std;

Estacionamiento::Estacionamiento(string cod) {
    codigo = cod;
    ocupado = false;
}

// ----------------------
// Getters
// ----------------------
string Estacionamiento::getCodigo() { return codigo; }
bool Estacionamiento::getOcupado() { return ocupado; }

// ----------------------
// Setters
// ----------------------
void Estacionamiento::setCodigo(string cod) { codigo = cod; }
void Estacionamiento::setOcupado(bool estado) { ocupado = estado; }

// ----------------------
// Métodos especificos
// ----------------------
void Estacionamiento::ocupar() { ocupado = true; }
void Estacionamiento::desocupar() { ocupado = false; }

string Estacionamiento::toString() {
    stringstream s;
    s << "\t\t\tEspacio Codigo: " << codigo << endl;
    s << "\t\t\tEstado: ";

    if (ocupado == true) {
        s << "OCUPADO";
    }
    else {
        s << "DISPONIBLE";
    }

    s << endl;
    return s.str();
}