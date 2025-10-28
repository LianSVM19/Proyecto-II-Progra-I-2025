#include "Vehiculo.h"

using namespace std;

Vehiculo::Vehiculo(string p, string m, string mod, double pd) :
    placa(p), marca(m), modelo(mod), precioDiario(pd) {
}

// Implementación del toString con el estilo solicitado (usando sstream y endl)
string Vehiculo::toString() const {
    stringstream s;
    s << "\t\t--- Datos del Vehículo ---" << endl;
    s << "\t\tPlaca del Vehículo: " << placa << endl;
    s << "\t\tMarca: " << marca << endl;
    s << "\t\tModelo: " << modelo << endl;
    // Se muestra el double directamente, sin formateo con iomanip
    s << "\t\tPrecio Diario: " << precioDiario << endl;
    s << "\t\t--------------------------" << endl;

    return s.str();
}
