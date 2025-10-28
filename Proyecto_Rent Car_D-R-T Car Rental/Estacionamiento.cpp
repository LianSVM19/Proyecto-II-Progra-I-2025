#include "Estacionamiento.h"

using namespace std;

string Estacionamiento::toString() const {
    stringstream s;
    s << "\t\t\tEspacio Código: " << codigo << endl;
    s << "\t\t\tEstado: " << (ocupado ? "OCUPADO" : "DISPONIBLE") << endl;
    return s.str();
}