// Utilidades.h
#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <iostream>
#include <string>
#include <sstream>
#include "ListaEnlazada.h"

// Declaraciones Anticipadas
class ListaEnlazada;
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
public:

    Utilidades();
    ~Utilidades();

    // Método que gestiona el ingreso de un nuevo cliente
    void ingresarCliente();

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