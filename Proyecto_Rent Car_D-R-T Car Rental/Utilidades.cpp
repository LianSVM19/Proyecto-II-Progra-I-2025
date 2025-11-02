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
    listaContratos = new ListaContrato();
    listaSolicitudes = new ListaSolicitud();
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

Sucursal* Utilidades::seleccionarSucursal() {

    // 1. Verificar si hay sucursales registradas
    if (listaSucursales == NULL || listaSucursales->estaVacia()) { // Asumo los métodos
        cout << "\n\t\tERROR: No hay sucursales registradas en el sistema." << endl;
        return NULL;
    }

    string codigoBuscado;
    Sucursal* suc = NULL;

    do {
        // 2. Mostrar la lista de sucursales
        cout << "\n\t\t--- SUCURSALES DISPONIBLES ---" << endl;
        // Asumo que ListaSucursales tiene un metodo para listar o toString
        cout << listaSucursales->toString() << endl;

        cout << "\t\tIngrese el CÓDIGO de la sucursal (o '0' para cancelar): ";
        getline(cin, codigoBuscado);

        if (codigoBuscado == "0") {
            cout << "\n\t\tSelección de sucursal cancelada." << endl;
            return NULL;
        }

        // 3. Buscar la sucursal (Asumo un método 'buscarSucursal' en ListaSucursales)
        suc = listaSucursales->buscar(codigoBuscado);

        if (suc == NULL) {
            cout << "\n\t\tERROR: Código de sucursal NO encontrado. Intente de nuevo." << endl;
        }

    } while (suc == NULL);

    cout << "\n\t\tSucursal seleccionada: " << suc->getNombre() << endl;
    return suc;
}


void Utilidades::crearPlantelSucursal() {
    string codigoSucursal, tipoPlantel, codigoPlantel;
    int filas, columnas;

    limpiarConsola();
    cout << "\n\t\t--- CREACION DE PLANTEL PARA ESTACIONAMIENTO ---" << endl;

    cout << "\t\tIngrese el codigo de la sucursal: ";
    getline(cin, codigoSucursal);

    Sucursal* sucursal = listaSucursales->buscar(codigoSucursal);
    if (sucursal == NULL) {
        cout << "\t\tERROR: No se encontro ninguna sucursal con ese codigo." << endl;
        return;
    }

    cout << "\t\tIngrese el codigo del plantel: "<< "\nConsejo: Usar un layout de <letra><numero>, donde las letras marcan la \"serie de Plantel\".";
    getline(cin, codigoPlantel);

    cout << "\t\tIngrese el tipo de plantel (Ej: Estandar, Premium, SUV, 4x4): ";
    getline(cin, tipoPlantel);

    cout << "\t\tIngrese el numero de filas: ";
    while (!(cin >> filas) || filas <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\t\tValor invalido. Intente de nuevo: ";
    }

    cout << "\t\tIngrese el numero de columnas: ";
    while (!(cin >> columnas) || columnas <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\t\tValor invalido. Intente de nuevo: ";
    }

    cin.ignore(10000, '\n'); // limpiar buffer

    Plantel* nuevoPlantel = new Plantel(codigoPlantel, tipoPlantel, filas, columnas);
    sucursal->getListaPlantel()->agregarPlantel(nuevoPlantel);

    cout << "\n\t\tPlantel creado exitosamente para la sucursal '"
        << sucursal->getNombre() << "'." << endl;

    cout << nuevoPlantel->toString() << endl;
}


Estacionamiento* Utilidades::obtenerRecomendacion(Plantel* plantel) {
    // Itera la matriz en busca del primer espacio no ocupado [cite: 2077]
    MatrizEstacionamientos* matriz = plantel->getMatrizEstacionamientos();
    for (int i = 0; i < matriz->getFilas(); ++i) {
        for (int j = 0; j < matriz->getColumnas(); ++j) {
            Estacionamiento* espacio = matriz->getEstacionamiento(i, j);
            if (espacio != NULL && !espacio->getOcupado()) { // [cite: 2004]
                return espacio;
            }
        }
    }
    return NULL;
}




