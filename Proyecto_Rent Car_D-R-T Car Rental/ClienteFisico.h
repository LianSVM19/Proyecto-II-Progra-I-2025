#ifndef CLIENTEFISICO_H
#define CLIENTEFISICO_H

#include <string>
#include <sstream>
#include "Cliente.h" // Hereda de Cliente
using namespace std;

class ClienteFisico : public Cliente {
private:
    // No requiere atributos adicionales especificos para una persona fisica.
    // Utiliza todos los atributos heredados de Persona y Cliente.

public:
    // Constructor: Llama directamente al constructor de la clase base Cliente
    ClienteFisico(string, string, string, string, char, string, string);

    // Destructor 
    ~ClienteFisico();

    // Funcion "to string"
    string toString();
};

#endif
