// Utilidades.cpp
#include "Utilidades.h"
#include "Sucursal.h"
#include "ListaEnlazada.h"
#include "ClienteFisico.h"
#include "ClienteJuridico.h"
#include "Colaborador.h"
#include <iostream>

using namespace std;

Utilidades::Utilidades() {
    // Inicializar la lista de clientes
    listaClientes = new ListaCliente();
    listaSucursales = new ListaSucursal();
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

//Implementacion de cositas jajaj
void Utilidades::ingresarCliente() {
    string cedula, nombre, correo, telefono, fNacimiento, fInscripcion;
    char sexo;
    int tipoCliente = -1;
    Cliente* nuevoCliente = NULL;
    limpiarConsola();
    cout << "\n\t\t--- INGRESO DE NUEVO CLIENTE ---" << endl;

    // 1. Determinar el tipo de cliente
    cout << "\t\t1. Cliente Físico" << endl;
    cout << "\t\t2. Cliente Jurídico" << endl;
    cout << "\t\tSeleccione el tipo de cliente (1 o 2): ";
    tipoCliente = leerOpcion(1, 2);
    cout << "\n";

    // ===========================================
    // FLUJO PARA CLIENTE FÍSICO
    // ===========================================
    if (tipoCliente == 1) {

        cout << "\t\t<< INGRESO DE CLIENTE FÍSICO >>" << endl;

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

        cout << "\t\tIngrese la fecha de inscripción (dd/mm/aaaa): ";
        getline(cin, fInscripcion);

        // Pedir dato específico
        cout << "\t\tIngrese el sexo (M/F): ";
        cin >> sexo;
        cin.ignore(10000, '\n'); // Limpiar buffer después de cin >> char

        // Crear el objeto dinámico
        nuevoCliente = new ClienteFisico(cedula, nombre, correo, telefono, sexo, fNacimiento, fInscripcion);

    }
    // ===========================================
    // FLUJO PARA CLIENTE JURÍDICO
    // ===========================================
    else if (tipoCliente == 2) {
        double descuento;
        string actividad;

        cout << "\t\t<< INGRESO DE CLIENTE JURÍDICO >>" << endl;

        // Pedir datos comunes (Asegurándonos de usar getline para strings con espacios)
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

        // Pedir datos específicos
        cout << "\t\tIngrese el porcentaje de descuento (0.0 a 100.0): ";
        // Función para leer un double de forma segura
        while (!(cin >> descuento)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\t\tValor inválido. Ingrese un número para el descuento: ";
        }
        cin.ignore(10000, '\n'); // Limpiar buffer después de cin >> double

        cout << "\t\tIngrese la actividad económica: ";
        getline(cin, actividad);

        // Crear el objeto dinámico. 'N' como sexo por defecto para empresas.
        nuevoCliente = new ClienteJuridico(cedula, nombre, correo, telefono, sexo, fNacimiento, fInscripcion, descuento, actividad);
    }
    // 3. Agregar a la lista
    if (nuevoCliente != NULL) {
        listaClientes->agregarCliente(nuevoCliente);
        cout << "\n\t\tCliente registrado con éxito." << endl;
        cout << "\t\tDatos del nuevo cliente:\n" << nuevoCliente->toString() << endl;
    }
    else {
        cout << "\t\tERROR: No se pudo crear el cliente (Tipo inválido)." << endl;
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
        cout << "\t\t❌ ERROR: Ya existe una sucursal con el código " << codigo << endl;
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

    cout << "\n\t\t✅ Sucursal '" << nombre << "' registrada con éxito." << endl;
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
    cin.get();
    getline(cin, codigoSucursal);

    Sucursal* sucursal = listaSucursales->buscar(codigoSucursal); // CLAVE: Buscar la sucursal

    if (sucursal == nullptr) {
        cout << "\t\t❌ ERROR: Sucursal con código " << codigoSucursal << " no encontrada." << endl;
        return;
    }

    ListaCliente* listaClientesSucursal = sucursal->getClientes(); // Acceder a la lista interna

    if (operacion == 1) { // Ingreso
        cout << "\n\t\t>> INGRESANDO CLIENTE en Sucursal: " << sucursal->getNombre() << endl;
        // Aquí se requiere una función auxiliar que pida los datos del cliente y lo retorne (ej. leerDatosCliente())
        // CLIENTE* c = leerDatosCliente(false); // Podrías reutilizar parte de ingresarCliente
        // listaClientesSucursal->agregarCliente(c);
        cout << "\t\t(PENDIENTE: Lógica de ingreso del cliente y añadirlo a la lista interna.)" << endl;

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
    cin.get();
    getline(cin, codigoSucursal);

    Sucursal* sucursal = listaSucursales->buscar(codigoSucursal);

    if (sucursal == nullptr) {
        cout << "\t\tERROR: Sucursal con código " << codigoSucursal << " no encontrada." << endl;
        return;
    }

    ListaColaborador* listaColaboradoresSucursal = sucursal->getColaboradores(); // Acceder a la lista interna

    if (operacion == 1) { // Ingreso
        cout << "\n\t\t>> INGRESANDO COLABORADOR en Sucursal: " << sucursal->getNombre() << endl;
        // Lógica para pedir datos del colaborador y añadirlo a la lista interna
        // Colaborador* nuevoColaborador = leerDatosColaborador();
        // listaColaboradoresSucursal->agregarColaborador(nuevoColaborador);
        cout << "\t\t(PENDIENTE: Lógica de ingreso del colaborador y añadirlo a la lista interna.)" << endl;

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
            // llamar a funcion CrearPlantel();
            break;
        case 2:
            cout << "\n\t\t>> Ejecutando: Visualizacion Grafica de Plantel..." << endl;
            // llamar a funcion VisualizacionPlantel();
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
        cout << "\t\t            SUBMENÚ DE CARROS Y PLANTELES             " << endl;
        cout << "\t\t======================================================" << endl;
        cout << "\t\t(1) Creacion de Solicitud" << endl;
        cout << "\t\t(2) Visualización de solicitudes/contratos por sucursal" << endl;
        cout << "\t\t(3) Visualización de solicitud/contratos especifica" << endl;
        cout << "\t\t(4) Aprobación/rechazo de solicitud" << endl;
        cout << "\t\t(5) Recepción de vehículo en prestado" << endl;
        cout << "\t\t(6) Reporte de contratos para vehículos especifico" << endl;
        cout << "\t\t(0) Regresar al Menú Principal" << endl;
        cout << "\t\t------------------------------------------------------" << endl;

        // 2. Leer la opción (Rango de 0 a 6)
        // Llamada a la función de la misma clase.
        opcionSubmenu = leerOpcion(0, 6);

        // 3. Ejecutar la lógica con switch
        switch (opcionSubmenu) {
        case 1:
            cout << "\n\t\t>> Ejecutando: Creación  de solicitud..." << endl;
            // llamar a funcion CrearSolicitud();
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
            // llamar a funcion ManejoSolicitud();
            break;
        case 5:
            cout << "\n\t\t>> Ejecutando: Recepción de vehículo en prestado ..." << endl;
            // llamar a funcion RecibirVehiPrestado();
            break;
        case 6:
            cout << "\n\t\t>> Ejecutando: Reporte de contratos para vehículos especifico..." << endl;
            // llamar a funcion ReporteContratosVehiEspecifico();
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