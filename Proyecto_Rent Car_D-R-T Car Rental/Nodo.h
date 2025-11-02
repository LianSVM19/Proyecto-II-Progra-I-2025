#ifndef NODO_H
#define NODO_H

#include <string>
#include "Vehiculo.h" 
#include "Cliente.h"
#include "Colaborador.h"
#include "Sucursal.h"
#include "Plantel.h"
#include "SolicitudAlquiler.h"
#include "ContratoAlquiler.h"

using namespace std;

class NodoVehiculo {
private:
    // Puntero para la asignaci�n din�mica de memoria (requisito del proyecto)
    Vehiculo* elem;
    NodoVehiculo* sig;

public:
    // Constructor
    NodoVehiculo(Vehiculo* , NodoVehiculo* = NULL);

    // Destructor (CR�TICO para liberar la memoria de 'elem')
    ~NodoVehiculo();

    // Setters
    void setElemento(Vehiculo*);
    void setSig(NodoVehiculo*);

    // Getters
    Vehiculo* getElemento(); // Retorna el puntero
    NodoVehiculo* getSig();

    // Funci�n "to string"
    string toStringNodo();
};

class NodoCliente {
private:
    Cliente* dato;
    NodoCliente* siguiente;
public:
    // Constructor (recibe el cliente a almacenar y el puntero al siguiente nodo)
    NodoCliente(Cliente* c, NodoCliente* sig = NULL);

    // Destructor (debe liberar la memoria del cliente almacenado)
    ~NodoCliente();

    // Getters
    Cliente* getDato();
    NodoCliente* getSiguiente();

    // Setters
    void setSiguiente(NodoCliente*);
    void setDato(Cliente*);

    // Funci�n "to string"
    string toStringNodo();
};

class NodoColaborador {
private:
    Colaborador* dato;
    NodoColaborador* siguiente;
public:
    // Constructor (recibe el cliente a almacenar y el puntero al siguiente nodo)
    NodoColaborador(Colaborador* c, NodoColaborador* sig = NULL);

    // Destructor (debe liberar la memoria del cliente almacenado)
    ~NodoColaborador();

    // Getters
    Colaborador* getDato();
    NodoColaborador* getSiguiente();

    // Setters
    void setSiguiente(NodoColaborador*);
    void setDato(Colaborador*);

    // Funci�n "to string"
    string toStringNodo();
};


// =====================================
// DEFINICI�N DE NODOSUCURSAL (NUEVO)
// =====================================
class NodoSucursal {
private:
    Sucursal* dato;
    NodoSucursal* siguiente;
public:
    // Constructor
    NodoSucursal(Sucursal* s, NodoSucursal* sig = NULL);

    // Destructor (debe liberar la memoria de la Sucursal almacenada)
    ~NodoSucursal();

    // Getters
    Sucursal* getDato();
    NodoSucursal* getSiguiente();

    // Setters
    void setSiguiente(NodoSucursal*);
    void setDato(Sucursal*);

    // Funci�n "to string"
    string toStringNodo();
};


// =====================================
// DEFINICI�N DE NODOPLANTEL
// =====================================

class NodoPlantel {
private:
    Plantel* dato;
    NodoPlantel* siguiente;
public:
    // Constructor
    NodoPlantel(Plantel* s, NodoPlantel* sig = NULL);

    // Destructor (debe liberar la memoria del Plantel almacenado)
    ~NodoPlantel();

    // Getters
    Plantel* getDato();
    NodoPlantel* getSiguiente();

    // Setters
    void setSiguiente(NodoPlantel*);
    void setDato(Plantel*);

    // Funci�n "to string"
    string toStringNodo();
};

// =====================================
// DEFINICI�N DE NODOSOLICITUD
// =====================================

class NodoSolicitud {
private:
    SolicitudAlquiler* dato;
    NodoSolicitud* siguiente;
public:
    // Constructor
    NodoSolicitud(SolicitudAlquiler* s, NodoSolicitud* sig = NULL);

    // Destructor (debe liberar la memoria de la Solicitud almacenada)
    ~NodoSolicitud();

    // Getters
    SolicitudAlquiler* getDato();
    NodoSolicitud* getSiguiente();

    // Setters
    void setSiguiente(NodoSolicitud*);
    void setDato(SolicitudAlquiler*);

    // Funci�n "to string"
    string toStringNodo();
};
// =====================================
// DEFINICI�N DE NODOCONTRATO
// =====================================
class NodoContrato {
private:
    ContratoAlquiler* dato;
    NodoContrato* siguiente;
public:
    // Constructor
    NodoContrato(ContratoAlquiler* s, NodoContrato* sig = NULL);

    // Destructor (debe liberar la memoria de la Contrato almacenada)
    ~NodoContrato();

    // Getters
    ContratoAlquiler* getDato();
    NodoContrato* getSiguiente();

    // Setters
    void setSiguiente(NodoContrato*);
    void setDato(ContratoAlquiler*);

    // Funci�n "to string"
    string toStringNodo();
};
#endif