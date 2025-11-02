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


    // Método que gestiona el ingreso de un nuevo cliente
    void ingresarCliente();
    void ingresarColaborador();
    Cliente* leerDatosCliente();
    Colaborador* leerDatosColaborador();
    // ====================================================
    // 1. GESTIÓN DIRECTA DE SUCURSALES
    // ====================================================
    void ingresarSucursal();
    void eliminarSucursal();
    void mostrarSucursales();

    // ====================================================
    // 2. GESTIÓN POR SUCURSAL
    // Se usa un método auxiliar que recibe un entero: 1=Ingreso, 2=Visualización, 3=Eliminación.
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
    // Funciones de Menú (Instancia)
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