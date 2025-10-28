#ifndef MATRIZESTACIONAMIENTOS_H
#define MATRIZESTACIONAMIENTOS_H

#include <string>
#include <sstream>
#include "Estacionamiento.h" // La clase que almacena

using namespace std;

class MatrizEstacionamientos {
private:
    // Estructura clave: Puntero a puntero a puntero (triple puntero)
    Estacionamiento*** matriz;
    int filas;
    int columnas;

public:
    // Constructor: Asigna toda la memoria dinámicamente
    MatrizEstacionamientos(int f, int c);

    // Destructor: Libera las tres capas de memoria dinámica
    ~MatrizEstacionamientos();

    // Métodos de acceso
    int getFilas() const;
    int getColumnas() const;
    Estacionamiento* getEstacionamiento(int fila, int columna) const;

    // Función "to string"
    string toString() const;
};

#endif
