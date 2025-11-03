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
    MatrizEstacionamientos(int, int);

    // Destructor: Libera las tres capas de memoria dinámica
    ~MatrizEstacionamientos();

    // Getters 
    int getFilas();
    int getColumnas();
    Estacionamiento* getEstacionamiento(int, int);

    // Setters 
    void setFilas(int);
    void setColumnas(int);
    void setEstacionamiento(int, int, Estacionamiento*);
    // Función "to string" 
    string toString();

    // Utilidad
    bool estaOcupado(int, int);
    Estacionamiento* buscarEstacionamiento(string);
    void mostrarMatriz();
    Estacionamiento* recomendarEspacioLibre();
};

#endif
