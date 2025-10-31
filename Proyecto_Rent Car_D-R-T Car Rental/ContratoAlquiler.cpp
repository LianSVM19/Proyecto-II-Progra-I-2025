#include "ContratoAlquiler.h"
#include "SolicitudAlquiler.h"

using namespace std;

// ----------------------
// Constructor 
// ----------------------
ContratoAlquiler::ContratoAlquiler(string cod, double costo, string est, SolicitudAlquiler* sol) {
    codigoContrato = cod;
    costoTotal = costo;
    estado = est;
    solicitud = sol;
}

// ----------------------
// Destructor 
// ----------------------
ContratoAlquiler::~ContratoAlquiler() {
    solicitud = NULL;
}

// ----------------------
// Getters 
// ----------------------
string ContratoAlquiler::getCodigoContrato() { return codigoContrato; }
double ContratoAlquiler::getCostoTotal() { return costoTotal; }
string ContratoAlquiler::getEstado() { return estado; }
SolicitudAlquiler* ContratoAlquiler::getSolicitud() { return solicitud; }

// ----------------------
// Setters 
// ----------------------
void ContratoAlquiler::setCodigoContrato(string cod) { codigoContrato = cod; }
void ContratoAlquiler::setCostoTotal(double costo) { costoTotal = costo; }
void ContratoAlquiler::setEstado(string est) { estado = est; }
void ContratoAlquiler::setSolicitud(SolicitudAlquiler* sol) { solicitud = sol; }

// ----------------------
// Función "to string"
// ----------------------
string ContratoAlquiler::toString() {
    stringstream s;

    s << "\t\t*************************************************" << endl;
    s << "\t\t--- DOCUMENTO DE CONTRATO DE ALQUILER ---" << endl;
    s << "\t\tCódigo de Contrato: " << codigoContrato << endl;
    s << "\t\tCosto Total Acordado: $" << costoTotal << endl;
    s << "\t\tEstado del Contrato: " << estado << endl;
    s << "\t\t-------------------------------------------------" << endl;

    if (solicitud != NULL) {
        s << "\t\tSOLICITUD DE ORIGEN (Código: " << solicitud->getCodigoSoli() << "):" << endl;
        s << solicitud->toString();
    }
    else {
        s << "\t\tSOLICITUD: [ERROR: Objeto NULL o no asignado]" << endl;
    }

    s << "\t\t*************************************************" << endl;

    return s.str();
}
