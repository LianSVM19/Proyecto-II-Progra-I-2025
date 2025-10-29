#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <sstream>
#include "Persona.h" // Hereda de Persona

using namespace std;

class Cliente : public Persona {
private:
    // Atributos específicos del cliente
    string fechaNacimiento;
    string fechaInscripcion;

public:
    // Constructor: Recibe los datos base y los datos de Cliente
    Cliente(string, string, string, string, char, string, string);

    // Destructor (No virtual, por solicitud)
    ~Cliente();

    // Getters (Sin const)
    string getFechaNacimiento();
    string getFechaInscripcion();

    // Setters (Sin const)
    void setFechaNacimiento(string);
    void setFechaInscripcion(string);

    // Función "to string" (Sobrescrita sin virtual)
    string toString();
};

#endif