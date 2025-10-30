#include "Plantel.h"
#include <iostream>

using namespace std;

// ----------------------
// Constructor (Asignaci�n Din�mica)
// ----------------------
Plantel::Plantel(string cod, string tipo, int filas, int columnas) {
    codigoPlantel = cod;
    tipoPlantel = tipo;
    capacidadFilas = filas;
    capacidadColumnas = columnas;

    // **ASIGNACI�N DIN�MICA DE LA ESTRUCTURA DE DATOS (MATRIZ)**
    // Se crea la MatrizEstacionamientos* con 'new'.
    matrizEstacionamientos = new MatrizEstacionamientos(filas, columnas);
}

// ----------------------
// Destructor (Liberaci�n de Memoria)
// ----------------------
Plantel::~Plantel() {
    if (matrizEstacionamientos != NULL) {
        delete matrizEstacionamientos;
        matrizEstacionamientos = NULL;
    }
}

// ----------------------
// Getters 
// ----------------------
string Plantel::getCodigoPlantel() { return codigoPlantel; }
string Plantel::getTipoPlantel() { return tipoPlantel; }
int Plantel::getCapacidadFilas() { return capacidadFilas; }
int Plantel::getCapacidadColumnas() { return capacidadColumnas; }

MatrizEstacionamientos* Plantel::getMatrizEstacionamientos() {return matrizEstacionamientos;}
// ----------------------
// Setters 
// ----------------------
void Plantel::setCodigoPlantel(string cod) {
    codigoPlantel = cod;
}

void Plantel::setTipoPlantel(string tipo) {
    tipoPlantel = tipo;
}

void Plantel::setCapacidadFilas(int filas) {
    if (filas > 0) {
        
        capacidadFilas = filas;
    }
}

void Plantel::setCapacidadColumnas(int columnas) {
    if (columnas > 0) {
       
        capacidadColumnas = columnas;
    }
}



// ----------------------
// Funci�n "to string"
// ----------------------
string Plantel::toString() {
    stringstream s;

    s << "\t\t************************************************" << endl;
    s << "\t\t--- INFORMACI�N DEL PLANTEL DE ESTACIONAMIENTO ---" << endl;
    s << "\t\tC�digo de Plantel: " << codigoPlantel << endl;
    s << "\t\tTipo de Plantel: " << tipoPlantel << endl;
    s << "\t\tCapacidad Total: " << (capacidadFilas * capacidadColumnas) << " espacios" << endl;
    s << "\t\tDimensiones (Filas x Columnas): " << capacidadFilas << "x" << capacidadColumnas << endl;

    if (matrizEstacionamientos != NULL) {
        // Llama al toString de la clase MatrizEstacionamientos
        s << "\t\t--- Distribuci�n de Estacionamientos ---" << endl;
        s << matrizEstacionamientos->toString();
    }
    else {
        s << "\t\tERROR: La matriz de estacionamientos no fue inicializada." << endl;
    }

    s << "\t\t************************************************" << endl;

    return s.str();
}