void Utilidades::ingresarVehiculo() {
    limpiarConsola();

    string plac, mar, mod, tipLic, est, codigoSucursal, feAc;
    char cat;

    cout << "\n\t\t--- INGRESO DE NUEVO VEHÍCULO ---" << endl;

    // 1. Ingreso de datos del Vehículo
    cout << "\t\tIngrese la placa del Vehiculo: ";
    getline(cin, plac);

    cout << "\t\tIngrese la marca del Vehiculo: ";
    getline(cin, mar);

    cout << "\t\tIngrese el modelo del Vehiculo: ";
    getline(cin, mod);

    cout << "\t\tIngrese el tipo de licencia (Ej: A1, B1, etc.): ";
    getline(cin, tipLic);

    cout << "\t\tIngrese la fecha Actual: ";
    getline(cin, feAc);


    cout << "\t\tIngrese la categoría (Ej: 'S' Sedan, 'C' Coupe, 'T' TodoTerreno): ";
    while (!(cin >> cat) || (cat != 'S' && cat != 'C' && cat != 'T')) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\t\tValor invalido. Use 'S', 'C' o 'T': ";
    }

    cin.ignore(10000, '\n'); // limpiar buffer

    est = "Disponible"; // Estado inicial (necesario para la Bitácora)
    Vehiculo* nuevoVehiculo = new Vehiculo(plac, mar, mod, tipLic, cat, est);
    


    // 2. Asignación a Sucursal
    cout << "\n\t\t--- ASIGNACIÓN A SUCURSAL Y ESTACIONAMIENTO ---" << endl;
    cout << "\t\tIngrese el codigo de la sucursal de destino: ";
    getline(cin, codigoSucursal);

    Sucursal* sucursal = listaSucursales->buscar(codigoSucursal);
    if (sucursal == NULL) {
        cout << "\t\tERROR: No se encontro ninguna sucursal con ese codigo." << endl;
        delete nuevoVehiculo;
        pausa();
        return;
    }

    // 3. Obtener Recomendación de Espacio (9 pts)
    Estacionamiento* recomendado = NULL;
    Plantel* plantelRecomendado = NULL;

    // Iteración usando la estructura NodoPlantel que proporcionaste:
    NodoPlantel* actual = sucursal->getListaPlantel()->getCab(); // Asumo getCab() existe y retorna el primer NodoPlantel

    while (actual != NULL && recomendado == NULL) {
        Plantel* plantel = actual->getDato(); // Usamos getDato() de NodoPlantel
        MatrizEstacionamientos* matriz = plantel->getMatrizEstacionamientos();

        // Buscar el primer espacio disponible en este plantel (RECOMENDACIÓN)
        for (int i = 0; i < matriz->getFilas(); ++i) {
            for (int j = 0; j < matriz->getColumnas(); ++j) {
                Estacionamiento* espacio = matriz->getEstacionamiento(i, j);
                if (espacio != NULL && !espacio->getOcupado()) {
                    recomendado = espacio;
                    plantelRecomendado = plantel;
                    break; // Salir del bucle de columnas
                }
            }
            if (recomendado != NULL) {
                break; // Salir del bucle de filas
            }
        }

        // Mover al siguiente nodo (Usamos getSiguiente() de NodoPlantel)
        actual = actual->getSiguiente();
    }


    if (recomendado == NULL) {
        cout << "\n\t\tERROR: La sucursal " << sucursal->getNombre() << " no tiene espacios de estacionamiento disponibles en ninguno de sus planteles." << endl;
        delete nuevoVehiculo;
        pausa();
        return;
    }

    // 4. Vincular el Vehículo al Espacio y Almacenar
    string codEspacio = recomendado->getCodigo();

    cout << "\n\t\t--- RECOMENDACIÓN GENERADA POR EL SISTEMA ---" << endl;
    cout << "\t\tPlantel recomendado: " << plantelRecomendado->getCodigoPlantel() << endl;
    cout << "\t\tEspacio de Estacionamiento recomendado: " << codEspacio << endl;
    cout << "\t\t¿Desea estacionar el vehículo en esta ubicación? (S/N): ";

    char resp;
    cin >> resp;
    cin.ignore(10000, '\n');

    if (resp == 'S' || resp == 's') {
        // A) VINCULACIÓN AL ESPACIO (9 pts)
        recomendado->setVehiculo(nuevoVehiculo);
        recomendado->ocupar();

        // B) AGREGAR VEHÍCULO A LA LISTA DE LA SUCURSAL (Asunción necesaria)
        // Se requiere este método para almacenar el vehículo.
        sucursal->getListaVehiculos()->agregarAlInicio(nuevoVehiculo);
        string ubicacion = plantelRecomendado->getCodigoPlantel() + "-" + codEspacio;
        string colaboradorId = "e"; // CAMBIO URGENTE

        // C) REGISTRO DE ESTADO EN BITÁCORA (4 pts, asumiendo setEstado fue modificado)
        nuevoVehiculo->setEstado("Disponible", ubicacion, "Sistema/Usuario-Ingreso");

        cout << "\n\t\tVehículo PLACA " << plac << " ingresado y estacionado exitosamente." << endl;
        cout << "\t\tUbicado en Sucursal: " << sucursal->getNombre()
            << ", Espacio: " << codEspacio << endl;
    }
    else {
        cout << "\n\t\tOperación cancelada. El vehículo NO fue ingresado ni estacionado." << endl;
        delete nuevoVehiculo;
    }

    pausa();
}
void Utilidades::visualizarPlantel() {
    limpiarConsola();
    cout << "\n\t\t--- VISUALIZACIÓN DE ESTACIONAMIENTOS POR PLANTEL (5 pts) ---" << endl;

    // 1. Seleccionar Sucursal (Usando el método auxiliar existente)
    Sucursal* suc = seleccionarSucursal();
    if (suc == nullptr) {
        pausa();
        return;
    }

    // 2. Mostrar planteles disponibles y solicitar el código
    string codigoPlantel;

    cout << "\n\t\t--- PLANTEL DISPONIBLE EN SUCURSAL " << suc->getNombre() << " ---" << endl;
    // Asumo que getListaPlantel()->toString() lista los códigos de planteles.
    cout << suc->getListaPlantel()->toString() << endl;

    cout << "\t\tIngrese el código del plantel a visualizar: ";
    getline(cin, codigoPlantel);

    // 3. Buscar el plantel específico (Reemplazando buscarPlantel(suc))
    Plantel* plantel = nullptr;
    // INICIO DEL RECORRIDO DE LA LISTA DE PLANTELES
    NodoPlantel* actual = suc->getListaPlantel()->getCab();

    while (actual != nullptr) {
        if (actual->getDato()->getCodigoPlantel() == codigoPlantel) {
            plantel = actual->getDato();
            break; // Plantel encontrado, salir del bucle
        }
        actual = actual->getSiguiente(); // Avanzar al siguiente nodo
    }

    if (plantel == nullptr) {
        cout << "\t\tERROR: Plantel con código " << codigoPlantel << " no encontrado en la sucursal." << endl;
        pausa();
        return;
    }


    // 4. Visualización de la distribución (muestra estado Ocupado/Disponible)
    cout << "\n\t\t--- DISTRIBUCIÓN GRÁFICA DEL PLANTEL " << plantel->getCodigoPlantel() << " ---" << endl;
    // Se asume que Plantel::toString() genera la representación gráfica.
    cout << plantel->toString() << endl;


    // 5. Ingresar y buscar espacio específico
    string codEspacio;
    cout << "\n\t\tIngrese el número de espacio de estacionamiento (Ej: A01) para ver la placa: ";
    getline(cin, codEspacio);

    // Asumo que MatrizEstacionamientos tiene un método de búsqueda por código
    MatrizEstacionamientos* matriz = plantel->getMatrizEstacionamientos();
    Estacionamiento* espacio = matriz->buscarEstacionamiento(codEspacio);

    if (espacio == nullptr) {
        cout << "\t\tERROR: Espacio no encontrado en el plantel (Código inválido)." << endl;
    }
    else if (espacio->getOcupado()) {
        // Mostrar la placa del vehículo estacionado (Requisito 5 pts)
        cout << "\n\t\t--- DETALLE DEL ESPACIO " << codEspacio << " ---" << endl;
        cout << "\t\tEstado: Ocupado" << endl;
        cout << "\t\tPlaca del Vehículo Estacionado: " << espacio->getVehiculo()->getPlaca() << endl;
    }
    else {
        cout << "\t\tEstado: Disponible" << endl;
        cout << "\t\tNo hay vehículo estacionado en el espacio " << codEspacio << "." << endl;
    }

    pausa();
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
    cout << "\t\t1. Cliente Fisico" << endl;
    cout << "\t\t2. Cliente Juridico" << endl;
    cout << "\t\tSeleccione el tipo de cliente (1 o 2): ";
    tipoCliente = leerOpcion(1, 2); // Esta funcion ya limpia el buffer

    cout << "\n";

    // ===========================================
    // FLUJO PARA CLIENTE FiSICO
    // ===========================================
    if (tipoCliente == 1) {
        cout << "\t\t<< DATOS DE CLIENTE FISICO >>" << endl;

        // El buffer esta limpio por leerOpcion()
        cout << "\t\tIngrese la cedula: ";
        getline(cin, cedula);

        cout << "\t\tIngrese el nombre completo: ";
        getline(cin, nombre);

        cout << "\t\tIngrese el correo electronico: ";
        getline(cin, correo);

        cout << "\t\tIngrese el numero de telefono: ";
        getline(cin, telefono);

        cout << "\t\tIngrese la fecha de nacimiento (dd/mm/aaaa): ";
        getline(cin, fNacimiento);

        cout << "\t\tIngrese la fecha de inscripcion (dd/mm/aaaa): ";
        getline(cin, fInscripcion);

        cout << "\t\tIngrese el sexo (M/F): ";
        cin >> sexo;
        cin.ignore(10000, '\n'); // Limpiar buffer despues de cin >> char

        nuevoCliente = new ClienteFisico(cedula, nombre, correo, telefono, sexo, fNacimiento, fInscripcion);

    }
    // ===========================================
    // FLUJO PARA CLIENTE JURiDICO (Con correccion de bug)
    // ===========================================
    else if (tipoCliente == 2) {
        double descuento;
        string actividad;

        cout << "\t\t<< DATOS DE CLIENTE JURiDICO >>" << endl;

        cout << "\t\tIngrese la cedula juridica: ";
        getline(cin, cedula);

        cout << "\t\tIngrese el nombre completo: ";
        getline(cin, nombre);

        cout << "\t\tIngrese el correo electronico: ";
        getline(cin, correo);

        cout << "\t\tIngrese el numero de telefono: ";
        getline(cin, telefono);

        cout << "\t\tIngrese la fecha de nacimiento (dd/mm/aaaa): ";
        getline(cin, fNacimiento);

        cout << "\t\tIngrese la fecha de inscripcion (dd/mm/aaaa): ";
        getline(cin, fInscripcion);

        cout << "\t\tIngrese el sexo (M/F): ";
        cin >> sexo;
        cin.ignore(10000, '\n');

        cout << "\t\tIngrese el porcentaje de descuento (0.0 a 100.0): ";
        while (!(cin >> descuento)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\t\tValor invalido. Ingrese un numero para el descuento: ";
        }

        cin.ignore(10000, '\n'); // 

        cout << "\t\tIngrese la actividad economica: ";
        getline(cin, actividad);

        nuevoCliente = new ClienteJuridico(cedula, nombre, correo, telefono, sexo, fNacimiento, fInscripcion, descuento, actividad);
    }

    // Retorna el puntero, no lo añade a ninguna lista
    return nuevoCliente;
}
void Utilidades::ingresarCliente() {
    Cliente* nuevoCliente = leerDatosCliente(); // Usa la nueva funcion
    
    if (nuevoCliente != NULL) {
        listaClientes->agregarCliente(nuevoCliente);
        cout << "\n\t\tCliente registrado con exito en la LISTA GLOBAL." << endl;
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

        // Pedir datos comunes (Asegurandonos de usar getline para strings con espacios)
        cout << "\t\tIngrese la cedula: ";
        getline(cin, cedula);

        cout << "\t\tIngrese el nombre completo: ";
        getline(cin, nombre);

        cout << "\t\tIngrese el correo electronico: ";
        getline(cin, correo);

        cout << "\t\tIngrese el numero de telefono: ";
        getline(cin, telefono);

        cout << "\t\tIngrese la fecha de nacimiento (dd/mm/aaaa): ";
        getline(cin, fNacimiento);

        cout << "\t\tIngrese la fecha de ingreso (dd/mm/aaaa): ";
        getline(cin, fInscripcion);
        fechaIngreso = fInscripcion;

        // Pedir dato especifico
        cout << "\t\tIngrese el sexo (M/F): ";
        cin >> sexo;
        cin.ignore(10000, '\n');

        cout << "\t\tIngrese el Puesto del Colaborador:";
        getline(cin, puesto);

        // Crear el objeto dinamico
        nuevoColaborador = new Colaborador(cedula, nombre, correo, telefono, sexo, fNacimiento, fInscripcion);
        return nuevoColaborador;
}

void Utilidades::ingresarColaborador() {
    Colaborador* nuevoColaborador = leerDatosColaborador();
    
    if (nuevoColaborador != NULL) {
        listaColaboradores->agregarColaborador(nuevoColaborador);
        cout << "\n\t\tColaborador registrado con exito." << endl;
        cout << "\t\tDatos del nuevo Colaborador:\n" << nuevoColaborador->toString() << endl;
    }
    else {
        cout << "\t\tERROR: No se pudo crear el Colaborador." << endl;
    }
}

// ====================================================
// IMPLEMENTACION DE GESTION DE SUCURSALES
// ====================================================

void Utilidades::ingresarSucursal() {
    string codigo, nombre, direccion, telefono;

    limpiarConsola();
    cout << "\n\t\t--- INGRESO DE NUEVA SUCURSAL ---" << endl;

    cout << "\t\tIngrese el codigo de la sucursal: ";
    getline(cin, codigo);

    
    if (listaSucursales->buscar(codigo) != NULL) {
        cout << "\t\tERROR: Ya existe una sucursal con el codigo " << codigo << endl;
        return;
    }

    cout << "\t\tIngrese el nombre de la sucursal: ";
    getline(cin, nombre);

    cout << "\t\tIngrese la direccion: ";
    getline(cin, direccion);

    cout << "\t\tIngrese el telefono: ";
    getline(cin, telefono);

    // Asumiendo el constructor: Sucursal(codigo, nombre, direccion, telefono)
    Sucursal* nuevaSucursal = new Sucursal(codigo, nombre, direccion, telefono);

    listaSucursales->agregarSucursal(nuevaSucursal); // Asume metodo agregarSucursal en ListaSucursal

    cout << "\n\t\tSucursal '" << nombre << "' registrada con exito." << endl;
}

void Utilidades::mostrarSucursales() {
    limpiarConsola();
    cout << "\n\t\t--- VISUALIZACIoN DE TODAS LAS SUCURSALES ---" << endl;
    if (listaSucursales->estaVacia()) {
        cout << "\t\tLa lista de sucursales esta vacia." << endl;
        return;
    }
    cout << listaSucursales->toString() << endl; // Asume metodo toString en ListaSucursal
}


void Utilidades::eliminarSucursal() {
    string codigoEliminar;

    limpiarConsola();
    cout << "\n\t\t--- ELIMINAR SUCURSAL POR CODIGO ---" << endl;

    if (listaSucursales->estaVacia()) {
        cout << "\t\tLa lista de sucursales esta vacia." << endl;
        return;
    }

    cout << "\t\tIngrese el codigo de la sucursal a eliminar: ";
    getline(cin, codigoEliminar);

    // Asumiendo que ListaSucursal::eliminar(codigo) retorna bool
    if (listaSucursales->eliminar(codigoEliminar)) {
        cout << "\n\t\tLa sucursal con codigo " << codigoEliminar << " ha sido eliminada." << endl;
    }
    else {
        cout << "\n\t\tERROR: No se encontro ninguna sucursal con el codigo " << codigoEliminar << endl;
    }
}

// ====================================================
// IMPLEMENTACIoN DE GESTION POR SUCURSAL
// ====================================================

// Funcio auxiliar para encontrar la sucursal y operar en su lista interna de Clientes
void Utilidades::gestionarClientesPorSucursal(int operacion) {
    string codigoSucursal, cedulaCliente;
    limpiarConsola();

    cout << "\n\t\t--- GESTIoN DE CLIENTES POR SUCURSAL ---" << endl;
    cout << "\t\tIngrese el codigo de la sucursal: ";
    
    getline(cin, codigoSucursal);

    Sucursal* sucursal = listaSucursales->buscar(codigoSucursal); 

    if (sucursal == NULL) {
        cout << "\t\tERROR: Sucursal con codigo " << codigoSucursal << " no encontrada." << endl;
        return;
    }

    ListaCliente* listaClientesSucursal = sucursal->getClientes(); // Acceder a la lista interna

    if (operacion == 1) { // Ingreso
        cout << "\n\t\t>> INGRESANDO CLIENTE en Sucursal: " << sucursal->getNombre() << endl;

       
        Cliente* c = leerDatosCliente(); // Llama a la funcion que pide los datos y lo crea

        if (c != NULL) {
            // Decides a donde añadirlo:
            listaClientesSucursal->agregarCliente(c); // Añadir a la lista de la sucursal
            listaClientes->agregarCliente(c); // Si tambien lo quieres en la lista global

            cout << "\n\t\t Cliente registrado con exito en la sucursal." << endl;
            cout << "\t\tDatos del nuevo cliente:\n" << c->toString() << endl;
        }
        else {
            cout << "\t\t ERROR: No se pudo completar el registro del cliente." << endl;
        }
    }
    else if (operacion == 2) { // Visualizacion
        cout << "\n\t\t>> VISUALIZANDO Clientes de Sucursal: " << sucursal->getNombre() << endl;
        cout << listaClientesSucursal->toString() << endl;

    }
    else if (operacion == 3) { // Eliminacion
        cout << "\n\t\t>> ELIMINANDO Cliente de Sucursal: " << sucursal->getNombre() << endl;
        cout << "\t\tIngrese la cedula del cliente a eliminar: ";
        getline(cin, cedulaCliente);

        // Asume ListaCliente::eliminar(cedula) en la lista de la Sucursal
        if (listaClientesSucursal->eliminar(cedulaCliente)) {
            cout << "\t\tCliente con cedula " << cedulaCliente << " eliminado de la sucursal." << endl;
        }
        else {
            cout << "\t\tERROR: Cliente no encontrado en esta sucursal." << endl;
        }
    }
}


// Funcio auxiliar para encontrar la sucursal y operar en su lista interna de Colaboradores
void Utilidades::gestionarColaboradoresPorSucursal(int operacion) {
    string codigoSucursal, idColaborador;
    limpiarConsola();

    cout << "\n\t\t--- GESTION DE COLABORADORES POR SUCURSAL ---" << endl;
    cout << "\t\tIngrese el codigo de la sucursal: ";
    getline(cin, codigoSucursal);

    Sucursal* sucursal = listaSucursales->buscar(codigoSucursal);

    if (sucursal == NULL) {
        cout << "\t\tERROR: Sucursal con codigo " << codigoSucursal << " no encontrada." << endl;
        return;
    }

    ListaColaborador* listaColaboradoresSucursal = sucursal->getColaboradores(); // Acceder a la lista interna

    if (operacion == 1) { // Ingreso
        ingresarColaborador();
        cout << "\n\t\t>> INGRESANDO COLABORADOR en Sucursal: " << sucursal->getNombre() << endl;
        Colaborador* c = leerDatosColaborador(); // Llama a la funcion que pide los datos y lo crea

        if (c != NULL) {
            // Decides a donde añadirlo:
            listaColaboradoresSucursal->agregarColaborador(c); // Añadir a la lista de la sucursal

            cout << "\n\t\t Cliente registrado con exito en la sucursal." << endl;
            cout << "\t\tDatos del nuevo cliente:\n" << c->toString() << endl;
        }
        else {
            cout << "\t\t ERROR: No se pudo completar el registro del cliente." << endl;
        }

    }
    else if (operacion == 2) { // Visualizacion
        cout << "\n\t\t>> VISUALIZANDO Colaboradores de Sucursal: " << sucursal->getNombre() << endl;
        cout << listaColaboradoresSucursal->toString() << endl; // Asume ListaColaborador::toString

    }
    else if (operacion == 3) { // Eliminacion
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

// Implementacion del metodo auxiliar para buscar un vehiculo en todas las sucursales
Vehiculo* Utilidades::buscarVehiculoGlobal(string placa, string& codigoSucursalEncontrado) {

    // Obtiene el inicio de la lista de sucursales
    NodoSucursal* actualSucursal = listaSucursales->getCab();

    while (actualSucursal != NULL) {

        Sucursal* suc = actualSucursal->getDato();
        ListaVehiculo* listaVehiculos = suc->getListaVehiculos();

        // Busca el vehiculo en la lista de la sucursal actual
        Vehiculo* vehiculo = listaVehiculos->buscar(placa);

        if (vehiculo != NULL) {
            // Asigna el codigo de la sucursal actual a la referencia
            codigoSucursalEncontrado = suc->getCodigoSucursal();
            return vehiculo; // Devuelve el vehiculo
        }

        // Avanza al siguiente nodo
        actualSucursal = actualSucursal->getSiguiente();
    }
    return NULL; // Vehiculo no encontrado
}


// ========================================================
// 2. IMPLEMENTACIoN DEL MeTODO DE PRESENTACIoN
//    (Este es el que tenia el error de llamada al 'buscar')
// ========================================================
void Utilidades::mostrarInformacionVehiculoGlobal(string placa) {

    // Variable para capturar el resultado de la busqueda
    string codigoSucursalDelVehiculo = "";

    // LiNEA CORREGIDA: Usando 'this->' para llamar al metodo miembro 'buscarVehiculoGlobal'
    Vehiculo* vehiculoEncontrado = buscarVehiculoGlobal(placa, codigoSucursalDelVehiculo);

    // Imprimimos el resultado
    if (vehiculoEncontrado != NULL) {
        cout << "\t\t===================================================" << endl;
        cout << "\t\t--- RESULTADO DE LA BuSQUEDA GLOBAL ---" << endl;
        cout << "\t\t¡Vehiculo encontrado!" << endl;
        cout << "\t\tPlaca: " << vehiculoEncontrado->getPlaca() << endl;
        cout << "\t\tMarca: " << vehiculoEncontrado->getMarca() << endl;
        cout << "\t\tModelo: " << vehiculoEncontrado->getModelo() << endl;
        cout << "\t\tTipp Licencia: " << vehiculoEncontrado->getTipoLicencia() << endl;
        cout << "\t\tPrecio por dia: " << vehiculoEncontrado->getPrecioDiario() << endl;
        cout << "\t\tCategoria: " << vehiculoEncontrado->getCategoria() << endl;
        cout << "\t\tEstado: " << vehiculoEncontrado->getEstado() << endl;

        cout << "\t\tUbicacion (Codigo Sucursal): " << codigoSucursalDelVehiculo << endl;
        cout << "\t\t===================================================" << endl;
    }
    else {
        cout << "\t\t===================================================" << endl;
        cout << "\t\t--- RESULTADO DE LA BuSQUEDA GLOBAL ---" << endl;
        cout << "\t\tEl vehiculo con placa [" << placa << "] no se encontro en ninguna sucursal." << endl;
        cout << "\t\t===================================================" << endl;
    }
}
void Utilidades::CrearSolicitud() {
    string codigoSoli, cedulaCliente, idColaborador, codigoSucursal, placaVehiculo, fIni, fFin;
    int dias = 0;
    double precioTotal = 0.0;

    // Punteros a las entidades que necesitamos:
    
    Colaborador* colaborador = NULL;
    Sucursal* sucursal = NULL;
    Vehiculo* vehiculo = NULL;

    limpiarConsola();
    cout << "\n\t\t--- CREACIoN DE NUEVA SOLICITUD DE ALQUILER ---" << endl;

    // 1. Obtener y buscar el Cliente (Cedula)
    cout << "\t\tIngrese la cedula del Cliente: ";
    getline(cin, cedulaCliente);
    Cliente * cliente = listaClientes->buscar(cedulaCliente);
    if (cliente == NULL) {
        cout << "\t\tERROR: Cliente con cedula " << cedulaCliente << " no encontrado." << endl;
        pausa();
        return;
    }

    // 2. Obtener y buscar el Colaborador (Cedula)
    cout << "\t\tIngrese la cedula del Colaborador que registra: ";
    getline(cin, idColaborador);
    colaborador = listaColaboradores->buscar(idColaborador);
    if (colaborador == NULL) {
        cout << "\t\tERROR: Colaborador con cedula " << idColaborador << " no encontrado." << endl;
        pausa();
        return;
    }

    // 3. Obtener y buscar el Vehiculo (Placa)
    cout << "\t\tIngrese la Placa del Vehiculo a alquilar: ";
    getline(cin, placaVehiculo);

    // *** CAMBIO CRUCIAL ***: 
    // Llamamos a buscarVehiculoGlobal con dos argumentos: la placa y la variable 'codigoSucursal' 
    // que se llenara con el codigo de la sucursal que tiene el carro.
    vehiculo = this->buscarVehiculoGlobal(placaVehiculo, codigoSucursal); // <-- AQUi ESTa EL CAMBIO

    if (vehiculo == NULL) {
        cout << "\t\tERROR: Vehiculo con placa " << placaVehiculo << " no encontrado en ninguna sucursal." << endl;
        pausa();
        return;
    }

    // 4. Validar estado del vehiculo
    if (vehiculo->getEstado() != "Disponible") {
        cout << "\t\tERROR: El vehiculo " << placaVehiculo << " no esta disponible. Estado actual: " << vehiculo->getEstado() << endl;
        pausa();
        return;
    }

    // 5. Obtener y buscar la Sucursal (Codigo)
    // El 'codigoSucursal' ya fue llenado por la funcion buscarVehiculoGlobal.
    sucursal = listaSucursales->buscar(codigoSucursal);

    // Si la sucursal es NULL, es un error interno grave, ya que el codigo se obtuvo de una Sucursal existente.
    if (sucursal == NULL) {
        cout << "\t\tERROR INTERNO: Sucursal asociada al vehiculo no encontrada." << endl;
        pausa();
        return;
    }


    // 6. Datos de la Solicitud
    cout << "\t\tIngrese el codigo de la nueva Solicitud (ej. S001): ";
    getline(cin, codigoSoli);
    cout << "\t\tIngrese la Fecha de Inicio (DD/MM/AAAA): ";
    getline(cin, fIni);
    cout << "\t\tIngrese la Fecha de Entrega Estimada (DD/MM/AAAA): ";
    getline(cin, fFin);
    cout << "\t\tIngrese la cantidad de dias de alquiler: ";

    // Logica para leer 'dias' (entero)
    cin >> dias;
    // Agregamos una verificacion simple para la lectura
    if (cin.fail()) {
        cin.clear();
        cout << "\t\tEntrada invalida. Dias de alquiler deben ser un numero." << endl;
        pausa();
        cin.ignore(10000, '\n');
        return;
    }
    cin.ignore(10000, '\n'); // Limpiar buffer

    // 7. Calculo del Precio Total
    if (dias <= 0) {
        cout << "\t\tERROR: Los dias de alquiler deben ser un numero positivo." << endl;
        pausa();
        return;
    }

    precioTotal = vehiculo->getPrecioDiario() * dias;

    // 8. Creacion de la Solicitud
    // Asumo que SolicitudAlquiler requiere un puntero a Sucursal
    SolicitudAlquiler* nuevaSoli = new SolicitudAlquiler(
        codigoSoli, cliente, colaborador, sucursal, vehiculo, fIni, fFin,
        precioTotal, "Pendiente" // Estado inicial
    );
    nuevaSoli->setCanDiasAlqui(dias);

    listaSolicitudes->agregarSolicitud(nuevaSoli);

    cout << "\n\t\t--- SOLICITUD CREADA CON eXITO ---" << endl;
    cout << nuevaSoli->toString() << endl;
    pausa();
}


void Utilidades::VerSolicitudesContratos() {
    limpiarConsola();
    cout << "\n\t\t===================================================" << endl;
    cout << "\t\t--- VISUALIZACIoN DE SOLICITUDES Y CONTRATOS ---" << endl;
    cout << "\t\t===================================================" << endl;

    // 1. Mostrar todas las Solicitudes
    cout << "\n\t\t--- 1. LISTA DE SOLICITUDES DE ALQUILER ---" << endl;
    if (listaSolicitudes->estaVacia()) {
        cout << "\t\t[INFO] No hay solicitudes registradas actualmente." << endl;
    }
    else {
        // Asumo que ListaSolicitud tiene un metodo 'toString()' o 'mostrar()'
        // que imprime todas las solicitudes. Usaremos toString() si esta implementado
        // en la lista, si no, se puede iterar, pero asumimos el metodo de la lista.
        cout << listaSolicitudes->toString();
    }
    cout << "\t\t---------------------------------------------------" << endl;


    // 2. Mostrar todos los Contratos
    cout << "\n\t\t--- 2. LISTA DE CONTRATOS DE ALQUILER ---" << endl;
    if (listaContratos->estaVacia()) {
        cout << "\t\t[INFO] No hay contratos registrados actualmente." << endl;
    }
    else {
        // Asumo que ListaContrato tiene un metodo 'toString()' o 'mostrar()'
        cout << listaContratos->toString();
    }
    cout << "\t\t---------------------------------------------------" << endl;

    pausa();
}




//jaja
void Utilidades::AprobarRechazarSolicitud() {
    string codigoSoli;
    string idColaborador;
    char opcion;
    limpiarConsola();
    cout << "\n\t\t--- APROBACIoN / RECHAZO DE SOLICITUD (1 pto) ---" << endl;

    cout << "\t\tIngrese el codigo de la Solicitud a procesar: ";
    getline(cin, codigoSoli);

    SolicitudAlquiler* solicitud = listaSolicitudes->buscar(codigoSoli);

    if (solicitud == NULL || solicitud->getEstado() != "Pendiente") {
        cout << "\t\tERROR: Solicitud no encontrada o ya procesada." << endl;
    }
    else {
        cout << "\n\t\t--- DETALLE DE LA SOLICITUD ---" << endl;
        cout << solicitud->toString() << endl;
        cout << "\t\tIngrese el ID del Colaborador que aprueba/rechaza: "; // Solicitud del ID
        getline(cin, idColaborador);
        cout << "\t\t[A]probar o [R]echazar la solicitud? (A/R): ";
        cin >> opcion;
        cin.ignore(10000, '\n');

        if (opcion == 'A' || opcion == 'a') {
            solicitud->setEstado("Aprobada");

            // 1. Cambiar estado del vehiculo
            Vehiculo* vehiculo = solicitud->getVehiculo();
            //string ubicacion = "EN_USO_" + solicitud->getCodigo(); // Ubicación temporal
            //string fechaActual = obtenerFechaActual();
            vehiculo->setEstado("Alquilado");
            //vehiculo->setEstado("Alquilado", ubicacion, idColaborador, fechaActual);

            // 2. Crear Contrato
            string codigoContrato = "CONT-" + codigoSoli;
            ContratoAlquiler* nuevoContrato = new ContratoAlquiler(
                codigoContrato, solicitud->getPrecioTotal(), "Activo", solicitud
            );

            listaContratos->agregarContrato(nuevoContrato);

            cout << "\n\t\t¡APROBACIoN EXITOSA! Contrato " << codigoContrato << " creado." << endl;

        }
        else if (opcion == 'R' || opcion == 'r') {
            solicitud->setEstado("Rechazada");
            cout << "\n\t\t¡RECHAZO EXITOSO! Solicitud " << codigoSoli << " rechazada." << endl;
        }
        else {
            cout << "\t\tOpcion invalida. No se realizo ninguna accion." << endl;
        }
    }
    pausa();
}




void Utilidades::RecepcionVehiculo() {
    string codigoContrato;
    limpiarConsola();
    cout << "\n\t\t--- RECEPCIoN DE VEHiCULO Y FINALIZACIoN DE CONTRATO (3 pts) ---" << endl;

    cout << "\t\tIngrese el codigo del Contrato a finalizar: ";
    getline(cin, codigoContrato);

    ContratoAlquiler* contrato = listaContratos->buscar(codigoContrato);

    if (contrato == NULL) {
        cout << "\t\tERROR: Contrato con codigo " << codigoContrato << " no encontrado." << endl;
    }
    else if (contrato->getEstado() == "Finalizado") {
        cout << "\t\tERROR: El contrato ya se encuentra 'Finalizado'." << endl;
    }
    else if (contrato->getEstado() == "Activo") {

        // 1. Finalizar el Contrato
        contrato->setEstado("Finalizado");

        // 2. Obtener Vehiculo y cambiar su estado
        Vehiculo* vehiculo = contrato->getSolicitud()->getVehiculo();

        // Transicion: Alquilado -> Devuelto (segun su logica interna)
        vehiculo->setEstado("Devuelto");

        cout << "\n\t\t¡RECEPCIoN EXITOSA!" << endl;
        cout << "\t\tEl contrato " << codigoContrato << " ha sido marcado como 'Finalizado'." << endl;
        cout << "\t\tEl vehiculo " << vehiculo->getPlaca() << " ha sido marcado como 'Devuelto'." << endl;
        cout << "\t\tNOTA: El vehiculo en estado 'Devuelto' debe pasar a 'Revision' o 'Lavado'." << endl;

    }
    else {
        cout << "\t\tERROR: El contrato no esta en estado 'Activo'." << endl;
    }
    pausa();
}


// ----------------------------------------------------
// Implementacion de Control de Interfaz y Consola
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
    cout << "\t\tDigite la opcion deseada: ";

    // 🚨 USO EXPLiCITO DE cin >>
    while (!(cin >> opcion) || opcion < min || opcion > max) {
        cin.clear();
        cin.ignore(10000, '\n'); // Limpieza del buffer
        cout << "\t\tOpcion invalida. Ingrese un numero entre [" << min << "] y [" << max << "]: ";
    }
    cin.ignore(10000, '\n'); // Limpieza del buffer
    return opcion;
}



// ----------------------------------------------------
// Implementacion de Funciones de Menu
// ----------------------------------------------------


void Utilidades::ejecutarSistema() {
    int opcion = -1;

    while (opcion != 0) {
        mostrarMenuPrincipal();
        opcion = this->op;

        switch (opcion) {
            // ... (casos 0 a 5) ...
        case 1:
            // Llama al submenu de Sucursales
            mostrarSubmenuSucursales();
            break;
        case 2:
            // Llama al submenu de Colaboradores
            mostrarSubmenuColaboradores();
            break;
        case 3:
            // Llama al submenu de Carros y Planteles
            mostrarSubmenuCarrosPlanteles();
            break;
        case 4:
            // Llama al submenu de Solicitudes y Contratos
            mostrarSubmenuSolicitudesContratos();
            break;
        case 5:
            // Llama al submenu de Clientes
            mostrarSubmenuClientes();
            break;
        case 0:
            cout << "\n\t\tGracias por usar el sistema. ¡Adios!" << endl;
            break;
        }

        // Resetea 'op' para volver a mostrar el Menu Principal
        this->op = -1;
    }
}
void Utilidades::mostrarMenuPrincipal() {
        limpiarConsola();
        cout << "\n\t\t======================================================" << endl;
        cout << "\t\t       C A D E N A   D E   R E N T A   A   C A R      " << endl;
        cout << "\t\t             \"D - R - T   C a r   R e n t a l\"      " << endl;
        cout << "\t\t======================================================" << endl;
        cout << "\t\t(1) Submenu de Sucursales" << endl;
        cout << "\t\t(2) Submenu de Colaboradores" << endl;
        cout << "\t\t(3) Submenu de Carros y Planteles" << endl;
        cout << "\t\t(4) Submenu de Solicitudes y Contratos" << endl;
        cout << "\t\t(5) Submenu de Clientes" << endl;
        cout << "\t\t(0) SALIR DEL SISTEMA" << endl;
        cout << "\t\t------------------------------------------------------" << endl;
        op = leerOpcion(0, 5);
    }



void Utilidades::mostrarSubmenuSucursales() {
    int opcionSubmenu = -1; // Inicializamos a un valor != 0 para entrar al bucle.

    // El bucle se ejecuta mientras la opcion NO sea 0 (Regresar al Menu Principal).
    while (opcionSubmenu != 0) {

        // 1. Mostrar el menu
        limpiarConsola();
        cout << "\n\t\t======================================================" << endl;
        cout << "\t\t                SUBMENu DE SUCURSALES                 " << endl;
        cout << "\t\t======================================================" << endl;
        cout << "\t\t(1) Ingresar Sucursal" << endl;
        cout << "\t\t(2) Mostrar Sucursales" << endl;
        cout << "\t\t(3) Eliminar Sucursal" << endl;
        cout << "\t\t(0) Regresar al Menu Principal" << endl;
        cout << "\t\t------------------------------------------------------" << endl;

        // 2. Leer la opcion (Rango de 0 a 3)
        // Llamada a la funcion de la misma clase.
        opcionSubmenu = leerOpcion(0, 3);

        // 3. Ejecutar la logica con switch
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
            // El bucle terminara automaticamente despues de esta iteracion.
            cout << "\n\t\tRegresando al Menu Principal..." << endl;
            break;
        }

        // Si la opcion NO es 0, hacemos una pausa para que el usuario vea el resultado de la accion.
        if (opcionSubmenu != 0) {
            cout << "\t\tPresione ENTER para volver al submenu...";
            // usamos cin.get() aqui para esperar una pulsacion.
            cin.get();
        }

    } // Fin del while
}
void Utilidades::mostrarSubmenuColaboradores() {
    int opcionSubmenu = -1; // Inicializamos a un valor != 0 para entrar al bucle.

    // El bucle se ejecuta mientras la opcion NO sea 0 (Regresar al Menu Principal).
    while (opcionSubmenu != 0) {

        // 1. Mostrar el menu
        limpiarConsola();
        cout << "\n\t\t======================================================" << endl;
        cout << "\t\t               SUBMENu DE COLABORADORES               " << endl;
        cout << "\t\t======================================================" << endl;
        cout << "\t\t(1) Incluir Colaborador en Sucursal" << endl;
        cout << "\t\t(2) Mostrar Colaborador" << endl;
        cout << "\t\t(3) Eliminar Colaborador" << endl;
        cout << "\t\t(4) Reporte de alquileres por colaborador" << endl;
        cout << "\t\t(0) Regresar al Menu Principal" << endl;
        cout << "\t\t------------------------------------------------------" << endl;

        // 2. Leer la opcion (Rango de 0 a 4)
        // Llamada a la funcion de la misma clase.
        opcionSubmenu = leerOpcion(0, 4);

        // 3. Ejecutar la logica con switch
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
            // El bucle terminara automaticamente despues de esta iteracion.
            cout << "\n\t\tRegresando al Menu Principal..." << endl;
            break;
        }

        // Si la opcion NO es 0, hacemos una pausa para que el usuario vea el resultado de la accion.
        if (opcionSubmenu != 0) {
            cout << "\t\tPresione ENTER para volver al submenu...";
            // usamos cin.get() aqui para esperar una pulsacion.
            cin.get();
        }

    } // Fin del while
}



