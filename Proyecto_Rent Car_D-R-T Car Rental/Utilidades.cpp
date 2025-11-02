// Utilidades.cpp
#include "Utilidades.h"
#include "Sucursal.h"
#include "ListaEnlazada.h"
#include "ClienteFisico.h"
#include "ClienteJuridico.h"
#include "Colaborador.h"
#include "Plantel.h"
#include <iostream>

using namespace std;

Utilidades::Utilidades() {
    // Inicializar la lista de clientes
    listaClientes = new ListaCliente();
    listaSucursales = new ListaSucursal();
    listaColaboradores = new ListaColaborador();
}

Utilidades::~Utilidades() {
    // Liberar la memoria de la lista de clientes
    if (listaClientes != NULL) {
        delete listaClientes;
        listaClientes = NULL;
    }
    // Liberar la memoria de la lista de sucursales (NUEVO)
    if (listaSucursales != NULL) {
        delete listaSucursales;
        listaSucursales = NULL;
    }
}


void Utilidades::crearPlantelSucursal() {
    string codigoSucursal, tipoPlantel, codigoPlantel;
    int filas, columnas;

    limpiarConsola();
    cout << "\n\t\t--- CREACIÓN DE PLANTEL PARA SUCURSAL ---" << endl;

    cout << "\t\tIngrese el código de la sucursal: ";
    getline(cin, codigoSucursal);

    Sucursal* sucursal = listaSucursales->buscar(codigoSucursal);
    if (sucursal == nullptr) {
        cout << "\t\tERROR: No se encontró ninguna sucursal con ese código." << endl;
        return;
    }

    cout << "\t\tIngrese el código del plantel: "<< "\nConsejo: Usar un layout de <letra><numero>, donde las letras marcan la \"serie de Plantel\".";
    getline(cin, codigoPlantel);

    cout << "\t\tIngrese el tipo de plantel (Ej: Estándar, Premium, SUV): ";
    getline(cin, tipoPlantel);

    cout << "\t\tIngrese el número de filas: ";
    while (!(cin >> filas) || filas <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\t\tValor inválido. Intente de nuevo: ";
    }

    cout << "\t\tIngrese el número de columnas: ";
    while (!(cin >> columnas) || columnas <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\t\tValor inválido. Intente de nuevo: ";
    }

    cin.ignore(10000, '\n'); // limpiar buffer

    Plantel* nuevoPlantel = new Plantel(codigoPlantel, tipoPlantel, filas, columnas);
    sucursal->getListaPlantel()->agregarPlantel(nuevoPlantel);

    cout << "\n\t\tPlantel creado exitosamente para la sucursal '"
        << sucursal->getNombre() << "'." << endl;

    cout << nuevoPlantel->toString() << endl;
}

void Utilidades::visualizarPlantel() {
    string codigoSucursal, codigoPlantel;
    int fil, col;
    limpiarConsola();
    cout << "\t\tIngrese el código de la sucursal: ";
    getline(cin, codigoSucursal);

    Sucursal* sucursal = listaSucursales->buscar(codigoSucursal);
    if (sucursal == nullptr) {
        cout << "\t\tERROR: No se encontró ninguna sucursal con ese código." << endl;
        return;
    }
    else {
        cout << "\t\tIngrese el código del plantel: ";
        getline(cin, codigoPlantel);
        Plantel* plantel = sucursal->getListaPlantel()->buscar(codigoPlantel);
        if (plantel == nullptr) {
            cout << "\t\tERROR: No se encontró ningun plantel con ese código." << endl;
            return;
        }
        fil = plantel->getCapacidadFilas();
        col = plantel->getCapacidadColumnas();

        for (int i = 0; i < fil; i++) {
            for (int j = 0; j < col; j++) {
                if (i < 10 && j < 10) { cout << "    [" << codigoPlantel << '0' << i << "/" << '0' << j << "]"; }
                else if (i > 10 && j < 10) { cout << "    [" << codigoPlantel << i << "/" << '0' << j << "]"; }
                else if (i < 10 && j > 10) { cout << "    [" << codigoPlantel << '0' << i << "/" << j << "]"; }
                else { cout << "    [" << codigoPlantel << i << "/" << j << "]"; }
            }
            cout << endl;
        }
    }
}




