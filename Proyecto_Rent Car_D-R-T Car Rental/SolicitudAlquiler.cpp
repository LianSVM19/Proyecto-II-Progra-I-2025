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
}


SolicitudAlquiler::~SolicitudAlquiler() {
	Clien = NULL;
	Colabora = NULL;
	Sucu = NULL;
	Vehi = NULL;
}
\
void SolicitudAlquiler::setfechIni(string x) { fechIni = x; }
void SolicitudAlquiler::setfechFin(string x) { fechFin = x; }
void SolicitudAlquiler::setCodigoSoli(string x) { codigoSolicitud = x; }
void SolicitudAlquiler::setCanDiasAlqui(int x) { canDiasAlqui = x; }

string SolicitudAlquiler::getFechIni() { return fechIni; }
string SolicitudAlquiler::getFechFin() { return fechFin; }
string SolicitudAlquiler::getCodigoSoli() { return codigoSolicitud; }
int SolicitudAlquiler::getCanDiasAlqui() { return canDiasAlqui; }

string toString() {
	stringstream s;


	return s.str();
}