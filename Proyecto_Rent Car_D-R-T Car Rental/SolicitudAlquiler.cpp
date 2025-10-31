#include "SolicitudAlquiler.h"
SolicitudAlquiler::SolicitudAlquiler(string cod, Cliente* cli, Colaborador* col,
    Sucursal* suc, Vehiculo* veh, string feI, string feF) {
    codigoSolicitud = cod;
    Clien = cli;
    Colabora = col;
    Sucu = suc;
    Vehi = veh;
    fechIni = feI;
    fechFin = feF;
    canDiasAlqui = 0;
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
    s << "\t\tC�digo de Solicitud: " << codigoSolicitud << endl;
    s << "\t\tDuraci�n del Alquiler: " << canDiasAlqui << " d�as" << endl;
    s << "\t\tPer�odo Solicitado: " << fechIni << " al " << fechFin << endl;
    s << "\t\t-------------------------------------------------" << endl;

    // --- INFORMACI�N DEL CLIENTE ---
    if (Clien != NULL) {
        s << "\t\tCLIENTE SOLICITANTE (ID: " << Clien->getCedula() << "):" << endl;
        s << Clien->toString();
    }
    else {
        s << "\t\tCLIENTE: [ERROR: Objeto NULL o no asignado]" << endl;
    }

    // --- INFORMACI�N DEL COLABORADOR ---
    if (Colabora != NULL) {
        s << "\t\tCOLABORADOR REGISTRA (ID: " << Colabora->getCedula() << "):" << endl;
        s << Colabora->toString();
    }
    else {
        s << "\t\tCOLABORADOR: [ERROR: Objeto NULL o no asignado]" << endl;
    }

    // --- INFORMACI�N DEL VEH�CULO ---
    // Asumo que Vehiculo tiene getPlaca()
    if (Vehi != NULL) {
        s << "\t\tVEH�CULO SOLICITADO (Placa: " << Vehi->getPlaca() << "):" << endl;
        s << Vehi->toString();
    }
    else {
        s << "\t\tVEH�CULO: [ERROR: Objeto NULL o no asignado]" << endl;
    }

    // --- INFORMACI�N DE LA SUCURSAL ---
    // Asumo que Sucursal tiene getCodigoSucursal()
    if (Sucu != NULL) {
        s << "\t\tSUCURSAL RECEPTORA (C�digo: " << Sucu->getCodigoSucursal() << "):" << endl;
        s << Sucu->toString();
    }
    else {
        s << "\t\tSUCURSAL: [ERROR: Objeto NULL o no asignado]" << endl;
    }

    s << "\t\t*************************************************" << endl;

    return s.str();
}