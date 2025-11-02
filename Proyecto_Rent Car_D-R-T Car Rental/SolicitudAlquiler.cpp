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
// Implementaci�n del toString()
// ----------------------
string SolicitudAlquiler::toString() {
    stringstream s;
    s << "\t\t*************************************************" << endl;
    s << "\t\t--- DOCUMENTO DE SOLICITUD DE ALQUILER ---" << endl;
    s << "\t\tC�digo Solicitud: " << codigoSolicitud << endl;
    s << "\t\tESTADO DE SOLICITUD: " << estado << endl; // (Estado)
    s << "\t\tD�as de Alquiler: " << canDiasAlqui << endl; // (D�as)
    s << "\t\tFecha de Inicio: " << fechIni << endl;
    s << "\t\tFecha de Entrega Estimada: " << fechFin << endl;
    s << "\t\tPrecio Diario: $" << (Vehi ? Vehi->getPrecioDiario() : 0.0) << endl; // (Precio Diario)
    s << "\t\tCosto Total Estimado: $" << precioTotal << endl; // (Precio Total)
    s << "\t\t-------------------------------------------------" << endl;

    // Inclusi�n de la informaci�n completa de entidades (Sucursal, Cliente, Veh�culo, Colaborador)
    s << "\t\tCLIENTE (C�dula: " << (Clien ? Clien->getCedula() : "N/A") << "):" << endl;
    if (Clien) s << Clien->toString();
    s << "\t\tCOLABORADOR (ID: " << (Colabora ? Colabora->getCedula() : "N/A") << "):" << endl;
    if (Colabora) s << Colabora->toString();
    s << "\t\tVEH�CULO (Placa: " << (Vehi ? Vehi->getPlaca() : "N/A") << "):" << endl;
    if (Vehi) s << Vehi->toString();
    s << "\t\tSUCURSAL (C�digo: " << (Sucu ? Sucu->getCodigoSucursal() : "N/A") << "):" << endl;
    if (Sucu) s << Sucu->toString();

    s << "\t\t*************************************************" << endl;
    return s.str();
}