// Utilidades.h
#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <iostream>
#include <string>
#include <sstream>

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
public:
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
    //void mostrarSubmenuSucursales(ListaEnlazada* listaSucursales);
    void ejecutarSistema();

    // ----------------------------------------------------
    // FUNCIONES CRUD PARA SUCURSALES (Instancia)
    // ----------------------------------------------------
    //void ingresarSucursal(ListaEnlazada* listaSucursales);
    //void visualizarSucursales(ListaEnlazada* listaSucursales);
    //void eliminarSucursal(ListaEnlazada* listaSucursales);


    // ----------------------------------------------------
    // Funciones de Creación de Objetos
    // ----------------------------------------------------
    //Cliente* crearNuevoCliente();
};

#endif