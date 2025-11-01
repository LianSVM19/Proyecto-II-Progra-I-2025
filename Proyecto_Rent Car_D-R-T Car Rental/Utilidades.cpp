// Utilidades.cpp
#include "Utilidades.h"
#include "Sucursal.h"
#include "ListaEnlazada.h"
#include "ClienteFisico.h"
#include "ClienteJuridico.h"

using namespace std;

Utilidades::Utilidades() {
    // Inicializar la lista de clientes
    listaClientes = new ListaCliente();
    // Aquí irían otras inicializaciones de listas (ej. listaSucursales = new ListaSucursal())
}

Utilidades::~Utilidades() {
    // Liberar la memoria de la lista de clientes al cerrar el sistema
    delete listaClientes;
    listaClientes = NULL; // Buenas prácticas
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


/*void Utilidades::mostrarSubmenuSucursales(ListaEnlazada* listaSucursales) {
    int opcion = -1;

    while (opcion != 0) {
        limpiarConsola();
        cout << "\n\t\t======================================================" << endl;
        cout << "\t\t             SUBMENÚ: GESTIÓN DE SUCURSALES           " << endl;
        cout << "\t\t======================================================" << endl;
        cout << "\t\t(1) Ingresar Nueva Sucursal" << endl;
        cout << "\t\t(2) Visualizar Todas las Sucursales" << endl;
        cout << "\t\t(3) Eliminar Sucursal (por Código)" << endl;
        cout << "\t\t(0) Regresar al Menú Principal" << endl;
        cout << "\t\t------------------------------------------------------" << endl;

        opcion = leerOpcion(0, 3);
        }
  */  
//}



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
            // llamarAFuncionIngresoSucursal();
            break;
        case 2:
            cout << "\n\t\t>> Ejecutando: Mostrar Sucursales..." << endl;
            // llamarAFuncionMostrarSucursales();
            break;
        case 3:
            cout << "\n\t\t>> Ejecutando: Eliminar Sucursal..." << endl;
            // llamarAFuncionEliminarSucursal();
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
            // llamar a funcion IncluirColaborador();
            break;
        case 2:
            cout << "\n\t\t>> Ejecutando: Mostrar Colaborador..." << endl;
            // llamar a funcion MostrarColaborador();
            break;
        case 3:
            cout << "\n\t\t>> Ejecutando: Eliminar Colaborador..." << endl;
            // llamar a funcion EliminarColaborador();
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
            this->ingresarCliente();
            break;
        case 2:
            cout << "\n\t\t>> Ejecutando: Mostrar Cliente..." << endl;
            cout << listaClientes->toString() << endl;
            break;
        case 3:
            cout << "\n\t\t>> Ejecutando: Eliminar Cliente..." << endl;
            // llamarAFuncionEliminarCliente();
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