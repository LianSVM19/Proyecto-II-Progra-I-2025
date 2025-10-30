// MatrizEstacionamientos.cpp
#include "MatrizEstacionamientos.h"
#include <iostream>

using namespace std;

// ----------------------
// Constructor (Asignación Dinámica de la Matriz)
// ----------------------
MatrizEstacionamientos::MatrizEstacionamientos(int f, int c) {
    filas = f;
    columnas = c;
    matriz = NULL;

    // 1. Asignar memoria para el arreglo principal
    matriz = new Estacionamiento * *[filas];

    for (int i = 0; i < filas; ++i) {
        // 2. Asignar memoria para cada fila (arreglo de punteros)
        matriz[i] = new Estacionamiento * [columnas];

        for (int j = 0; j < columnas; ++j) {
            // Generación de código
            stringstream codigoSS; //varible como el "s" que contiene texto
            codigoSS << (char)('A' + i);
            codigoSS << (j + 1 < 10 ? "0" : "") << j + 1;

            // 3. Asignar memoria para cada objeto Estacionamiento
            matriz[i][j] = new Estacionamiento(codigoSS.str());
        }
    }
}

// ----------------------
// Destructor (Liberación de Memoria TRIPLE PUNTERO)
// ----------------------
MatrizEstacionamientos::~MatrizEstacionamientos() {
    if (matriz != NULL) {
        for (int i = 0; i < filas; ++i) {
            if (matriz[i] != NULL) {
                for (int j = 0; j < columnas; ++j) {
                    // 3. Liberar cada objeto
                    delete matriz[i][j];
                }
                // 2. Liberar la fila
                delete[] matriz[i];
            }
        }
        // 1. Liberar el arreglo principal
        delete[] matriz;
        matriz = NULL;
    }
}

// ----------------------
// Getters 
// ----------------------
int MatrizEstacionamientos::getFilas() { return filas; }
int MatrizEstacionamientos::getColumnas() { return columnas; }

Estacionamiento* MatrizEstacionamientos::getEstacionamiento(int fila, int columna) {
    if (fila >= 0 && fila < filas && columna >= 0 && columna < columnas) {
        return matriz[fila][columna];
    }
    return NULL;
}

// ----------------------
// Setters
// ----------------------

// Nota: Cambiar las filas/columnas requiere reasignar TODA la matriz
// La implementación simplificada solo cambia los atributos, no la estructura en sí.
void MatrizEstacionamientos::setFilas(int f) {
    if (f > 0) filas = f;
}

void MatrizEstacionamientos::setColumnas(int c) {
    if (c > 0) columnas = c;
}

// ----------------------
// Función "to string"
// ----------------------
string MatrizEstacionamientos::toString() {
    stringstream s;

    s << "\t\t*************************************" << endl;
    s << "\t\t[MATRIZ DE ESTACIONAMIENTOS (" << filas << "x" << columnas << ")]" << endl;
    s << "\t\t-------------------------------------" << endl;
    s << "\t\tLeyenda: [Código - E] (O=Ocupado, D=Disponible)" << endl;
    s << "\t\t-------------------------------------" << endl;

    for (int i = 0; i < filas; ++i) {
        s << "\t\tFILA " << (char)('A' + i) << ": ";
        for (int j = 0; j < columnas; ++j) {
            Estacionamiento* espacio = matriz[i][j];
            if (espacio != NULL) {
                s << "[" << espacio->getCodigo() << "-"
                    << (espacio->getOcupado() ? "O" : "D") << "] ";
            }
        }
        s << endl;
    }

    s << "\t\t*************************************" << endl;
    return s.str();
}