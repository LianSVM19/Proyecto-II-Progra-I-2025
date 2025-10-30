#ifndef PLANTEL_H
#define PLANTEL_H

#include <string>
#include <sstream>
#include "MatrizEstacionamientos.h"

using namespace std;

class Plantel {
private:
    string codigoPlantel;
    string tipoPlantel; // Ejemplo: "Est�ndar", "Premium", "SUV"
    int capacidadFilas;
    int capacidadColumnas;

    // El plantel contiene la matriz de estacionamientos (Relaci�n de Composici�n)
    MatrizEstacionamientos* matrizEstacionamientos;

public:
    // Constructor: Inicializa la matriz din�mica
    Plantel(string, string, int, int);

    // Destructor (debe liberar la MatrizEstacionamientos)
    ~Plantel();

    // Getters 
    string getCodigoPlantel();
    string getTipoPlantel();
    int getCapacidadFilas();
    int getCapacidadColumnas();
    MatrizEstacionamientos* getMatrizEstacionamientos();

    // Setters
    void setCodigoPlantel(string);
    void setTipoPlantel(string);
    void setCapacidadFilas(int);
    void setCapacidadColumnas(int);


    // Funci�n "to string"
    string toString();
};

#endif