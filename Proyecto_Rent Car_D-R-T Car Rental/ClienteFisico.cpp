#include "ClienteFisico.h"

using namespace std;

// ----------------------
// Constructor
// ----------------------
// Simplemente pasa todos los par�metros al constructor de la clase base Cliente.
ClienteFisico::ClienteFisico(string ced, string nom, string corr, string tel, char s,
    string fNac, string fIns)
    : Cliente(ced, nom, corr, tel, s, fNac, fIns) {
    // Cuerpo del constructor vac�o
}

// ----------------------
// Destructor
// ----------------------
ClienteFisico::~ClienteFisico() {}


// ----------------------
// Funci�n "to string"
// ----------------------
string ClienteFisico::toString() {
    stringstream s;

    s << "\t\t************************************************" << endl;
    s << "\t\t--- CLIENTE F�SICO (PERSONA INDIVIDUAL) ---" << endl;

    // 1. Llama a la funci�n toString de la clase base Cliente
    // Esto incluir� la info de Persona y los datos de fechas del Cliente
    s << Cliente::toString();

    s << "\t\t------------------------------------------------" << endl;
    s << "\t\tEstado del Cliente: Persona F�sica Est�ndar." << endl;
    s << "\t\t************************************************" << endl;

    return s.str();
}
