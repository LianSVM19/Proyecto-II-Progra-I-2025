
#ifndef VEHICULO_H
#define VEHICULO_H

#include <string>
#include <sstream>

using namespace std;

class Vehiculo {
private:
    string placa;
    string marca;
    string modelo;
    double precioDiario; // Para mostrar un valor numérico
public:
    // Constructor
    Vehiculo(string p, string m, string mod, double pd);

    // Función "to string" con el estilo solicitado
    string toString() const;
};

#endif