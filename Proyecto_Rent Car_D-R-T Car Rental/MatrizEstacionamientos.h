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
    // Constructor: Asigna toda la memoria din�micamente
    MatrizEstacionamientos(int f, int c);

    // Destructor: Libera las tres capas de memoria din�mica
    ~MatrizEstacionamientos();

    // M�todos de acceso
    int getFilas() const;
    int getColumnas() const;
    Estacionamiento* getEstacionamiento(int fila, int columna) const;

    // Funci�n "to string"
    string toString() const;
};

#endif
