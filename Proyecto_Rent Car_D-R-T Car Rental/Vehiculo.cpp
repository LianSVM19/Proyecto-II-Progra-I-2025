#include "Vehiculo.h"
#include <iostream>

using namespace std;


//constructor sin finalizar
Vehiculo::Vehiculo(string pla, string mar, string mod, string til, double prd, char ca, string es) {
    placa = pla;
    marca = mar;
    modelo = mod;
    tipoLicencia = til;
    precioDiario = prd;
    categoria = ca;
    estado = es;
}
Vehiculo::Vehiculo() {
    placa = "";
    marca = "";
    modelo = "";
    tipoLicencia = "";
    precioDiario = 0,0;
    categoria = ' ';
    estado = "";
}

//set
void Vehiculo::setPlaca(string p) {
    placa = p;
};
void Vehiculo::setMarca(string m) {
    marca = m;
};
void Vehiculo::setModelo(string mo) {
    modelo = mo;
};
void Vehiculo::setTipoLicencia(string tl) {
    tipoLicencia = tl;
};
void Vehiculo::setPrecioDiario(double pd) {
    precioDiario = pd;
};
void Vehiculo::setCategoria(char c) {
    switch (c) {
    case 'A'://para que caiga por el siguiente case, ya que no hay break.
    case 'a':
        categoria = c;
        cout << "Categoria "<<c<<" anadida" << endl;
        break;
    case 'B'://igual que linea 45
    case 'b':
        categoria = c;
        cout << "Categoria " << c << " anadida" << endl;
        break;
    case 'C'://igual que linea 45
    case 'c':
        categoria = c;
        cout << "Categoria " << c << " anadida" << endl;
        break;
    case 'D'://igual que linea 45
    case 'd':
        categoria = c;
        cout << "Categoria " << c << " anadida" << endl;
        break;
    default:
        cout << "Categoria de vehiculo invalida";
    }
};
void Vehiculo::setEstado(string e) {
    if (e == "Disponible" || "Alquilado" || "Devuelto" || "Revision" || "Lavado") {
        estado = e;
        cout << "Estado del carro: " << e << endl;
    }
    else { cout << "Estado del carro invalido" << endl; }
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