//Cositas
Cliente* Utilidades::leerDatosCliente() {
    string cedula, nombre, correo, telefono, fNacimiento, fInscripcion;
    char sexo;
    int tipoCliente = -1;
    Cliente* nuevoCliente = NULL;
    limpiarConsola();

    cout << "\n\t\t--- LECTURA DE DATOS DEL CLIENTE ---" << endl;

    // 1. Determinar el tipo de cliente
    cout << "\t\t1. Cliente Físico" << endl;
    cout << "\t\t2. Cliente Jurídico" << endl;
    cout << "\t\tSeleccione el tipo de cliente (1 o 2): ";
    tipoCliente = leerOpcion(1, 2); // Esta función ya limpia el buffer

    cout << "\n";

    // ===========================================
    // FLUJO PARA CLIENTE FÍSICO
    // ===========================================
    if (tipoCliente == 1) {
        cout << "\t\t<< DATOS DE CLIENTE FÍSICO >>" << endl;

        // El buffer está limpio por leerOpcion()
        cout << "\t\tIngrese la cédula: ";
        getline(cin, cedula);

        cout << "\t\tIngrese el nombre completo: ";
        getline(cin, nombre);

        cout << "\t\tIngrese el correo electrónico: ";
        getline(cin, correo);

        cout << "\t\tIngrese el número de teléfono: ";
        getline(cin, telefono);

        cout << "\t\tIngrese la fecha de nacimiento (dd/mm/aaaa): ";
        getline(cin, fNacimiento);

        cout << "\t\tIngrese la fecha de inscripción (dd/mm/aaaa): ";
        getline(cin, fInscripcion);

        cout << "\t\tIngrese el sexo (M/F): ";
        cin >> sexo;
        cin.ignore(10000, '\n'); // Limpiar buffer después de cin >> char

        nuevoCliente = new ClienteFisico(cedula, nombre, correo, telefono, sexo, fNacimiento, fInscripcion);

    }
    // ===========================================
    // FLUJO PARA CLIENTE JURÍDICO (Con corrección de bug)
    // ===========================================
    else if (tipoCliente == 2) {
        double descuento;
        string actividad;

        cout << "\t\t<< DATOS DE CLIENTE JURÍDICO >>" << endl;

        cout << "\t\tIngrese la cédula jurídica: ";
        getline(cin, cedula);

        cout << "\t\tIngrese el nombre completo: ";
        getline(cin, nombre);

        cout << "\t\tIngrese el correo electrónico: ";
        getline(cin, correo);

        cout << "\t\tIngrese el número de teléfono: ";
        getline(cin, telefono);

        cout << "\t\tIngrese la fecha de nacimiento (dd/mm/aaaa): ";
        getline(cin, fNacimiento);

        cout << "\t\tIngrese la fecha de inscripción (dd/mm/aaaa): ";
        getline(cin, fInscripcion);

        cout << "\t\tIngrese el sexo (M/F): ";
        cin >> sexo;
        cin.ignore(10000, '\n');

        cout << "\t\tIngrese el porcentaje de descuento (0.0 a 100.0): ";
        while (!(cin >> descuento)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\t\tValor inválido. Ingrese un número para el descuento: ";
        }

        cin.ignore(10000, '\n'); // 

        cout << "\t\tIngrese la actividad económica: ";
        getline(cin, actividad);

        nuevoCliente = new ClienteJuridico(cedula, nombre, correo, telefono, sexo, fNacimiento, fInscripcion, descuento, actividad);
    }

    // Retorna el puntero, no lo añade a ninguna lista
    return nuevoCliente;
}
void Utilidades::ingresarCliente() {
    Cliente* nuevoCliente = leerDatosCliente(); // Usa la nueva función
    
    if (nuevoCliente != NULL) {
        listaClientes->agregarCliente(nuevoCliente);
        cout << "\n\t\tCliente registrado con éxito en la LISTA GLOBAL." << endl;
        cout << "\t\tDatos del nuevo cliente:\n" << nuevoCliente->toString() << endl;
    }
    else {
        cout << "\t\tERROR: No se pudo crear el cliente." << endl;
    }
}
Colaborador* Utilidades::leerDatosColaborador() {
    string cedula, nombre, correo, telefono, fNacimiento, fInscripcion, fechaIngreso, puesto;
    char sexo;
    int tipoColaborador = -1;
    Colaborador* nuevoColaborador = NULL;
    limpiarConsola();
    cout << "\n\t\t--- INGRESO DE NUEVO Colaborador ---" << endl;

        cout << "\t\t<< INGRESO DE COLABORADOR >>" << endl;

        // Pedir datos comunes (Asegurándonos de usar getline para strings con espacios)
        cout << "\t\tIngrese la cédula: ";
        getline(cin, cedula);

        cout << "\t\tIngrese el nombre completo: ";
        getline(cin, nombre);

        cout << "\t\tIngrese el correo electrónico: ";
        getline(cin, correo);

        cout << "\t\tIngrese el número de teléfono: ";
        getline(cin, telefono);

        cout << "\t\tIngrese la fecha de nacimiento (dd/mm/aaaa): ";
        getline(cin, fNacimiento);

        cout << "\t\tIngrese la fecha de ingreso (dd/mm/aaaa): ";
        getline(cin, fInscripcion);
        fechaIngreso = fInscripcion;

        // Pedir dato específico
        cout << "\t\tIngrese el sexo (M/F): ";
        cin >> sexo;
        cin.ignore(10000, '\n');

        cout << "\t\tIngrese el Puesto del Colaborador:";
        getline(cin, puesto);

        // Crear el objeto dinámico
        nuevoColaborador = new Colaborador(cedula, nombre, correo, telefono, sexo, fNacimiento, fInscripcion);
        return nuevoColaborador;
}

void Utilidades::ingresarColaborador() {
    Colaborador* nuevoColaborador = leerDatosColaborador();
    
    if (nuevoColaborador != NULL) {
        listaColaboradores->agregarColaborador(nuevoColaborador);
        cout << "\n\t\tColaborador registrado con éxito." << endl;
        cout << "\t\tDatos del nuevo Colaborador:\n" << nuevoColaborador->toString() << endl;
    }
    else {
        cout << "\t\tERROR: No se pudo crear el Colaborador." << endl;
    }
}

// ====================================================
// IMPLEMENTACIÓN DE GESTIÓN DE SUCURSALES
// ====================================================

void Utilidades::ingresarSucursal() {
    string codigo, nombre, direccion, telefono;

    limpiarConsola();
    cout << "\n\t\t--- INGRESO DE NUEVA SUCURSAL ---" << endl;

    cout << "\t\tIngrese el código de la sucursal: ";
    getline(cin, codigo);

    // Opcional: Verificar si ya existe una sucursal con ese código
    if (listaSucursales->buscar(codigo) != nullptr) {
        cout << "\t\tERROR: Ya existe una sucursal con el código " << codigo << endl;
        return;
    }

    cout << "\t\tIngrese el nombre de la sucursal: ";
    getline(cin, nombre);

    cout << "\t\tIngrese la dirección: ";
    getline(cin, direccion);

    cout << "\t\tIngrese el teléfono: ";
    getline(cin, telefono);

    // Asumiendo el constructor: Sucursal(codigo, nombre, direccion, telefono)
    Sucursal* nuevaSucursal = new Sucursal(codigo, nombre, direccion, telefono);

    listaSucursales->agregarSucursal(nuevaSucursal); // Asume método agregarSucursal en ListaSucursal

    cout << "\n\t\tSucursal '" << nombre << "' registrada con éxito." << endl;
}

void Utilidades::mostrarSucursales() {
    limpiarConsola();
    cout << "\n\t\t--- VISUALIZACIÓN DE TODAS LAS SUCURSALES ---" << endl;
    if (listaSucursales->estaVacia()) {
        cout << "\t\tLa lista de sucursales está vacía." << endl;
        return;
    }
    cout << listaSucursales->toString() << endl; // Asume método toString en ListaSucursal
}


