#include "Vehiculo.h"
#include <iostream>

using namespace std;


string FechaActual() {
    string e;
    cout << "digite la Fecha Actual" << endl;
    cin >> e;
    return e;
}

//constructor sin finalizar
Vehiculo::Vehiculo(string pla, string mar, string mod, string til, char ca, string es) {
    placa = pla;
    marca = mar;
    modelo = mod;
    tipoLicencia = til;
    categoria = ca;
    estado = es;

    switch (categoria) {
    case 'a':
    case 'A':
        precioDiario = 25500.0;
        break;
    case 'b':
    case 'B':
        precioDiario = 42500.0;
        break;
    case 'c':
    case 'C':
        precioDiario = 120000.0;
        break;
    case 'd':
    case 'D':
        precioDiario = 64500.0;
        break;
    }
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
void Vehiculo::setEstado(string e, string ubicacion, string colaboradorId, string fecha) {
    string estadoAnterior = estado;
    bool transicionValida = false;

    // Lógica de matriz de transiciones (Casos de uso)
    if (estado == "Disponible") {
        if (e == "Alquilado" || e == "Revision" || e == "Lavado") {
            transicionValida = true;
        }
    }
    else if (estado == "Alquilado") {
        if (e == "Devuelto") { // Solo se permite Devuelto
            transicionValida = true;
        }
    }
    else if (estado == "Devuelto") {
        if (e == "Revision" || e == "Lavado") { // Transiciona a una fase de procesamiento
            transicionValida = true;
        }
    }
    else if (estado == "Revision") {
        if (e == "Lavado" || e == "Disponible") { // Asumo que puede ir a Disponible después de Revisión
            transicionValida = true;
        }
    }
    else if (estado == "Lavado") {
        if (e == "Disponible" || e == "Revision") {
            transicionValida = true;
        }
    }
    // NOTA: Considerar el estado "En Reparación" o "Mantenimiento" para mayor robustez.

    if (transicionValida) {
        estado = e; // Aplicar el nuevo estado

        string fechaActual=FechaActual(); // Usar la fecha proporcionada 
        stringstream desc;
        desc << "Cambio de [" << estadoAnterior << "] a [" << e << "]. Ubicacion: " << ubicacion << ". Operado por ID: " << colaboradorId;

        Estado* nuevoRegistro = new Estado(fechaActual, desc.str(), ubicacion);

        // Se usa Bitacora* en lugar de BitacoraEstado* como atributo, se corrige la inicialización.
        if (historialEstados == NULL) {
            historialEstados = new BitacoraEstado();
        }
        historialEstados->agregarEstado(nuevoRegistro);
        cout << "\t\t[INFO] Transicion valida: Nuevo estado del carro: " << e << endl;
    }
    else {
        // Si la función llega hasta aquí, la transición no fue válida o el estado es desconocido.
        cout << "\t\t[ERROR] Transicion de estado invalida o no compatible." << endl;
        cout << "\t\tEl carro NO puede pasar de [" << estadoAnterior << "] a [" << e << "]." << endl;
    }
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
BitacoraEstado* Vehiculo::getHistorialEstados() {
    return historialEstados;
};



// Implementación del toString con el estilo solicitado (usando sstream y endl)
string Vehiculo::toString() const {
    stringstream s;
    s << "\t\t*********************************" << endl;
    s << "\t\t--- Datos del Vehiculo ---" << endl;
    s << "\t\tPlaca: " << placa << endl;
    s << "\t\tMarca: " << marca << endl;
    s << "\t\tModelo: " << modelo << endl;
    s << "\t\tCategoria: " << categoria << endl;
    s << "\t\tTipo Licencia Requerida: " << tipoLicencia << endl;
    s << "\t\tPrecio Diario: $" << precioDiario << endl;
    s << "\t\tESTADO ACTUAL: " << estado << endl;
    s << "\t\t*********************************" << endl;

    return s.str();

}
Vehiculo::~Vehiculo() {};
