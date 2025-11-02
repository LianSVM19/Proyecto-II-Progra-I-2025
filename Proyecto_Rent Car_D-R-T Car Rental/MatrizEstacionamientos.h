#ifndef MATRIZESTACIONAMIENTOS_H
#define MATRIZESTACIONAMIENTOS_H

#include <string>
#include <sstream>
#include "Estacionamiento.h" 

using namespace std;

class MatrizEstacionamientos {
private:
    // **TRIPLE PUNTERO para Matriz Din�mica**
    Estacionamiento*** matriz;
    int filas;
    int columnas;

public:
    // Constructor: Asigna toda la memoria din�micamente
    MatrizEstacionamientos(int, int);

    // Destructor: Libera las tres capas de memoria din�mica
    ~MatrizEstacionamientos();

    // Getters 
    int getFilas();
    int getColumnas();
    Estacionamiento* getEstacionamiento(int, int);

    // Setters 
    void setFilas(int);
    void setColumnas(int);

    // Funci�n "to string" 
    string toString();

    // Utilidad
    bool estaOcupado(int, int);
};

#endif