void Utilidades::mostrarSubmenuCarrosPlanteles() {
    int opcionSubmenu = -1; // Inicializamos a un valor != 0 para entrar al bucle.

    // El bucle se ejecuta mientras la opcion NO sea 0 (Regresar al Menu Principal).
    while (opcionSubmenu != 0) {

        // 1. Mostrar el menu
        limpiarConsola();
        cout << "\n\t\t======================================================" << endl;
        cout << "\t\t            SUBMENu DE CARROS Y PLANTELES             " << endl;
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
        cout << "\t\t(0) Regresar al Menu Principal" << endl;
        cout << "\t\t------------------------------------------------------" << endl;

        // 2. Leer la opcion (Rango de 0 a 10)
        // Llamada a la funcion de la misma clase.
        opcionSubmenu = leerOpcion(0, 10);

        // 3. Ejecutar la logica con switch
        switch (opcionSubmenu) {
        case 1:
            cout << "\n\t\t>> Ejecutando: Crear Plantel..." << endl;
            Utilidades::crearPlantelSucursal();
            break;
        case 2:
            cout << "\n\t\t>> Ejecutando: Visualizacion Grafica de Plantel..." << endl;
            //Utilidades::visualizarPlantel();
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
            // El bucle terminara automaticamente despues de esta iteracion.
            cout << "\n\t\tRegresando al Menu Principal..." << endl;
            break;
        }

        // Si la opcion NO es 0, hacemos una pausa para que el usuario vea el resultado de la accion.
        if (opcionSubmenu != 0) {
            cout << "\t\tPresione ENTER para volver al submenu...";
            // usamos cin.get() aqui para esperar una pulsacion.
            cin.get();
        }

    } // Fin del while
}

