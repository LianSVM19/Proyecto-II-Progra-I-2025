#ifndef CLIENTEFISICO_H
#define CLIENTEFISICO_H

#include <string>
#include <sstream>
#include "Cliente.h" // Hereda de Cliente
using namespace std;

class ClienteFisico : public Cliente {
private:
    // No requiere atributos adicionales espec�ficos para una persona f�sica.
    // Utiliza todos los atributos heredados de Persona y Cliente.

public:
    // Constructor: Llama directamente al constructor de la clase base Cliente
    ClienteFisico(string, string, string, string, char, string, string);

    // Destructor (No virtual, por solicitud)
    ~ClienteFisico();

    // Funci�n "to string" (Sobrescrita sin virtual)
    string toString();
};

#endif
