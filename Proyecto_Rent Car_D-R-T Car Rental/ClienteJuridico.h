#ifndef CLIENTEJURIDICO_H
#define CLIENTEJURIDICO_H

#include <string>
#include <sstream>
#include "Cliente.h" // Hereda de Cliente
using namespace std;

class ClienteJuridico : public Cliente {
private:
    // Atributos espec�ficos del cliente jur�dico
    double porcentajeDescuento;
    string actividadEconomica;

public:
    // Constructor: Recibe todos los datos base m�s los datos de Jur�dico
    ClienteJuridico(string, string, string, string, char, string, string, double, string);

    // Destructor
    ~ClienteJuridico();

    // Getters
    double getPorcentajeDescuento();
    string getActividadEconomica();

    // Setters
    void setPorcentajeDescuento(double desc);
    void setActividadEconomica(string actEcon);

    // Funci�n "to string"
    string toString();
};

#endif // CLIENTEJURIDICO_H