void Utilidades::eliminarSucursal() {
    string codigoEliminar;

    limpiarConsola();
    cout << "\n\t\t--- ELIMINAR SUCURSAL POR CÓDIGO ---" << endl;

    if (listaSucursales->estaVacia()) {
        cout << "\t\tLa lista de sucursales está vacía." << endl;
        return;
    }

    cout << "\t\tIngrese el código de la sucursal a eliminar: ";
    getline(cin, codigoEliminar);

    // Asumiendo que ListaSucursal::eliminar(codigo) retorna bool
    if (listaSucursales->eliminar(codigoEliminar)) {
        cout << "\n\t\tLa sucursal con código " << codigoEliminar << " ha sido eliminada." << endl;
    }
    else {
        cout << "\n\t\tERROR: No se encontró ninguna sucursal con el código " << codigoEliminar << endl;
    }
}

// ====================================================
// IMPLEMENTACIÓN DE GESTIÓN POR SUCURSAL
// ====================================================

// Funció auxiliar para encontrar la sucursal y operar en su lista interna de Clientes
void Utilidades::gestionarClientesPorSucursal(int operacion) {
    string codigoSucursal, cedulaCliente;
    limpiarConsola();

    cout << "\n\t\t--- GESTIÓN DE CLIENTES POR SUCURSAL ---" << endl;
    cout << "\t\tIngrese el código de la sucursal: ";
    
    getline(cin, codigoSucursal);

    Sucursal* sucursal = listaSucursales->buscar(codigoSucursal); 

    if (sucursal == NULL) {
        cout << "\t\tERROR: Sucursal con código " << codigoSucursal << " no encontrada." << endl;
        return;
    }

    ListaCliente* listaClientesSucursal = sucursal->getClientes(); // Acceder a la lista interna

    if (operacion == 1) { // Ingreso
        cout << "\n\t\t>> INGRESANDO CLIENTE en Sucursal: " << sucursal->getNombre() << endl;

       
        Cliente* c = leerDatosCliente(); // Llama a la función que pide los datos y lo crea

        if (c != NULL) {
            // Decides a dónde añadirlo:
            listaClientesSucursal->agregarCliente(c); // Añadir a la lista de la sucursal
            // Opcional: listaClientes->agregarCliente(c); // Si también lo quieres en la lista global

            cout << "\n\t\t Cliente registrado con éxito en la sucursal." << endl;
            cout << "\t\tDatos del nuevo cliente:\n" << c->toString() << endl;
        }
        else {
            cout << "\t\t ERROR: No se pudo completar el registro del cliente." << endl;
        }
    }
    else if (operacion == 2) { // Visualización
        cout << "\n\t\t>> VISUALIZANDO Clientes de Sucursal: " << sucursal->getNombre() << endl;
        cout << listaClientesSucursal->toString() << endl;

    }
    else if (operacion == 3) { // Eliminación
        cout << "\n\t\t>> ELIMINANDO Cliente de Sucursal: " << sucursal->getNombre() << endl;
        cout << "\t\tIngrese la cédula del cliente a eliminar: ";
        getline(cin, cedulaCliente);

        // Asume ListaCliente::eliminar(cedula) en la lista de la Sucursal
        if (listaClientesSucursal->eliminar(cedulaCliente)) {
            cout << "\t\tCliente con cédula " << cedulaCliente << " eliminado de la sucursal." << endl;
        }
        else {
            cout << "\t\tERROR: Cliente no encontrado en esta sucursal." << endl;
        }
    }
}


// Funció auxiliar para encontrar la sucursal y operar en su lista interna de Colaboradores
void Utilidades::gestionarColaboradoresPorSucursal(int operacion) {
    string codigoSucursal, idColaborador;
    limpiarConsola();

    cout << "\n\t\t--- GESTIÓN DE COLABORADORES POR SUCURSAL ---" << endl;
    cout << "\t\tIngrese el código de la sucursal: ";
    getline(cin, codigoSucursal);

    Sucursal* sucursal = listaSucursales->buscar(codigoSucursal);

    if (sucursal == NULL) {
        cout << "\t\tERROR: Sucursal con código " << codigoSucursal << " no encontrada." << endl;
        return;
    }

    ListaColaborador* listaColaboradoresSucursal = sucursal->getColaboradores(); // Acceder a la lista interna

    if (operacion == 1) { // Ingreso
        ingresarColaborador();
        cout << "\n\t\t>> INGRESANDO COLABORADOR en Sucursal: " << sucursal->getNombre() << endl;
        Colaborador* c = leerDatosColaborador(); // Llama a la función que pide los datos y lo crea

        if (c != NULL) {
            // Decides a dónde añadirlo:
            listaColaboradoresSucursal->agregarColaborador(c); // Añadir a la lista de la sucursal

            cout << "\n\t\t Cliente registrado con éxito en la sucursal." << endl;
            cout << "\t\tDatos del nuevo cliente:\n" << c->toString() << endl;
        }
        else {
            cout << "\t\t ERROR: No se pudo completar el registro del cliente." << endl;
        }

    }
    else if (operacion == 2) { // Visualización
        cout << "\n\t\t>> VISUALIZANDO Colaboradores de Sucursal: " << sucursal->getNombre() << endl;
        cout << listaColaboradoresSucursal->toString() << endl; // Asume ListaColaborador::toString

    }
    else if (operacion == 3) { // Eliminación
        cout << "\n\t\t>> ELIMINANDO Colaborador de Sucursal: " << sucursal->getNombre() << endl;
        cout << "\t\tIngrese el ID del colaborador a eliminar: ";
        getline(cin, idColaborador);

        // Asume ListaColaborador::eliminar(id) en la lista de la Sucursal
        if (listaColaboradoresSucursal->eliminar(idColaborador)) {
            cout << "\t\tColaborador con ID " << idColaborador << " eliminado de la sucursal." << endl;
        }
        else {
            cout << "\t\tERROR: Colaborador no encontrado en esta sucursal." << endl;
        }
    }
}