void Utilidades::mostrarSubmenuSolicitudesContratos() {
    int opcionSubmenu = -1; // Inicializamos a un valor != 0 para entrar al bucle.

    // El bucle se ejecuta mientras la opcion NO sea 0 (Regresar al Menu Principal).
    while (opcionSubmenu != 0) {

        // 1. Mostrar el menu
        limpiarConsola();
        cout << "\n\t\t======================================================" << endl;
        cout << "\t\t          SUBMENu DE SOLICITUDES Y CONTRATOS          " << endl;
        cout << "\t\t======================================================" << endl;
        cout << "\t\t(1) Creacion de Solicitud" << endl;
        cout << "\t\t(2) Visualizacion de solicitudes/contratos por sucursal" << endl;
        cout << "\t\t(3) Visualizacion de solicitud/contratos especifica" << endl;
        cout << "\t\t(4) Aprobacion/rechazo de solicitud" << endl;
        cout << "\t\t(5) Recepcion de vehiculo en prestado" << endl;
        cout << "\t\t(6) Reporte de contratos para vehiculos especifico" << endl;
        cout << "\t\t(7) Visualizar TODAS las Solicitudes/Contratos (Auxiliar)" << endl;
        cout << "\t\t(0) Regresar al Menu Principal" << endl;
        cout << "\t\t------------------------------------------------------" << endl;

        // 2. Leer la opcion (Rango de 0 a 7)
        // Llamada a la funcion de la misma clase.
        opcionSubmenu = leerOpcion(0, 7);

        // 3. Ejecutar la logica con switch
        switch (opcionSubmenu) {
        case 1:
            cout << "\n\t\t>> Ejecutando: Creacion  de solicitud..." << endl;
            this->CrearSolicitud();
            break;
        case 2:
            cout << "\n\t\t>> Ejecutando: Visualizacion de solicitudes/contratos por sucursal..." << endl;
            // llamar a funcion VerSoliCont_Sucursal();
            break;
        case 3:
            cout << "\n\t\t>> Ejecutando: Visualizacion de solicitud/contratos especifica..." << endl;
            // llamar a funcion VerSoliCont_Especifico();
            break;
        case 4:
            cout << "\n\t\t>> Ejecutando: Aprobacion/rechazo de solicitud..." << endl;
            this->AprobarRechazarSolicitud();
            break;
        case 5:
            cout << "\n\t\t>> Ejecutando: Recepcion de vehiculo en prestado ..." << endl;
            // llamar a funcion RecibirVehiPrestado();
            this->RecepcionVehiculo();
            break;
        case 6:
            cout << "\n\t\t>> Ejecutando: Reporte de contratos para vehiculos especifico..." << endl;
            // llamar a funcion ReporteContratosVehiEspecifico();
            break;
        case 7:
            cout << "\n\t\t>> Ejecutando: Visualizacion de todas las solicitudes / contratos..." << endl;
            this->VerSolicitudesContratos();
            break;
        case 0:
            // El bucle terminara automaticamente despues de esta iteracion.
            cout << "\n\t\tRegresando al Menu Principal..." << endl;
            break;
        }

        // Si la opcion NO es 0, hacemos una pausa para que el usuario vea el resultado de la accion.
        if (opcionSubmenu != 0) {
            cout << "\t\tPresione ENTER para volver al submenu...";
            // usamos cin.get() aqui para esperar una pulsacion.
            cin.get();
        }

    } // Fin del while
}


