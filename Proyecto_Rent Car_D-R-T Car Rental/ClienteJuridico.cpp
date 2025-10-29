// ClienteJuridico.cpp
#include "ClienteJuridico.h"

using namespace std;

// ----------------------
// Constructor
// ----------------------
// Llama al constructor de la clase base 'Cliente' y luego asigna los atributos propios.
ClienteJuridico::ClienteJuridico(string ced, string nom, string corr, string tel, char s,
    string fNac, string fIns, double desc, string actEcon)
    : Cliente(ced, nom, corr, tel, s, fNac, fIns) {

    // Asignación de atributos propios
    porcentajeDescuento = desc;
    actividadEconomica = actEcon;
}

// ----------------------
// Destructor
// ----------------------
ClienteJuridico::~ClienteJuridico() {}

// ----------------------
// Getters 
// ----------------------
double ClienteJuridico::getPorcentajeDescuento() { return porcentajeDescuento; }
string ClienteJuridico::getActividadEconomica() { return actividadEconomica; }

// ----------------------
// Setters 
// ----------------------
void ClienteJuridico::setPorcentajeDescuento(double desc) { porcentajeDescuento = desc; }
void ClienteJuridico::setActividadEconomica(string actEcon) { actividadEconomica = actEcon; }


// ----------------------
// Función "to string"
// ----------------------
string ClienteJuridico::toString() {
    stringstream s;

    s << "\t\t************************************************" << endl;
    s << "\t\t--- CLIENTE JURÍDICO (EMPRESA) ---" << endl;

    // 1. Llama a la función toString de la clase base Cliente (Persona + fechas)
    s << Cliente::toString();

    // 2. Agrega los atributos específicos del Cliente Jurídico
    s << "\t\tActividad Económica: " << actividadEconomica << endl;
    s << "\t\tPorcentaje de Descuento: " << porcentajeDescuento << "%" << endl;

    s << "\t\t************************************************" << endl;

    return s.str();
}