// Implementación del método auxiliar para buscar un vehículo en todas las sucursales
Vehiculo* Utilidades::buscarVehiculoGlobal(string placa, string& codigoSucursalEncontrado) {

    // Obtiene el inicio de la lista de sucursales
    NodoSucursal* actualSucursal = listaSucursales->getCab();

    while (actualSucursal != NULL) {

        Sucursal* suc = actualSucursal->getDato();
        ListaVehiculo* listaVehiculos = suc->getListaVehiculos();

        // Busca el vehículo en la lista de la sucursal actual
        Vehiculo* vehiculo = listaVehiculos->buscar(placa);

        if (vehiculo != NULL) {
            // Asigna el código de la sucursal actual a la referencia
            codigoSucursalEncontrado = suc->getCodigoSucursal();
            return vehiculo; // Devuelve el vehículo
        }

        // Avanza al siguiente nodo
        actualSucursal = actualSucursal->getSiguiente();
    }
    return NULL; // Vehículo no encontrado
}


// ========================================================
// 2. IMPLEMENTACIÓN DEL MÉTODO DE PRESENTACIÓN
//    (Este es el que tenía el error de llamada al 'buscar')
// ========================================================
void Utilidades::mostrarInformacionVehiculoGlobal(string placa) {

    // Variable para capturar el resultado de la búsqueda
    string codigoSucursalDelVehiculo = "";

    // LÍNEA CORREGIDA: Usando 'this->' para llamar al método miembro 'buscarVehiculoGlobal'
    Vehiculo* vehiculoEncontrado = buscarVehiculoGlobal(placa, codigoSucursalDelVehiculo);

    // Imprimimos el resultado
    if (vehiculoEncontrado != NULL) {
        cout << "\t\t===================================================" << endl;
        cout << "\t\t--- RESULTADO DE LA BÚSQUEDA GLOBAL ---" << endl;
        cout << "\t\t¡Vehículo encontrado!" << endl;
        cout << "\t\tPlaca: " << vehiculoEncontrado->getPlaca() << endl;
        // La información del vehículo es limpia, y la ubicación es de la Sucursal
        cout << "\t\tUbicación (Código Sucursal): " << codigoSucursalDelVehiculo << endl;
        cout << "\t\t===================================================" << endl;
    }
    else {
        cout << "\t\t===================================================" << endl;
        cout << "\t\t--- RESULTADO DE LA BÚSQUEDA GLOBAL ---" << endl;
        cout << "\t\tEl vehículo con placa [" << placa << "] no se encontró en ninguna sucursal." << endl;
        cout << "\t\t===================================================" << endl;
    }
}
void Utilidades::CrearSolicitud() {
    string codigoSoli, cedulaCliente, idColaborador, codigoSucursal, placaVehiculo, fIni, fFin;
    int dias = 0;
    double precioTotal = 0.0;

    // Punteros a las entidades que necesitamos:
    Cliente* cliente = NULL;
    Colaborador* colaborador = NULL;
    Sucursal* sucursal = NULL;
    Vehiculo* vehiculo = NULL;

    limpiarConsola();
    cout << "\n\t\t--- CREACIÓN DE NUEVA SOLICITUD DE ALQUILER ---" << endl;

    // 1. Obtener y buscar el Cliente (Cédula)
    cout << "\t\tIngrese la cédula del Cliente: ";
    getline(cin, cedulaCliente);
    cliente = listaClientes->buscar(cedulaCliente);
    if (cliente == NULL) {
        cout << "\t\tERROR: Cliente con cédula " << cedulaCliente << " no encontrado." << endl;
        pausa();
        return;
    }

    // 2. Obtener y buscar el Colaborador (Cédula)
    cout << "\t\tIngrese la cédula del Colaborador que registra: ";
    getline(cin, idColaborador);
    colaborador = listaColaboradores->buscar(idColaborador);
    if (colaborador == NULL) {
        cout << "\t\tERROR: Colaborador con cédula " << idColaborador << " no encontrado." << endl;
        pausa();
        return;
    }

    // 3. Obtener y buscar el Vehículo (Placa)
    cout << "\t\tIngrese la Placa del Vehículo a alquilar: ";
    getline(cin, placaVehiculo);

    // *** CAMBIO CRUCIAL ***: 
    // Llamamos a buscarVehiculoGlobal con dos argumentos: la placa y la variable 'codigoSucursal' 
    // que se llenará con el código de la sucursal que tiene el carro.
    vehiculo = this->buscarVehiculoGlobal(placaVehiculo, codigoSucursal); // <-- AQUÍ ESTÁ EL CAMBIO

    if (vehiculo == NULL) {
        cout << "\t\tERROR: Vehículo con placa " << placaVehiculo << " no encontrado en ninguna sucursal." << endl;
        pausa();
        return;
    }

    // 4. Validar estado del vehículo
    if (vehiculo->getEstado() != "Disponible") {
        cout << "\t\tERROR: El vehículo " << placaVehiculo << " no está disponible. Estado actual: " << vehiculo->getEstado() << endl;
        pausa();
        return;
    }

    // 5. Obtener y buscar la Sucursal (Código)
    // El 'codigoSucursal' ya fue llenado por la función buscarVehiculoGlobal.
    sucursal = listaSucursales->buscar(codigoSucursal);

    // Si la sucursal es NULL, es un error interno grave, ya que el código se obtuvo de una Sucursal existente.
    if (sucursal == NULL) {
        cout << "\t\tERROR INTERNO: Sucursal asociada al vehículo no encontrada." << endl;
        pausa();
        return;
    }


    // 6. Datos de la Solicitud
    cout << "\t\tIngrese el código de la nueva Solicitud (ej. S001): ";
    getline(cin, codigoSoli);
    cout << "\t\tIngrese la Fecha de Inicio (DD/MM/AAAA): ";
    getline(cin, fIni);
    cout << "\t\tIngrese la Fecha de Entrega Estimada (DD/MM/AAAA): ";
    getline(cin, fFin);
    cout << "\t\tIngrese la cantidad de días de alquiler: ";

    // Lógica para leer 'dias' (entero)
    cin >> dias;
    // Agregamos una verificación simple para la lectura
    if (cin.fail()) {
        cin.clear();
        cout << "\t\tEntrada inválida. Días de alquiler deben ser un número." << endl;
        pausa();
        cin.ignore(10000, '\n');
        return;
    }
    cin.ignore(10000, '\n'); // Limpiar buffer

    // 7. Cálculo del Precio Total
    if (dias <= 0) {
        cout << "\t\tERROR: Los días de alquiler deben ser un número positivo." << endl;
        pausa();
        return;
    }

    precioTotal = vehiculo->getPrecioDiario() * dias;

    // 8. Creación de la Solicitud
    // Asumo que SolicitudAlquiler requiere un puntero a Sucursal
    SolicitudAlquiler* nuevaSoli = new SolicitudAlquiler(
        codigoSoli, cliente, colaborador, sucursal, vehiculo, fIni, fFin,
        precioTotal, "Pendiente" // Estado inicial
    );
    nuevaSoli->setCanDiasAlqui(dias);

    listaSolicitudes->agregarSolicitud(nuevaSoli);

    cout << "\n\t\t--- SOLICITUD CREADA CON ÉXITO ---" << endl;
    cout << nuevaSoli->toString() << endl;
    pausa();
}


