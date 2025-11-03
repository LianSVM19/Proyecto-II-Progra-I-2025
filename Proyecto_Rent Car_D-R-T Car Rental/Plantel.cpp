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

// Representación textual y gráfica del plantel
string Plantel::toString() {
    stringstream s;
    s << "\t\t************************************************" << endl;
    s << "\t\t--- INFORMACION DEL PLANTEL DE ESTACIONAMIENTO ---" << endl;
    s << "\t\tCodigo de Plantel: " << codigoPlantel << endl;
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

void Plantel::mostrarMatriz() {
    cout << "\n\t\t=== DISTRIBUCION DEL PLANTEL ===" << endl;
    cout << "\t\tCodigo: " << codigoPlantel
        << " | Tipo: " << tipoPlantel
        << " | Dimension: " << capacidadFilas
        << "x" << capacidadColumnas << endl;

    if (matrizEstacionamientos != nullptr) {
        matrizEstacionamientos->mostrarMatriz();
    }
    else {
        cout << "\t\tERROR: La matriz de estacionamientos no está inicializada." << endl;
    }
}

Estacionamiento* Plantel::recomendarEspacio() {
    return matrizEstacionamientos->recomendarEspacioLibre();
}

int Plantel::getTotalEspacios(){
    if (matrizEstacionamientos == nullptr) return 0;
    return matrizEstacionamientos->getFilas() * matrizEstacionamientos->getColumnas();
}

int Plantel::getOcupados(){
    if (matrizEstacionamientos == nullptr) return 0;
    int ocupados = 0;
    for (int i = 0; i < matrizEstacionamientos->getFilas(); ++i) {
        for (int j = 0; j < matrizEstacionamientos->getColumnas(); ++j) {
            Estacionamiento* e = matrizEstacionamientos->getEstacionamiento(i, j);
            if (e != nullptr && e->getOcupado())
                ocupados++;
        }
    }
    return ocupados;
}