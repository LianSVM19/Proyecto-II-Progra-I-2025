// Colaborador.h
#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <string>
#include <sstream>
#include "Persona.h" // Hereda de Persona

using namespace std;

class Colaborador : public Persona {
private:
    // Atributos especificos del colaborador
    string fechaIngreso;
    string puesto;

public:
    // Constructor: Recibe los datos base y los datos de Colaborador
    Colaborador(string, string, string, string, char,
        string, string);

    // Destructor
    ~Colaborador();

    // Getters
    string getFechaIngreso();
    string getPuesto();

    // Setters
    void setFechaIngreso(string);
    void setPuesto(string);

    // Funcion "to string"
    string toString();
};

#endif