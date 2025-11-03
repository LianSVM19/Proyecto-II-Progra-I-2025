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
            matriz[i][j] = new Estacionamiento(codigoSS.str(), NULL);
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



void MatrizEstacionamientos::setEstacionamiento(int f, int c, Estacionamiento* esta) {
    if ((f >= 0 && f < filas && c >= 0 && c < columnas) && !MatrizEstacionamientos::estaOcupado(f, c)) {
        if (matriz[f][c] != NULL) {
            delete matriz[f][c]; 
        }
        matriz[f][c] = esta;
    }
}

bool MatrizEstacionamientos::estaOcupado(int fila, int columna) {
    if (fila >= 0 && fila < filas && columna >= 0 && columna < columnas) {
        Estacionamiento* e = matriz[fila][columna];
        return e != NULL && e->getOcupado();
    }
    return false;
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

Estacionamiento* MatrizEstacionamientos::buscarEstacionamiento(string codEspacio) {
    // Itera sobre las filas
    for (int i = 0; i < filas; i++) {
        // Itera sobre las columnas
        for (int j = 0; j < columnas; j++) {

            Estacionamiento* espacio = matriz[i][j]; // Acceso directo al puntero de Estacionamiento

            // 1. Verifica que el espacio exista (no sea NULL)
            // 2. Compara el código del espacio con el código buscado.
            //    Asumo que la clase Estacionamiento tiene un método getCodigo().
            if (espacio != nullptr && espacio->getCodigo() == codEspacio) {
                return espacio; // Retorna el puntero al objeto Estacionamiento
            }
        }
    }
    // Si el bucle termina sin encontrar el código, retorna NULL (o nullptr)
    return nullptr;
}

void MatrizEstacionamientos::mostrarMatriz() {
    cout << "\t\t-------------------------------------" << endl;
    cout << "\t\tDISTRIBUCION GRAFICA DE ESPACIOS" << endl;
    cout << "\t\t-------------------------------------" << endl;

    for (int i = 0; i < filas; ++i) {
        cout << "\t\t"; // Sangría para formato de tabla
        for (int j = 0; j < columnas; ++j) {
            Estacionamiento* espacio = matriz[i][j];
            if (espacio == nullptr) {
                cout << "[ ] ";
            }
            else if (espacio->getOcupado()) {
                cout << "[X] ";
            }
            else {
                cout << "[ ] ";
            }
        }
        cout << "  <- Fila " << (char)('A' + i) << endl;
    }

    cout << "\t\t-------------------------------------" << endl;
    cout << "\t\t[ ] = Disponible | [X] = Ocupado" << endl;
}


Estacionamiento* MatrizEstacionamientos::recomendarEspacioLibre() {
    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < columnas; ++c) {
            Estacionamiento* e = matriz[f][c];
            if (e != nullptr && !e->getOcupado()) {
                return e;
            }
        }
    }
    return nullptr;
}