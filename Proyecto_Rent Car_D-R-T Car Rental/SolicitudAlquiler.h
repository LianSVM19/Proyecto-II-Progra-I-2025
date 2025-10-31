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

	//setters
	void setfechIni(string);
	void setfechFin(string);
	void setCodigoSoli(string);
	void setCanDiasAlqui(int);

	//setters para punteros
	void setCliente(Cliente*);
	void setColaborador(Colaborador*);
	void setSucursal(Sucursal*);
	void setVehiculo(Vehiculo*);

	//getters
	string getFechIni();
	string getFechFin();
	string getCodigoSoli();
	int getCanDiasAlqui();

	//getters para punteros
	Cliente* getCliente();
	Colaborador* getColaborador();
	Sucursal* getSucursal();
	Vehiculo* getVehiculo();


	string toString();
};

#endif