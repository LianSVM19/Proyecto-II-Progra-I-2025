// Sucursal.h
#ifndef SUCURSAL_H
#define SUCURSAL_H

#include <string>
#include <sstream>

// Declaraci�n Anticipada: Solo indica que existe una clase con este nombre, luego se le da el trabajo (include) al cpp por si hay que 
// incluir el .h en la lista enlazada final 
class ListaVehiculo;

using namespace std;

class Sucursal {
private:
    string codigoSucursal;
    string nombre;
    string direccion;
    string telefono;

    // El puntero va a la estructura de colecci�n
    ListaVehiculo* planteles;

public:
    // Constructor
    Sucursal(string, string, string, string);

    // Destructor
    ~Sucursal();

    // Getters 
    string getCodigoSucursal();
    string getNombre();
    string getDireccion();
    string getTelefono();
    ListaVehiculo* getPlanteles();

    // Setters
    void setNombre(string);
    void setDireccion(string);
    void setTelefono(string);

    // Funci�n "to string"
    string toString();
};

#endif