void Utilidades::VerSolicitudesContratos() {
    limpiarConsola();
    cout << "\n\t\t===================================================" << endl;
    cout << "\t\t--- VISUALIZACIÓN DE SOLICITUDES Y CONTRATOS ---" << endl;
    cout << "\t\t===================================================" << endl;

    // 1. Mostrar todas las Solicitudes
    cout << "\n\t\t--- 1. LISTA DE SOLICITUDES DE ALQUILER ---" << endl;
    if (listaSolicitudes->estaVacia()) {
        cout << "\t\t[INFO] No hay solicitudes registradas actualmente." << endl;
    }
    else {
        // Asumo que ListaSolicitud tiene un método 'toString()' o 'mostrar()'
        // que imprime todas las solicitudes. Usaremos toString() si está implementado
        // en la lista, si no, se puede iterar, pero asumimos el método de la lista.
        cout << listaSolicitudes->toString();
    }
    cout << "\t\t---------------------------------------------------" << endl;


    // 2. Mostrar todos los Contratos
    cout << "\n\t\t--- 2. LISTA DE CONTRATOS DE ALQUILER ---" << endl;
    if (listaContratos->estaVacia()) {
        cout << "\t\t[INFO] No hay contratos registrados actualmente." << endl;
    }
    else {
        // Asumo que ListaContrato tiene un método 'toString()' o 'mostrar()'
        cout << listaContratos->toString();
    }
    cout << "\t\t---------------------------------------------------" << endl;

    pausa();
}




//jaja
void Utilidades::AprobarRechazarSolicitud() {
    string codigoSoli;
    char opcion;
    limpiarConsola();
    cout << "\n\t\t--- APROBACIÓN / RECHAZO DE SOLICITUD (1 pto) ---" << endl;

    cout << "\t\tIngrese el código de la Solicitud a procesar: ";
    getline(cin, codigoSoli);

    SolicitudAlquiler* solicitud = listaSolicitudes->buscar(codigoSoli);

    if (solicitud == NULL || solicitud->getEstado() != "Pendiente") {
        cout << "\t\tERROR: Solicitud no encontrada o ya procesada." << endl;
    }
    else {
        cout << "\n\t\t--- DETALLE DE LA SOLICITUD ---" << endl;
        cout << solicitud->toString() << endl;
        cout << "\t\t[A]probar o [R]echazar la solicitud? (A/R): ";
        cin >> opcion;
        cin.ignore(10000, '\n');

        if (opcion == 'A' || opcion == 'a') {
            solicitud->setEstado("Aprobada");

            // 1. Cambiar estado del vehículo
            Vehiculo* vehiculo = solicitud->getVehiculo();
            vehiculo->setEstado("Alquilado");

            // 2. Crear Contrato
            string codigoContrato = "CONT-" + codigoSoli;
            ContratoAlquiler* nuevoContrato = new ContratoAlquiler(
                codigoContrato, solicitud->getPrecioTotal(), "Activo", solicitud
            );

            listaContratos->agregarContrato(nuevoContrato);

            cout << "\n\t\t¡APROBACIÓN EXITOSA! Contrato " << codigoContrato << " creado." << endl;

        }
        else if (opcion == 'R' || opcion == 'r') {
            solicitud->setEstado("Rechazada");
            cout << "\n\t\t¡RECHAZO EXITOSO! Solicitud " << codigoSoli << " rechazada." << endl;
        }
        else {
            cout << "\t\tOpción inválida. No se realizó ninguna acción." << endl;
        }
    }
    pausa();
}




void Utilidades::RecepcionVehiculo() {
    string codigoContrato;
    limpiarConsola();
    cout << "\n\t\t--- RECEPCIÓN DE VEHÍCULO Y FINALIZACIÓN DE CONTRATO (3 pts) ---" << endl;

    cout << "\t\tIngrese el código del Contrato a finalizar: ";
    getline(cin, codigoContrato);

    ContratoAlquiler* contrato = listaContratos->buscar(codigoContrato);

    if (contrato == NULL) {
        cout << "\t\tERROR: Contrato con código " << codigoContrato << " no encontrado." << endl;
    }
    else if (contrato->getEstado() == "Finalizado") {
        cout << "\t\tERROR: El contrato ya se encuentra 'Finalizado'." << endl;
    }
    else if (contrato->getEstado() == "Activo") {

        // 1. Finalizar el Contrato
        contrato->setEstado("Finalizado");

        // 2. Obtener Vehículo y cambiar su estado
        Vehiculo* vehiculo = contrato->getSolicitud()->getVehiculo();

        // Transición: Alquilado -> Devuelto (según su lógica interna)
        vehiculo->setEstado("Devuelto");

        cout << "\n\t\t¡RECEPCIÓN EXITOSA!" << endl;
        cout << "\t\tEl contrato " << codigoContrato << " ha sido marcado como 'Finalizado'." << endl;
        cout << "\t\tEl vehículo " << vehiculo->getPlaca() << " ha sido marcado como 'Devuelto'." << endl;
        cout << "\t\tNOTA: El vehículo en estado 'Devuelto' debe pasar a 'Revisión' o 'Lavado'." << endl;

    }
    else {
        cout << "\t\tERROR: El contrato no está en estado 'Activo'." << endl;
    }
    pausa();
}


