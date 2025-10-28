#include "Estacionamiento.h"

using namespace std;

string Estacionamiento::toString() const {
    stringstream s;
    s << "\t\t\tEspacio C�digo: " << codigo << endl;
    s << "\t\t\tEstado: " << (ocupado ? "OCUPADO" : "DISPONIBLE") << endl;
    return s.str();
}