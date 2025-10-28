#include "MatrizEstacionamientos.h"

using namespace std;

// ----------------------
// Constructor (Asignación Dinámica de la Matriz)
// ----------------------
MatrizEstacionamientos::MatrizEstacionamientos(int f, int c)
    : filas(f), columnas(c), matriz(nullptr) {

    // 1. Asignar memoria para el arreglo de punteros a filas (Estacionamiento**)
    matriz = new Estacionamiento * *[filas];

    for (int i = 0; i < filas; ++i) {
        // 2. Asignar memoria para cada fila (arreglo de punteros a Estacionamiento*)
        matriz[i] = new Estacionamiento * [columnas];

        for (int j = 0; j < columnas; ++j) {
            // 3. Asignar memoria para cada objeto Estacionamiento

            // Generar código único (ej: A01, B10, etc.)
            stringstream codigoSS;
            codigoSS << (char)('A' + i);
            codigoSS << (j < 10 ? "0" : "") << j + 1; // +1 para que inicie en 01

            matriz[i][j] = new Estacionamiento(codigoSS.str());
        }
    }
}

// ----------------------
// Destructor (Liberación de Triple Capa CRÍTICO)
// ----------------------
MatrizEstacionamientos::~MatrizEstacionamientos() {
    if (matriz != nullptr) {
        for (int i = 0; i < filas; ++i) {
            if (matriz[i] != nullptr) {
                for (int j = 0; j < columnas; ++j) {
                    // 3. Liberar cada objeto Estacionamiento
                    delete matriz[i][j];
                }
                // 2. Liberar la fila (el arreglo de punteros)
                delete[] matriz[i];
            }
        }
        // 1. Liberar el arreglo principal
        delete[] matriz;
        matriz = nullptr;
    }
}

// ----------------------
// Getters
// ----------------------
int MatrizEstacionamientos::getFilas() const { return filas; }
int MatrizEstacionamientos::getColumnas() const { return columnas; }

Estacionamiento* MatrizEstacionamientos::getEstacionamiento(int fila, int columna) const {
    if (fila >= 0 && fila < filas && columna >= 0 && columna < columnas) {
        return matriz[fila][columna];
    }
    return nullptr; // Manejo de error o índice inválido
}

// ----------------------
// Función "to string"
// ----------------------
string MatrizEstacionamientos::toString() const {
    stringstream s;
    s << "\t\t=====================================" << endl;
    s << "\t\tVISUALIZACIÓN DE ESTACIONAMIENTOS" << endl;
    s << "\t\tFilas: " << filas << ", Columnas: " << columnas << endl;
    s << "\t\tLeyenda: [Código - E] (E=Ocupado/D=Disponible)" << endl;
    s << "\t\t-------------------------------------" << endl;

    for (int i = 0; i < filas; ++i) {
        s << "\t\t[FILA " << (char)('A' + i) << "]: ";
        for (int j = 0; j < columnas; ++j) {
            Estacionamiento* espacio = matriz[i][j];
            if (espacio != nullptr) {
                s << "[" << espacio->getCodigo() << "-"
                    << (espacio->estaOcupado() ? "O" : "D") << "] ";
            }
        }
        s << endl;
    }

    s << "\t\t=====================================" << endl;
    return s.str();
}
