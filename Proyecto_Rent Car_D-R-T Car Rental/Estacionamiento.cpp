#include "Estacionamiento.h"
#include "Vehiculo.h"

using namespace std;

Estacionamiento::Estacionamiento(string cod, Vehiculo* vehi) {
    // Si el código viene vacío o con caracteres no válidos, se asigna uno por defecto
    if (cod.length() == 0) {
        codigo = "SIN-COD";
    }
    else {
        codigo = cod;
    }

    // Inicializar el puntero al vehículo
    if (vehi != NULL) {
        vehiculo = vehi;
        ocupado = true;  // Si ya viene con vehículo, está ocupado
    }
    else {
        vehiculo = NULL;
        ocupado = false; // Si no tiene vehículo, está libre
    }
}

// Getters
// ----------------------
string Estacionamiento::getCodigo() { return codigo; }
bool Estacionamiento::getOcupado() { return ocupado; }
Vehiculo* Estacionamiento::getVehiculo() { return vehiculo; }

// ----------------------
// Setters
// ----------------------
void Estacionamiento::setCodigo(string cod) { codigo = cod; }
void Estacionamiento::setOcupado(bool estado) { ocupado = estado; }
void Estacionamiento::setVehiculo(Vehiculo* v) { vehiculo = v; }

// ----------------------
// Metodos especificos
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