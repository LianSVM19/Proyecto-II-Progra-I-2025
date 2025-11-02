#include "Plantel.h"
#include <iostream>

using namespace std;

// Constructor
Plantel::Plantel(string cod, string tipo, int filas, int columnas) {
    codigoPlantel = cod;
    tipoPlantel = tipo;
    capacidadFilas = filas;
    capacidadColumnas = columnas;

    matrizEstacionamientos = new MatrizEstacionamientos(filas, columnas);
}

// Destructor
Plantel::~Plantel() {
    if (matrizEstacionamientos != NULL) {
        delete matrizEstacionamientos;
        matrizEstacionamientos = NULL;
    }
}

// Getters
string Plantel::getCodigoPlantel() { return codigoPlantel; }
string Plantel::getTipoPlantel() { return tipoPlantel; }
int Plantel::getCapacidadFilas() { return capacidadFilas; }
int Plantel::getCapacidadColumnas() { return capacidadColumnas; }
MatrizEstacionamientos* Plantel::getMatrizEstacionamientos() { return matrizEstacionamientos; }

// Setters
void Plantel::setCodigoPlantel(string cod) { codigoPlantel = cod; }
void Plantel::setTipoPlantel(string tipo) { tipoPlantel = tipo; }
void Plantel::setCapacidadFilas(int filas) { if (filas > 0) capacidadFilas = filas; }
void Plantel::setCapacidadColumnas(int columnas) { if (columnas > 0) capacidadColumnas = columnas; }

// Representaci�n textual y gr�fica del plantel
string Plantel::toString() {
    stringstream s;
    s << "\t\t************************************************" << endl;
    s << "\t\t--- INFORMACI�N DEL PLANTEL DE ESTACIONAMIENTO ---" << endl;
    s << "\t\tC�digo de Plantel: " << codigoPlantel << endl;
    s << "\t\tTipo de Plantel: " << tipoPlantel << endl;
    s << "\t\tCapacidad Total: " << (capacidadFilas * capacidadColumnas) << " espacios" << endl;
    s << "\t\tDimensiones (Filas x Columnas): " << capacidadFilas << "x" << capacidadColumnas << endl;

    if (matrizEstacionamientos != NULL)
        s << matrizEstacionamientos->toString();
    else
        s << "\t\tERROR: La matriz no fue inicializada." << endl;

    s << "\t\t************************************************" << endl;
    return s.str();
}