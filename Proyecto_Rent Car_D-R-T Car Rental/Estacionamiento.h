// Estacionamiento.h
#ifndef ESTACIONAMIENTO_H
#define ESTACIONAMIENTO_H

#include <string>
#include <sstream>


using namespace std;
class Vehiculo;

class Estacionamiento {
private:
    string codigo;
    bool ocupado;
    Vehiculo* vehiculo;

public:
    Estacionamiento(string, Vehiculo*);

    // Getters
    string getCodigo();
    bool getOcupado();
    Vehiculo* getVehiculo();

    // Setters
    void setCodigo(string);
    void setOcupado(bool);
    void setVehiculo(Vehiculo*);

    // Métodos especificos
    void ocupar();
    void desocupar();

    string toString();
};

#endif