// ----------------------------------------------------
// Implementación de Control de Interfaz y Consola
// ----------------------------------------------------

void Utilidades::limpiarConsola() {
    system("cls || clear");
}

void Utilidades::pausa() {
    cout << "\t\tPresione [ENTER] para continuar...";
    cin.get();
}

int Utilidades::leerOpcion(int min, int max) {
    int opcion;
    cout << "\t\tDigite la opción deseada: ";

    // 🚨 USO EXPLÍCITO DE cin >>
    while (!(cin >> opcion) || opcion < min || opcion > max) {
        cin.clear();
        cin.ignore(10000, '\n'); // Limpieza del buffer
        cout << "\t\tOpción inválida. Ingrese un número entre [" << min << "] y [" << max << "]: ";
    }
    cin.ignore(10000, '\n'); // Limpieza del buffer
    return opcion;
}



// ----------------------------------------------------
// Implementación de Funciones de Menú
// ----------------------------------------------------


void Utilidades::ejecutarSistema() {
    int opcion = -1;

    while (opcion != 0) {
        mostrarMenuPrincipal();
        opcion = this->op;

        switch (opcion) {
            // ... (casos 0 a 5) ...
        case 1:
            // Llama al submenú de Sucursales
            mostrarSubmenuSucursales();
            break;
        case 2:
            // Llama al submenú de Colaboradores
            mostrarSubmenuColaboradores();
            break;
        case 3:
            // Llama al submenú de Carros y Planteles
            mostrarSubmenuCarrosPlanteles();
            break;
        case 4:
            // Llama al submenú de Solicitudes y Contratos
            mostrarSubmenuSolicitudesContratos();
            break;
        case 5:
            // Llama al submenú de Clientes
            mostrarSubmenuClientes();
            break;
        case 0:
            cout << "\n\t\tGracias por usar el sistema. ¡Adiós!" << endl;
            break;
        }

        // Resetea 'op' para volver a mostrar el Menú Principal
        this->op = -1;
    }
}
void Utilidades::mostrarMenuPrincipal() {
        limpiarConsola();
        cout << "\n\t\t======================================================" << endl;
        cout << "\t\t       C A D E N A   D E   R E N T A   A   C A R      " << endl;
        cout << "\t\t             \"D - R - T   C a r   R e n t a l\"      " << endl;
        cout << "\t\t======================================================" << endl;
        cout << "\t\t(1) Submenú de Sucursales" << endl;
        cout << "\t\t(2) Submenú de Colaboradores" << endl;
        cout << "\t\t(3) Submenú de Carros y Planteles" << endl;
        cout << "\t\t(4) Submenú de Solicitudes y Contratos" << endl;
        cout << "\t\t(5) Submenú de Clientes" << endl;
        cout << "\t\t(0) SALIR DEL SISTEMA" << endl;
        cout << "\t\t------------------------------------------------------" << endl;
        op = leerOpcion(0, 5);
    }



void Utilidades::mostrarSubmenuSucursales() {
    int opcionSubmenu = -1; // Inicializamos a un valor != 0 para entrar al bucle.

    // El bucle se ejecuta mientras la opción NO sea 0 (Regresar al Menú Principal).
    while (opcionSubmenu != 0) {

        // 1. Mostrar el menú
        limpiarConsola();
        cout << "\n\t\t======================================================" << endl;
        cout << "\t\t                SUBMENÚ DE SUCURSALES                 " << endl;
        cout << "\t\t======================================================" << endl;
        cout << "\t\t(1) Ingresar Sucursal" << endl;
        cout << "\t\t(2) Mostrar Sucursales" << endl;
        cout << "\t\t(3) Eliminar Sucursal" << endl;
        cout << "\t\t(0) Regresar al Menú Principal" << endl;
        cout << "\t\t------------------------------------------------------" << endl;

        // 2. Leer la opción (Rango de 0 a 3)
        // Llamada a la función de la misma clase.
        opcionSubmenu = leerOpcion(0, 3);

        // 3. Ejecutar la lógica con switch
        switch (opcionSubmenu) {
        case 1:
            cout << "\n\t\t>> Ejecutando: Ingresar Sucursal..." << endl;
            this->ingresarSucursal();
            break;
        case 2:
            cout << "\n\t\t>> Ejecutando: Mostrar Sucursales..." << endl;
            this->mostrarSucursales();
            break;
        case 3:
            cout << "\n\t\t>> Ejecutando: Eliminar Sucursal..." << endl;
            this->eliminarSucursal();
            break;
        case 0:
            // El bucle terminará automáticamente después de esta iteración.
            cout << "\n\t\tRegresando al Menú Principal..." << endl;
            break;
        }

        // Si la opción NO es 0, hacemos una pausa para que el usuario vea el resultado de la acción.
        if (opcionSubmenu != 0) {
            cout << "\t\tPresione ENTER para volver al submenú...";
            // usamos cin.get() aquí para esperar una pulsación.
            cin.get();
        }

    } // Fin del while
}
void Utilidades::mostrarSubmenuColaboradores() {
    int opcionSubmenu = -1; // Inicializamos a un valor != 0 para entrar al bucle.

    // El bucle se ejecuta mientras la opción NO sea 0 (Regresar al Menú Principal).
    while (opcionSubmenu != 0) {

        // 1. Mostrar el menú
        limpiarConsola();
        cout << "\n\t\t======================================================" << endl;
        cout << "\t\t               SUBMENÚ DE COLABORADORES               " << endl;
        cout << "\t\t======================================================" << endl;
        cout << "\t\t(1) Incluir Colaborador en Sucursal" << endl;
        cout << "\t\t(2) Mostrar Colaborador" << endl;
        cout << "\t\t(3) Eliminar Colaborador" << endl;
        cout << "\t\t(4) Reporte de alquileres por colaborador" << endl;
        cout << "\t\t(0) Regresar al Menú Principal" << endl;
        cout << "\t\t------------------------------------------------------" << endl;

        // 2. Leer la opción (Rango de 0 a 4)
        // Llamada a la función de la misma clase.
        opcionSubmenu = leerOpcion(0, 4);

        // 3. Ejecutar la lógica con switch
        switch (opcionSubmenu) {
        case 1:
            cout << "\n\t\t>> Ejecutando: Incluir Colaborador en Sucursal..." << endl;
            this->gestionarColaboradoresPorSucursal(1);
            break;
        case 2:
            cout << "\n\t\t>> Ejecutando: Mostrar Colaborador..." << endl;
            this->gestionarColaboradoresPorSucursal(2);
            break;
        case 3:
            cout << "\n\t\t>> Ejecutando: Eliminar Colaborador..." << endl;
            this->gestionarColaboradoresPorSucursal(3);
            break;
        case 4:
            cout << "\n\t\t>> Ejecutando: Reporte de Alquileres..." << endl;
            // llamar a funcion ReporteAlquileres();
            break;
        case 0:
            // El bucle terminará automáticamente después de esta iteración.
            cout << "\n\t\tRegresando al Menú Principal..." << endl;
            break;
        }

        // Si la opción NO es 0, hacemos una pausa para que el usuario vea el resultado de la acción.
        if (opcionSubmenu != 0) {
            cout << "\t\tPresione ENTER para volver al submenú...";
            // usamos cin.get() aquí para esperar una pulsación.
            cin.get();
        }

    } // Fin del while
}



