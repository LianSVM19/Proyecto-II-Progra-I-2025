#ifndef SOLICITUDALQUILER_H
#define SOLICITUDALQUILER_H

#include "Cliente.h"
#include "Vehiculo.h"
#include "Sucursal.h"
#include "Colaborador.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class SolicitudAlquiler
	//Documento inicial del proceso de alquiler
{

private:
	string codigoSolicitud;
	Cliente* Clien;
	Colaborador* Colabora;
	Sucursal* Sucu;
	Vehiculo* Vehi;
	int canDiasAlqui;
	string fechIni;
	string fechFin;
public:
	SolicitudAlquiler(string, Cliente*, Colaborador*, Sucursal*, Vehiculo*, string, string);
	~SolicitudAlquiler();

	void setfechIni(string);
	void setfechFin(string);
	void setCodigoSoli(string);
	void setCanDiasAlqui(int);

	string getFechIni();
	string getFechFin();
	string getCodigoSoli();
	int getCanDiasAlqui();
	string toString();
};

#endif