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
// Funcion "to string"
// ----------------------
string ContratoAlquiler::toString() {
    stringstream s;
    s << "Contrato Codigo: " << codigoContrato
        << " | Estado: " << estado
        << " | Costo Total: $" << costoTotal;
    if (solicitud != NULL)
        s << " | Solicitud Origen: " << solicitud->getCodigoSoli();
    return s.str();
}