void Utilidades::mostrarSubmenuCarrosPlanteles() {
    int opcionSubmenu = -1; // Inicializamos a un valor != 0 para entrar al bucle.

    // El bucle se ejecuta mientras la opción NO sea 0 (Regresar al Menú Principal).
    while (opcionSubmenu != 0) {

        // 1. Mostrar el menú
        limpiarConsola();
        cout << "\n\t\t======================================================" << endl;
        cout << "\t\t            SUBMENÚ DE CARROS Y PLANTELES             " << endl;
        cout << "\t\t======================================================" << endl;
        cout << "\t\t(1) Crear Plantel" << endl;
        cout << "\t\t(2) Visualizacion Grafica de Plantel" << endl;
        cout << "\t\t(3) Ingreso de Vehiculo" << endl;
        cout << "\t\t(4) Visualizacion de Vehiculo" << endl;
        cout << "\t\t(5) Eliminacion de Vehiculo" << endl;
        cout << "\t\t(6) Reasignacion de Vehiculo en Plantel" << endl;
        cout << "\t\t(7) Cambio de Estado de Vehiculo" << endl;
        cout << "\t\t(8) Estados de un Vehiculo especifico" << endl;
        cout << "\t\t(9) Reportaje de porcentaje de ocupacion de los planteles" << endl;
        cout << "\t\t(10) Traslado de Vehiculos a Plantel (OPTATIVO)" << endl;
        cout << "\t\t(0) Regresar al Menú Principal" << endl;
        cout << "\t\t------------------------------------------------------" << endl;

        // 2. Leer la opción (Rango de 0 a 10)
        // Llamada a la función de la misma clase.
        opcionSubmenu = leerOpcion(0, 10);

        // 3. Ejecutar la lógica con switch
        switch (opcionSubmenu) {
        case 1:
            cout << "\n\t\t>> Ejecutando: Crear Plantel..." << endl;
            Utilidades::crearPlantelSucursal();
            break;
        case 2:
            cout << "\n\t\t>> Ejecutando: Visualizacion Grafica de Plantel..." << endl;
            Utilidades::visualizarPlantel();
            break;
        case 3:
            cout << "\n\t\t>> Ejecutando: Ingreso de Vehiculo..." << endl;
            // llamar a funcion IngresoVehiculo();
            break;
        case 4:
            cout << "\n\t\t>> Ejecutando: Visualizacion de Vehiculo..." << endl;
            // llamar a funcion VisualizacionVehiculo();
            break;
        case 5:
            cout << "\n\t\t>> Ejecutando: Eliminacion de Vehiculo..." << endl;
            // llamar a funcion EliminacionVehiculo();
            break;

        case 6:
            cout << "\n\t\t>> Ejecutando: Reasignacion de Vehiculo en Plantel..." << endl;
            // llamar a funcion ReasignaVehiculoPlantel();
            break;
        case 7:
            cout << "\n\t\t>> Ejecutando: Cambio de Estado de Vehiculo..." << endl;
            // llamar a funcion CambioEstadoVehiculo();
            break;
        case 8:
            cout << "\n\t\t>> Ejecutando: Estados de un Vehiculo especifico..." << endl;
            // llamar a funcion VerEstadosVehiculo();
            break;
        case 9:
            cout << "\n\t\t>> Ejecutando: Reportaje de porcentaje de ocupacion de los planteles..." << endl;
            // llamar a funcion PorcenOcupacionPlantel();
            break;
        case 10:
            cout << "\n\t\t>> Ejecutando: Traslado de Vehiculos a Plantel (OPTATIVO)..." << endl;
            // llamar a funcion TrasladoVehiculosPlantel();
            break;
        case 0:
            // El bucle terminará automáticamente después de esta iteración.
            cout << "\n\t\tRegresando al Menú Principal..." << endl;
            break;
        }

        // Si la opción NO es 0, hacemos una pausa para que el usuario vea el resultado de la acción.
        if (opcionSubmenu != 0) {
            cout << "\t\tPresione ENTER para volver al submenú...";
            // usamos cin.get() aquí para esperar una pulsación.
            cin.get();
        }

    } // Fin del while
}

