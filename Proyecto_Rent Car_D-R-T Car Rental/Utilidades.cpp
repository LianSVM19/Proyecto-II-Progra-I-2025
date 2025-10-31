// Utilidades.cpp
#include "Utilidades.h"
#include "Sucursal.h"
#include "ListaEnlazada.h"
#include "ClienteFisico.h"
#include "ClienteJuridico.h"

using namespace std;

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
            // ... (casos 1 a 4) ...
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
            // llamarAFuncionIngresoCliente();
            break;
        case 2:
            cout << "\n\t\t>> Ejecutando: Mostrar Cliente..." << endl;
            // llamarAFuncionMostrarCliente();
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
