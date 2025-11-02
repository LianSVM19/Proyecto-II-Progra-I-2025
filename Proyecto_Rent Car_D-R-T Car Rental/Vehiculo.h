
#ifndef VEHICULO_H
#define VEHICULO_H

#include <string>
#include <sstream>
#include "BitacoraEstado.h"

using namespace std;

class Vehiculo {
private:
    string placa;
    string marca;
    string modelo;
    double precioDiario; // Para mostrar un valor numérico
    char categoria;
    string tipoLicencia;
    string estado;
    BitacoraEstado* historialEstados;
public:
    // Constructor
    Vehiculo(string /*placa*/, string/*marca*/, string/*modelo*/, 
    string/*tipo licencia*/, char/*categoria*/, string/*estado*/);
    ~Vehiculo();
    void setPlaca(string );
    void setMarca(string );
    void setModelo(string );
    void setTipoLicencia(string);
    void setCategoria(char );
    void setEstado(string,string,string);


    string getPlaca();
    string getMarca();
    string getModelo();
    string getTipoLicencia();
    double getPrecioDiario();
    char getCategoria();
    string getEstado();
    BitacoraEstado* getHistorialEstados();
    string FechaActual();

    // Función "to string" con el estilo solicitado
    string toString() const;
};

#endif