#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <sstream>
#include "Persona.h" // Hereda de Persona

using namespace std;

class Cliente : public Persona {
private:
    // Atributos especificos del cliente
    string fechaNacimiento;
    string fechaInscripcion;

public:
    // Constructor: Recibe los datos base y los datos de Cliente
    Cliente(string, string, string, string, char, string, string);

    // Destructor
    ~Cliente();

    // Getters
    string getFechaNacimiento();
    string getFechaInscripcion();

    // Setters
    void setFechaNacimiento(string);
    void setFechaInscripcion(string);

    // Funcion "to string" 
    virtual string toString();
};

#endif