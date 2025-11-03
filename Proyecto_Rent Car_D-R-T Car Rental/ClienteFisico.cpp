#include "ClienteFisico.h"

using namespace std;

// ----------------------
// Constructor
// ----------------------
// Simplemente pasa todos los parametros al constructor de la clase base Cliente.
ClienteFisico::ClienteFisico(string ced, string nom, string corr, string tel, char s,
    string fNac, string fIns)
    : Cliente(ced, nom, corr, tel, s, fNac, fIns) {
    // Cuerpo del constructor vacio
}

// ----------------------
// Destructor
// ----------------------
ClienteFisico::~ClienteFisico() {}


// ----------------------
// Funcion "to string"
// ----------------------
string ClienteFisico::toString() {
    stringstream s;

    s << "\t\t************************************************" << endl;
    s << "\t\t--- CLIENTE FISICO (PERSONA INDIVIDUAL) ---" << endl;

    // 1. Llama a la funcion toString de la clase base Cliente
    // Esto incluira la info de Persona y los datos de fechas del Cliente
    s << Cliente::toString();

    s << "\t\t------------------------------------------------" << endl;
    s << "\t\tEstado del Cliente: Persona Fisica Estandar." << endl;
    s << "\t\t************************************************" << endl;

    return s.str();
}
