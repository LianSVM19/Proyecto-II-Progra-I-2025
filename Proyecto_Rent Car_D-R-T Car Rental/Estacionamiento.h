// Estacionamiento.h
#ifndef ESTACIONAMIENTO_H
#define ESTACIONAMIENTO_H

#include <string>
#include <sstream>

using namespace std;

class Estacionamiento {
private:
    string codigo;
    bool ocupado;

public:
    Estacionamiento(string cod);

    // Getters
    string getCodigo();
    bool getOcupado();

    // Setters
    void setCodigo(string cod);
    void setOcupado(bool estado);

    // Métodos especificos
    void ocupar();
    void desocupar();

    string toString();
};

#endif