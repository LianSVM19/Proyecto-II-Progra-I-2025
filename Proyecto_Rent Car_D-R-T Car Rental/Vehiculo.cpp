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
    case 'A':
    case 'a':
    case 'B':
    case 'b':
    case 'C':
    case 'c':
    case 'D':
    case 'd':
        // Si pasa cualquiera de los casos, normalizamos a mayúscula
        // (Si la entrada fue 'a', 'a' - 'a' + 'A' = 'A')
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';
        }
        categoria = c;
        cout << "Categoria " << c << " anadida" << endl;
        break;
    default:
        cout << "Categoria de vehiculo invalida" << endl;
    }
}
void Vehiculo::setEstado(string e) {

    // El método debe verificar si el NUEVO estado 'e' es una transición permitida
    // desde el ESTADO ACTUAL 'estado'.

    // Caso 1: Disponible (Estado Actual)
    if (estado == "Disponible") {
        if (e == "Alquilado" || e == "Revisión" || e == "Lavado") {
            estado = e;
            cout << "Transicion valida: Nuevo estado del carro: " << e << endl;
            return; // Salir de la función si se actualizó el estado
        }
    }
    // Caso 2: Alquilado (Estado Actual)
    else if (estado == "Alquilado") {
        // Según la matriz, solo Devuelto es SI.
        if (e == "Devuelto") {
            estado = e;
            cout << "Transicion valida: Nuevo estado del carro: " << e << endl;
            return;
        }
    }
    // Caso 3: Devuelto (Estado Actual)
    else if (estado == "Devuelto") {
        if (e == "Revisión" || e == "Lavado") {
            estado = e;
            cout << "Transicion valida: Nuevo estado del carro: " << e << endl;
            return;
        }
    }
    // Caso 4: Revisión (Estado Actual)
    else if (estado == "Revisión") {
        if (e == "Lavado") {
            estado = e;
            cout << "Transicion valida: Nuevo estado del carro: " << e << endl;
            return;
        }
    }
    // Caso 5: Lavado (Estado Actual)
    else if (estado == "Lavado") {
        if (e == "Disponible" || e == "Revisión") {
            estado = e;
            cout << "Transicion valida: Nuevo estado del carro: " << e << endl;
            return;
        }
    }

    // Si la función llega hasta aquí, la transición no fue válida o el estado es desconocido.
    cout << "ERROR: Transicion de estado invalida o no compatible." << endl;
    cout << "El carro NO puede pasar de [" << estado << "] a [" << e << "]." << endl;
}


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
    s << "\t\t*********************************" << endl;
    s << "\t\t--- Datos del Vehículo ---" << endl;
    s << "\t\tPlaca: " << placa << endl;
    s << "\t\tMarca: " << marca << endl;
    s << "\t\tModelo: " << modelo << endl;
    s << "\t\tCategoria: " << categoria << endl;
    s << "\t\tTipo Licencia Requerida: " << tipoLicencia << endl;
    s << "\t\tPrecio Diario: $" << precioDiario << endl;
    s << "\t\tESTADO ACTUAL: " << estado << endl;
    s << "\t\t*********************************" << endl;

    return s.str();

Vehiculo::~Vehiculo() {};
