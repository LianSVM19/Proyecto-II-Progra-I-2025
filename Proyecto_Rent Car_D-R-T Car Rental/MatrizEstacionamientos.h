#ifndef MATRIZESTACIONAMIENTOS_H
#define MATRIZESTACIONAMIENTOS_H

#include <string>
#include <sstream>
#include "Estacionamiento.h" 

using namespace std;

class MatrizEstacionamientos {
private:
    // **TRIPLE PUNTERO para Matriz Dinámica**
    Estacionamiento*** matriz;
    int filas;
    int columnas;

public:
    // Constructor: Asigna toda la memoria dinámicamente
    MatrizEstacionamientos(int f, int c);

    // Destructor: Libera las tres capas de memoria dinámica
    ~MatrizEstacionamientos();

    // Getters 
    int getFilas();
    int getColumnas();
    Estacionamiento* getEstacionamiento(int fila, int columna);

    // Setters 
    void setFilas(int f);
    void setColumnas(int c);

    // Función "to string" 
    string toString();
};

#endif
