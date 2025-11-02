// Utilidades.h
#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <iostream>
#include <string>
#include <sstream>
#include "ListaEnlazada.h"

// Declaraciones Anticipadas
class ListaEnlazada;
class ListaSucursal;
class Sucursal;
class Cliente;
class ClienteFisico;
class ClienteJuridico;
class Colaborador;

using namespace std;

class Utilidades
{
private:
    int op = -1;
    ListaCliente* listaClientes;
    ListaSucursal* listaSucursales;
    ListaColaborador* listaColaboradores;

public:

    Utilidades();
    ~Utilidades();

    void crearPlantelSucursal();
    void visualizarPlantel();


    // M�todo que gestiona el ingreso de un nuevo cliente
    void ingresarCliente();
    void ingresarColaborador();
    Cliente* leerDatosCliente();
    Colaborador* leerDatosColaborador();
    // ====================================================
    // 1. GESTI�N DIRECTA DE SUCURSALES
    // ====================================================
    void ingresarSucursal();
    void eliminarSucursal();
    void mostrarSucursales();

    // ====================================================
    // 2. GESTI�N POR SUCURSAL
    // Se usa un m�todo auxiliar que recibe un entero: 1=Ingreso, 2=Visualizaci�n, 3=Eliminaci�n.
    // ====================================================
    void gestionarClientesPorSucursal(int);
    void gestionarColaboradoresPorSucursal(int);

    // ----------------------------------------------------
    // Funciones de Control de Interfaz y Consola (Instancia)
    // ----------------------------------------------------
    void limpiarConsola();
    int leerOpcion(int min, int max);
    void pausa();

    // ----------------------------------------------------
    // Funciones de Men� (Instancia)
    // ----------------------------------------------------
    void mostrarMenuPrincipal(); //Menu principal

    //Submenus
    void mostrarSubmenuSucursales();
    void mostrarSubmenuColaboradores();
    void mostrarSubmenuCarrosPlanteles();
    void mostrarSubmenuSolicitudesContratos();
    void mostrarSubmenuClientes();
    void ejecutarSistema();

};

#endif