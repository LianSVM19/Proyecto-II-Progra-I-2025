#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include <sstream>
using namespace std;

class Persona {
private:
    string cedula;
    string nombre;
    string correo;
    string telefono;
    char sexo;

public:
    // Constructor
    Persona(string , string , string , string , char );

    // Destructor
    ~Persona();

    // Getters 
    string getCedula();
    string getNombre();
    string getCorreo();
    string getTelefono();
    char getSexo();

    // Setters 
    void setNombre(string );
    void setCorreo(string );
    void setTelefono(string );
    void setSexo(char );

    // Función "to string" 
    string toString();
};

#endif
