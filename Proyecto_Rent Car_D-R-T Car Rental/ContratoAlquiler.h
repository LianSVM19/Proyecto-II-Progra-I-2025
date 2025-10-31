#ifndef CONTRATOALQUILER_H
#define CONTRATOALQUILER_H

#include "SolicitudAlquiler.h" 

#include <string>
#include <sstream>

using namespace std;

class ContratoAlquiler {
private:
    string codigoContrato;
    double costoTotal;
    string estado;

    SolicitudAlquiler* solicitud;

public:
    // Constructor: 
    ContratoAlquiler(string, double, string, SolicitudAlquiler*);

    // Destructor
    ~ContratoAlquiler();

    // Getters y Setters
    string getCodigoContrato();
    double getCostoTotal();
    string getEstado();
    SolicitudAlquiler* getSolicitud();

    void setCodigoContrato(string);
    void setCostoTotal(double);
    void setEstado(string);
    void setSolicitud(SolicitudAlquiler*);

    string toString();
};

#endif