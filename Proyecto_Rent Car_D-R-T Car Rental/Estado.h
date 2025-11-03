#ifndef ESTADO_H
#define ESTADO_H

#include <string>
#include <sstream>

using namespace std;

class Estado {
private:
    string fecha;
    string descripcion;
    string ubicacion;

public:
    Estado(string, string, string);

    // Getters
    string getFecha();
    string getDescripcion();
    string getUbicacion();

    // Setters
    void setFecha(string);
    void setDescripcion(string);
    void setUbicacion(string);

    // Funcion "to string" 
    string toString();
};

#endif // ESTADO_H