void Utilidades::mostrarSubmenuClientes() {
    int opcionSubmenu = -1; // Inicializamos a un valor != 0 para entrar al bucle.

    // El bucle se ejecuta mientras la opcion NO sea 0 (Regresar al Menu Principal).
    while (opcionSubmenu != 0) {

        // 1. Mostrar el menu
        limpiarConsola();
        cout << "\n\t\t======================================================" << endl;
        cout << "\t\t            SUBMENu DE CLIENTES                       " << endl;
        cout << "\t\t======================================================" << endl;
        cout << "\t\t(1) Ingresar Cliente" << endl;
        cout << "\t\t(2) Mostrar Cliente" << endl;
        cout << "\t\t(3) Eliminar Cliente" << endl;
        cout << "\t\t(4) Historial del Cliente" << endl;
        cout << "\t\t(5) Reporte de clientes por cantidad de contratos" << endl;
        cout << "\t\t(0) Regresar al Menu Principal" << endl;
        cout << "\t\t------------------------------------------------------" << endl;

        // 2. Leer la opcion (Rango de 0 a 5)
        // Llamada a la funcion de la misma clase.
        opcionSubmenu = leerOpcion(0, 5);

        // 3. Ejecutar la logica con switch
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
            // El bucle terminara automaticamente despues de esta iteracion.
            cout << "\n\t\tRegresando al Menu Principal..." << endl;
            break;
        }

        // Si la opcion NO es 0, hacemos una pausa para que el usuario vea el resultado de la accion.
        if (opcionSubmenu != 0) {
            cout << "\t\tPresione ENTER para volver al submenu...";
            // usamos cin.get() aqui para esperar una pulsacion.
            cin.get();
        }

    } // Fin del while
}