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
    Estacionamiento(string cod) : codigo(cod), ocupado(false) {}

    void ocupar() { ocupado = true; }
    void desocupar() { ocupado = false; }
    bool estaOcupado() const { return ocupado; }
    string getCodigo() const { return codigo; }

    // Función "to string"
    string toString() const;
};

#endif