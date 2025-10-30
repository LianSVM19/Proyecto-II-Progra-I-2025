
#ifndef VEHICULO_H
#define VEHICULO_H

#include <string>
#include <sstream>

using namespace std;

class Vehiculo {
private:
    string placa;
    string marca;
    string modelo;
    double precioDiario; // Para mostrar un valor numérico
    char categoria;
    string tipoLicencia;
    string estado;
public:
    // Constructor
    Vehiculo(string /*placa*/, string/*marca*/, string/*modelo*/, 
    string/*tipo licencia*/, double/*preciodiario*/,
    char/*categoria*/, string/*estado*/);
    Vehiculo();
    void setPlaca(string );
    void setMarca(string );
    void setModelo(string );
    void setTipoLicencia(string);
    void setPrecioDiario(double );
    void setCategoria(char );
    void setEstado(string);


    string getPlaca();
    string getMarca();
    string getModelo();
    string getTipoLicencia();
    double getPrecioDiario();
    char getCategoria();
    string getEstado();


    // Función "to string" con el estilo solicitado
    string toString() const;
};

#endif