void Utilidades::mostrarSubmenuSolicitudesContratos() {
    int opcionSubmenu = -1; // Inicializamos a un valor != 0 para entrar al bucle.

    // El bucle se ejecuta mientras la opción NO sea 0 (Regresar al Menú Principal).
    while (opcionSubmenu != 0) {

        // 1. Mostrar el menú
        limpiarConsola();
        cout << "\n\t\t======================================================" << endl;
        cout << "\t\t          SUBMENÚ DE SOLICITUDES Y CONTRATOS          " << endl;
        cout << "\t\t======================================================" << endl;
        cout << "\t\t(1) Creacion de Solicitud" << endl;
        cout << "\t\t(2) Visualización de solicitudes/contratos por sucursal" << endl;
        cout << "\t\t(3) Visualización de solicitud/contratos especifica" << endl;
        cout << "\t\t(4) Aprobación/rechazo de solicitud" << endl;
        cout << "\t\t(5) Recepción de vehículo en prestado" << endl;
        cout << "\t\t(6) Reporte de contratos para vehículos especifico" << endl;
        cout << "\t\t(7) Visualizar TODAS las Solicitudes/Contratos (Auxiliar)" << endl;
        cout << "\t\t(0) Regresar al Menú Principal" << endl;
        cout << "\t\t------------------------------------------------------" << endl;

        // 2. Leer la opción (Rango de 0 a 7)
        // Llamada a la función de la misma clase.
        opcionSubmenu = leerOpcion(0, 7);

        // 3. Ejecutar la lógica con switch
        switch (opcionSubmenu) {
        case 1:
            cout << "\n\t\t>> Ejecutando: Creación  de solicitud..." << endl;
            this->CrearSolicitud();
            break;
        case 2:
            cout << "\n\t\t>> Ejecutando: Visualización de solicitudes/contratos por sucursal..." << endl;
            // llamar a funcion VerSoliCont_Sucursal();
            break;
        case 3:
            cout << "\n\t\t>> Ejecutando: Visualización de solicitud/contratos especifica..." << endl;
            // llamar a funcion VerSoliCont_Especifico();
            break;
        case 4:
            cout << "\n\t\t>> Ejecutando: Aprobación/rechazo de solicitud..." << endl;
            this->AprobarRechazarSolicitud();
            break;
        case 5:
            cout << "\n\t\t>> Ejecutando: Recepción de vehículo en prestado ..." << endl;
            // llamar a funcion RecibirVehiPrestado();
            this->RecepcionVehiculo();
            break;
        case 6:
            cout << "\n\t\t>> Ejecutando: Reporte de contratos para vehículos especifico..." << endl;
            // llamar a funcion ReporteContratosVehiEspecifico();
            break;
        case 7:
            cout << "\n\t\t>> Ejecutando: Visualizacion de todas las solicitudes / contratos..." << endl;
            this->VerSolicitudesContratos();
            break;
        case 0:
            // El bucle terminará automáticamente después de esta iteración.
            cout << "\n\t\tRegresando al Menú Principal..." << endl;
            break;
        }

        // Si la opción NO es 0, hacemos una pausa para que el usuario vea el resultado de la acción.
        if (opcionSubmenu != 0) {
            cout << "\t\tPresione ENTER para volver al submenú...";
            // usamos cin.get() aquí para esperar una pulsación.
            cin.get();
        }

    } // Fin del while
}


void Utilidades::mostrarSubmenuClientes() {
    int opcionSubmenu = -1; // Inicializamos a un valor != 0 para entrar al bucle.

    // El bucle se ejecuta mientras la opción NO sea 0 (Regresar al Menú Principal).
    while (opcionSubmenu != 0) {

        // 1. Mostrar el menú
        limpiarConsola();
        cout << "\n\t\t======================================================" << endl;
        cout << "\t\t            SUBMENÚ DE CLIENTES                       " << endl;
        cout << "\t\t======================================================" << endl;
        cout << "\t\t(1) Ingresar Cliente" << endl;
        cout << "\t\t(2) Mostrar Cliente" << endl;
        cout << "\t\t(3) Eliminar Cliente" << endl;
        cout << "\t\t(4) Historial del Cliente" << endl;
        cout << "\t\t(5) Reporte de clientes por cantidad de contratos" << endl;
        cout << "\t\t(0) Regresar al Menú Principal" << endl;
        cout << "\t\t------------------------------------------------------" << endl;

        // 2. Leer la opción (Rango de 0 a 5)
        // Llamada a la función de la misma clase.
        opcionSubmenu = leerOpcion(0, 5);

        // 3. Ejecutar la lógica con switch
        switch (opcionSubmenu) {
        case 1:
            cout << "\n\t\t>> Ejecutando: Ingresar Cliente..." << endl;
            this->gestionarClientesPorSucursal(1);
            break;
        case 2:
            cout << "\n\t\t>> Ejecutando: Mostrar Cliente..." << endl;
            this->gestionarClientesPorSucursal(2);
            break;
        case 3:
            cout << "\n\t\t>> Ejecutando: Eliminar Cliente..." << endl;
            this->gestionarClientesPorSucursal(3);
            break;
        case 4:
            cout << "\n\t\t>> Ejecutando: Historial del Cliente..." << endl;
            // llamarAFuncionHistorialCliente();
            break;
        case 5:
            cout << "\n\t\t>> Ejecutando: Reporte de clientes..." << endl;
            // llamarAFuncionReporteClientes();
            break;
        case 0:
            // El bucle terminará automáticamente después de esta iteración.
            cout << "\n\t\tRegresando al Menú Principal..." << endl;
            break;
        }

        // Si la opción NO es 0, hacemos una pausa para que el usuario vea el resultado de la acción.
        if (opcionSubmenu != 0) {
            cout << "\t\tPresione ENTER para volver al submenú...";
            // usamos cin.get() aquí para esperar una pulsación.
            cin.get();
        }

    } // Fin del while
}