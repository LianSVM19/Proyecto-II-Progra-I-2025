#include "SolicitudAlquiler.h"
SolicitudAlquiler::SolicitudAlquiler(string cod, Cliente* cli, Colaborador* col,
    Sucursal* suc, Vehiculo* veh, string feI, string feF, double pre, string esta) {
    codigoSolicitud = cod;
    Clien = cli;
    Colabora = col;
    Sucu = suc;
    Vehi = veh;
    fechIni = feI;
    fechFin = feF;
    canDiasAlqui = 0;
    precioTotal = pre;
    estado = esta;
}

SolicitudAlquiler::~SolicitudAlquiler() {
	Clien = NULL;
	Colabora = NULL;
	Sucu = NULL;
	Vehi = NULL;
}





// ----------------------
// Setters de Atributos
// ----------------------
void SolicitudAlquiler::setfechIni(string x) { fechIni = x; }
void SolicitudAlquiler::setfechFin(string x) { fechFin = x; }
void SolicitudAlquiler::setCodigoSoli(string x) { codigoSolicitud = x; }
void SolicitudAlquiler::setCanDiasAlqui(int x) { canDiasAlqui = x; }
void SolicitudAlquiler::setEstado(string x) { estado = x; }
void SolicitudAlquiler::setPrecioTotal(double x) { precioTotal = x; }

// ----------------------
// Setters de Punteros
// ----------------------
void SolicitudAlquiler::setCliente(Cliente* cli) { Clien = cli; }
void SolicitudAlquiler::setColaborador(Colaborador* col) { Colabora = col; }
void SolicitudAlquiler::setSucursal(Sucursal* suc) { Sucu = suc; }
void SolicitudAlquiler::setVehiculo(Vehiculo* veh) { Vehi = veh; }

// ----------------------
// Getters de Atributos
// ----------------------
string SolicitudAlquiler::getFechIni() { return fechIni; }
string SolicitudAlquiler::getFechFin() { return fechFin; }
string SolicitudAlquiler::getCodigoSoli() { return codigoSolicitud; }
int SolicitudAlquiler::getCanDiasAlqui() { return canDiasAlqui; }
string SolicitudAlquiler::getEstado() { return estado; }
double SolicitudAlquiler::getPrecioTotal() { return precioTotal; }

// ----------------------
// Getters de Punteros 
// ----------------------
Cliente* SolicitudAlquiler::getCliente() { return Clien; }
Colaborador* SolicitudAlquiler::getColaborador() { return Colabora; }
Sucursal* SolicitudAlquiler::getSucursal() { return Sucu; }
Vehiculo* SolicitudAlquiler::getVehiculo() { return Vehi; }

// ----------------------
// Implementación del toString()
// ----------------------
string SolicitudAlquiler::toString() {
    stringstream s;
    s << "Solicitud Codigo: " << codigoSolicitud
        << " | Estado: " << estado
        << " | Dias: " << canDiasAlqui;

    if (Clien != NULL) {
        s << " | Cliente: " << Clien->getNombre();
    }
    else {
        s << " | Cliente: N/A";
    }

    if (Vehi != NULL) {
        s << " | Vehiculo: " << Vehi->getPlaca();
    }
    else {
        s << " | Vehiculo: N/A";
    }

    return s.str();
}