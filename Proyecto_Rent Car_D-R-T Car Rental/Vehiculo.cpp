#include "Vehiculo.h"

using namespace std;


//constructor sin finalizar
Vehiculo::Vehiculo(string p, string m, string mod, string tl, double pd, char c, string e) {
    
}


//set
void Vehiculo::setPlaca(string p) {
    this->placa = p;
};
void Vehiculo::setMarca(string m) {
    this->marca = m;
};
void Vehiculo::setModelo(string mod) {
    this->modelo = mod;
};
void Vehiculo::setTipoLicencia(string tl) {
    this->tipoLicencia = tl;
};
void Vehiculo::setPrecioDiario(double pd) {
    this->precioDiario = pd;
};
void Vehiculo::setCategoria(char c) {
    this->categoria = c;
};
void Vehiculo::setEstado(string e) {
    this->estado = e;
};



// get
string Vehiculo::getPlaca() {
    return placa;
};
string Vehiculo::getMarca() {
    return marca;
};
string Vehiculo::getModelo() {
    return modelo;
};
string Vehiculo::getTipoLicencia() {
    return tipoLicencia;
};
double Vehiculo::getPrecioDiario() {
    return precioDiario;
};
char Vehiculo::getCategoria() {
    return categoria;
};
string Vehiculo::getEstado() {
    return estado;
};




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
