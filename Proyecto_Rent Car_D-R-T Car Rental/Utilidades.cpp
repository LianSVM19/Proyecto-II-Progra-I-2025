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
    if (listaSucursales == nullptr || listaSucursales->estaVacia()) {
        cout << "\n\t\tNo hay sucursales registradas." << endl;
        return nullptr;
    }

    cout << "\n\t\t--- SELECCIONAR SUCURSAL ---" << endl;
    cout << listaSucursales->toString() << endl;
    string codigo;
    cout << "\t\tIngrese codigo de sucursal: ";
    cin >> codigo;
    Sucursal* s = listaSucursales->buscar(codigo);
    if (s == nullptr) {
        cout << "\t\tSucursal no encontrada." << endl;
    }
    return s;
}


void Utilidades::crearPlantelSucursal() {
    string codigoSucursal;
    limpiarConsola();
    cout << "\n\t\t--- CREAR PLANTEL EN SUCURSAL ---" << endl;
    cout << "\t\tIngrese codigo de sucursal: ";
    getline(cin, codigoSucursal);

    Sucursal* suc = listaSucursales->buscar(codigoSucursal);
    if (suc == nullptr) {
        cout << "\t\tERROR: Sucursal no encontrada." << endl;
        pausa();
        return;
    }

    string codigoPlantel, nombrePlantel;
    int filas = 0, columnas = 0;
    cout << "\t\tIngrese codigo interno del plantel (ej: P001): ";
    getline(cin, codigoPlantel);
    cout << "\t\tIngrese nombre del plantel: ";
    getline(cin, nombrePlantel);

    cout << "\t\tIngrese cantidad de filas: ";
    while (!(cin >> filas) || filas <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\t\tEntrada invalida. Ingrese cantidad de filas: ";
    }
    cout << "\t\tIngrese cantidad de columnas: ";
    while (!(cin >> columnas) || columnas <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\t\tEntrada invalida. Ingrese cantidad de columnas: ";
    }
    cin.ignore(10000, '\n'); // limpiar buffer

    // Crear Plantel: asumo que Plantel tiene constructor (codigo/nombre, filas, columnas) o (nombre, filas, columnas)
    Plantel* nuevo = new Plantel(codigoPlantel, nombrePlantel, filas, columnas);
    suc->getListaPlantel()->agregarPlantel(nuevo);

    cout << "\n\t\tPlantel creado con exito. Distribucion de espacios:\n";
    nuevo->mostrarMatriz();
    pausa();
}



Estacionamiento* Utilidades::obtenerRecomendacion(Plantel* plantel) {
    if (plantel == nullptr) return nullptr;

    // Si Plantel tiene un metodo recomendarEspacio() o similar, llamarlo.
    // Si no, implementamos una busqueda simple: primer espacio libre.
    MatrizEstacionamientos* matriz = plantel->getMatrizEstacionamientos();
    if (matriz == nullptr) return nullptr;

    for (int i = 0; i < matriz->getFilas(); ++i) {
        for (int j = 0; j < matriz->getColumnas(); ++j) {
            Estacionamiento* e = matriz->getEstacionamiento(i, j);
            if (e != nullptr && !e->getOcupado()) {
                return e;
            }
        }
    }
    return nullptr;
}




void Utilidades::ingresarVehiculo() {
    limpiarConsola();
    cout << "\n\t\t--- INGRESAR VEHICULO A SUCURSAL ---" << endl;

    Sucursal* suc = seleccionarSucursal();
    if (suc == nullptr) {
        pausa();
        return;
    }

    // Pedir datos del vehiculo
    string placa, marca, modelo, tipoLicencia;
    char categoria;
    cout << "\t\tPlaca: "; getline(cin, placa);
    cout << "\t\tMarca: "; getline(cin, marca);
    cout << "\t\tModelo: "; getline(cin, modelo);
    cout << "\t\tTipo Licencia: "; getline(cin, tipoLicencia);
    cout << "\t\tCategoria (A/B/C/D): "; cin >> categoria; cin.ignore(10000, '\n');

    Vehiculo* v = new Vehiculo(placa, marca, modelo, tipoLicencia, categoria, "Disponible");
    // Inicialmente estado "Disponible" o segun flujo

    // Seleccionar plantel (recomendacion)
    ListaPlantel* lp = suc->getListaPlantel();
    if (lp == nullptr || lp->estaVacia()) {
        cout << "\t\tNo hay planteles en la sucursal. Primero cree uno.\n";
        delete v;
        pausa();
        return;
    }

    // Mostrar planteles brevemente
    cout << "\n\t\tPlanteles disponibles:\n" << lp->toString() << endl;
    cout << "\t\tDesea que el sistema recomiende plantel/espacio? (S/N): ";
    char res; cin >> res; cin.ignore(10000, '\n');

    Plantel* plantelSeleccionado = nullptr;
    Estacionamiento* espacioSeleccionado = nullptr;

    if (res == 'S' || res == 's') {
        // Intentar recomendar a partir de cada plantel: la primer plaza libre
        NodoPlantel* n = lp->getCab();
        while (n != nullptr && espacioSeleccionado == nullptr) {
            Plantel* p = n->getDato();
            espacioSeleccionado = obtenerRecomendacion(p);
            if (espacioSeleccionado != nullptr) {
                plantelSeleccionado = p;
                break;
            }
            n = n->getSiguiente();
        }
        if (espacioSeleccionado == nullptr) {
            cout << "\t\tNo se encontraron espacios libres en ningun plantel.\n";
            delete v;
            pausa();
            return;
        }
        cout << "\t\tRecomendacion: Plantel " << plantelSeleccionado->getCodigoPlantel()
            << " - Espacio " << espacioSeleccionado->getCodigo() << endl;
        cout << "\t\tAceptar recomendacion? (S/N): ";
        char a; cin >> a; cin.ignore(10000, '\n');
        if (a != 'S' && a != 's') {
            espacioSeleccionado = nullptr;
        }
    }

    if (espacioSeleccionado == nullptr) {
        // pedir plantel y espacio directamente
        string codPlantel;
        cout << "\t\tIngrese codigo/nombre de plantel: ";
        getline(cin, codPlantel);
        plantelSeleccionado = lp->buscar(codPlantel);
        if (plantelSeleccionado == nullptr) {
            cout << "\t\tPlantel no encontrado.\n";
            delete v;
            pausa();
            return;
        }
        plantelSeleccionado->mostrarMatriz();
        string codEsp; cout << "\t\tIngrese codigo de espacio (ej: A01): ";
        getline(cin, codEsp);
        MatrizEstacionamientos* m = plantelSeleccionado->getMatrizEstacionamientos();
        if (m == nullptr) {
            cout << "\t\tPlantel no tiene matriz.\n";
            delete v;
            pausa();
            return;
        }
        espacioSeleccionado = m->buscarEstacionamiento(codEsp);
        if (espacioSeleccionado == nullptr || espacioSeleccionado->getOcupado()) {
            cout << "\t\tEspacio invalido o ya ocupado.\n";
            delete v;
            pausa();
            return;
        }
    }

    // Ocupar espacio y registrar vehiculo en lista de sucursal
    espacioSeleccionado->setVehiculo(v);
    espacioSeleccionado->ocupar();

    v->setPlantel(plantelSeleccionado);
    v->setEspacio(espacioSeleccionado);

    // Insertar en la lista de vehiculos de la sucursal (usa el metodo que tu lista define)
    suc->getListaVehiculos()->agregarAlInicio(v);

    cout << "\n\t\tVehiculo ingresado correctamente en espacio " << espacioSeleccionado->getCodigo() << endl;
    pausa();
}

void Utilidades::visualizarPlantel() {
    limpiarConsola();
    cout << "\n\t\t--- VISUALIZAR PLANTEL ---" << endl;
    Sucursal* suc = seleccionarSucursal();
    if (suc == nullptr) {
        pausa();
        return;
    }

    ListaPlantel* lp = suc->getListaPlantel();
    if (lp == nullptr || lp->estaVacia()) {
        cout << "\t\tNo hay planteles en esta sucursal." << endl;
        pausa();
        return;
    }

    cout << lp->toString() << endl;
    string codigoPlantel;
    cout << "\t\tIngrese codigo/nombre del plantel a visualizar: ";
    getline(cin, codigoPlantel);

    Plantel* plantel = lp->buscar(codigoPlantel);
    if (plantel == nullptr) {
        cout << "\t\tPlantel no encontrado." << endl;
        pausa();
        return;
    }

    // Mostrar grafica de matriz
    plantel->mostrarMatriz();

    // Preguntar si desea revisar un espacio por codigo
    cout << "\t\tDesea consultar un espacio especifico? (S/N): ";
    char op; cin >> op; cin.ignore(10000, '\n');
    if (op == 'S' || op == 's') {
        string codEsp;
        cout << "\t\tIngrese codigo de espacio (ej: A01): ";
        getline(cin, codEsp);
        MatrizEstacionamientos* m = plantel->getMatrizEstacionamientos();
        if (m == nullptr) {
            cout << "\t\tError: Plantel sin matriz.\n";
            pausa();
            return;
        }
        Estacionamiento* e = m->buscarEstacionamiento(codEsp);
        if (e == nullptr) {
            cout << "\t\tEspacio no encontrado.\n";
            pausa();
            return;
        }
        cout << e->toString() << endl;
        if (e->getOcupado()) {
            if (e->getVehiculo() != nullptr)
                cout << "\t\tPlaca del vehiculo: " << e->getVehiculo()->getPlaca() << endl;
            else
                cout << "\t\tEspacio marcado ocupado pero vehiculo es NULL.\n";
        }
    }
    pausa();
}


// -----------------------------
// ELIMINAR VEHICULO (interactivo)
// -----------------------------
void Utilidades::EliminarVehiculo() {
    limpiarConsola();
    cout << "\n\t\t======================================================" << endl;
    cout << "\t\t                 ELIMINAR VEHICULO                    " << endl;
    cout << "\t\t======================================================" << endl;

    // 1. Seleccionar sucursal
    Sucursal* sucursalSeleccionada = seleccionarSucursal();
    if (sucursalSeleccionada == nullptr) {
        cout << "\t\tNo se seleccionó ninguna sucursal.\n";
        pausa();
        return;
    }

    // 2. Obtener lista de vehículos
    ListaVehiculo* listaVehiculos = sucursalSeleccionada->getListaVehiculos();
    if (listaVehiculos == nullptr) {
        cout << "\t\tError: La sucursal no tiene lista de vehículos.\n";
        pausa();
        return;
    }

    // 3. Ingresar placa
    string placa;
    cout << "\t\tIngrese la placa del vehículo a eliminar: ";
    getline(cin, placa);

    // 4. Recorremos la lista
    NodoVehiculo* actual = listaVehiculos->getCabeza();
    NodoVehiculo* anterior = nullptr;
    Vehiculo* vehiculo = nullptr;

    while (actual != nullptr) {
        Vehiculo* v = actual->getElemento();
        if (v != nullptr && v->getPlaca() == placa) {
            vehiculo = v;
            break;
        }
        anterior = actual;
        actual = actual->getSig();
    }

    if (vehiculo == nullptr) {
        cout << "\t\tVehículo no encontrado.\n";
        pausa();
        return;
    }

    // 5. Liberar el espacio en el plantel si lo tiene
    Estacionamiento* espacio = vehiculo->getEspacio();
    if (espacio != nullptr) {
        espacio->setVehiculo(nullptr);
        espacio->setOcupado(false);
        cout << "\t\tEspacio " << espacio->getCodigo() << " liberado correctamente.\n";
    }

    // 6. Eliminar el nodo de la lista
    if (anterior == nullptr) {
        // El nodo a eliminar está en la cabeza
        listaVehiculos->setCabeza(actual->getSig());
    }
    else {
        anterior->setSig(actual->getSig());
    }

    delete actual; // Esto elimina también el vehículo, porque el destructor de NodoVehiculo lo borra

    cout << "\t\tVehículo con placa [" << placa << "] eliminado correctamente.\n";
    pausa();
}

// -----------------------------
// REUBICAR VEHICULO DENTRO DE UNA SUCURSAL 
// -----------------------------
void Utilidades::reubicarVehiculoSucursal() {
    limpiarConsola();
    cout << "\n\t\t--- REUBICAR VEHICULO ---" << endl;
    Sucursal* suc = seleccionarSucursal();
    if (suc == nullptr) { pausa(); return; }

    string placa;
    cout << "\t\tIngrese placa del vehiculo a reubicar: ";
    getline(cin, placa);

    Vehiculo* v = suc->getListaVehiculos()->buscar(placa);
    if (v == nullptr) {
        cout << "\t\tVehiculo no encontrado en la sucursal.\n";
        pausa();
        return;
    }

    Plantel* p = v->getPlantel();
    if (p == nullptr) {
        cout << "\t\tVehiculo no tiene plantel asignado.\n";
        pausa();
        return;
    }

    p->mostrarMatriz();
    cout << "\t\tIngrese codigo de nuevo espacio (ej: A01): ";
    string cod; getline(cin, cod);

    MatrizEstacionamientos* m = p->getMatrizEstacionamientos();
    if (m == nullptr) {
        cout << "\t\tError: plantel sin matriz.\n";
        pausa();
        return;
    }
    Estacionamiento* nuevo = m->buscarEstacionamiento(cod);
    if (nuevo == nullptr || nuevo->getOcupado()) {
        cout << "\t\tEspacio invalido o ya ocupado.\n";
        pausa();
        return;
    }

    // Liberar espacio actual
    Estacionamiento* actual = v->getEspacio();
    if (actual != nullptr) {
        actual->desocupar();
        actual->setVehiculo(nullptr);
    }

    // Ocupar el nuevo
    nuevo->setVehiculo(v);
    nuevo->ocupar();
    v->setEspacio(nuevo);

    cout << "\t\tVehiculo reubicado correctamente a " << nuevo->getCodigo() << endl;
    pausa();
}

// -----------------------------
// CAMBIO DE ESTADO DEL VEHICULO 
// -----------------------------
void Utilidades::cambiarEstadoVehiculo() {
    limpiarConsola();
    cout << "\n\t\t======================================================" << endl;
    cout << "\t\t              CAMBIO DE ESTADO DE VEHICULO            " << endl;
    cout << "\t\t======================================================" << endl;

    // 1. Seleccionar sucursal
    Sucursal* suc = seleccionarSucursal();
    if (suc == nullptr) {
        cout << "\t\tNo se seleccionó ninguna sucursal.\n";
        pausa();
        return;
    }

    // 2. Buscar vehículo por placa
    string placa;
    cout << "\t\tIngrese la placa del vehículo: ";
    getline(cin, placa);

    ListaVehiculo* lista = suc->getListaVehiculos();
    if (lista == nullptr) {
        cout << "\t\tLa sucursal no tiene lista de vehículos.\n";
        pausa();
        return;
    }

    Vehiculo* v = lista->buscar(placa);
    if (v == nullptr) {
        cout << "\t\tVehículo no encontrado.\n";
        pausa();
        return;
    }

    // 3. Mostrar estado actual y pedir el nuevo
    cout << "\t\tEstado actual: " << v->getEstado() << endl;

    string nuevoEstado;
    cout << "\t\tIngrese el nuevo estado (Alquilado, Disponible, Lavado, Revision, etc.): ";
    getline(cin, nuevoEstado);

    // 4. Ingresar colaborador responsable
    string colaboradorId;
    cout << "\t\tIngrese la cédula o ID del colaborador que realiza el cambio: ";
    getline(cin, colaboradorId);

    // 5. Llamar directamente al setEstado (usa internamente FechaActual)
    v->setEstado(nuevoEstado, suc->getNombre(), colaboradorId);

    cout << "\n\t\tEl cambio de estado fue procesado correctamente.\n";
    cout << "\t\tVerifique la bitácora del vehículo para confirmar el registro.\n";
    pausa();
}

// -----------------------------
// TRASLADO DE VEHICULOS ENTRE SUCURSALES 
// -----------------------------
void Utilidades::trasladarVehiculos() {
    limpiarConsola();
    cout << "\n\t\t--- TRASLADO DE VEHICULOS ENTRE SUCURSALES (OPCIONAL) ---" << endl;
    cout << "\t\tSucursal origen:\n";
    Sucursal* origen = seleccionarSucursal();
    if (origen == nullptr) { pausa(); return; }

    cout << "\t\tSucursal destino:\n";
    Sucursal* destino = seleccionarSucursal();
    if (destino == nullptr) { pausa(); return; }

    int n;
    cout << "\t\tCantidad de vehiculos a trasladar: ";
    while (!(cin >> n) || n <= 0) {
        cin.clear(); cin.ignore(10000, '\n');
        cout << "\t\tEntrada invalida. Ingrese cantidad: ";
    }
    cin.ignore(10000, '\n');

    ListaVehiculo* lvOrigen = origen->getListaVehiculos();
    if (lvOrigen == nullptr || lvOrigen->estaVacia()) {
        cout << "\t\tNo hay vehiculos en la sucursal origen.\n";
        pausa(); return;
    }

    int trasladados = 0;
    NodoVehiculo* actual = lvOrigen->getCabeza();
    while (actual != nullptr && trasladados < n) {
        Vehiculo* v = actual->getElemento();
        // Solo trasladar si no esta alquilado
        if (v != nullptr && v->getEstado() != "Alquilado" && v->getEstado() != "ALQUILADO") {
            // buscar plantel destino con espacio
            ListaPlantel* lpd = destino->getListaPlantel();
            if (lpd == nullptr || lpd->estaVacia()) { actual = actual->getSig(); continue; }

            NodoPlantel* np = lpd->getCab();
            bool movido = false;
            while (np != nullptr && !movido) {
                Plantel* pd = np->getDato();
                Estacionamiento* rec = obtenerRecomendacion(pd);
                if (rec != nullptr) {
                    // Desocupar de origen
                    Estacionamiento* eo = v->getEspacio();
                    if (eo != nullptr) { eo->desocupar(); eo->setVehiculo(nullptr); }

                    // Ocupar en destino
                    rec->setVehiculo(v);
                    rec->ocupar();
                    v->setPlantel(pd);
                    v->setEspacio(rec);

                    // Mover en listas (agregar a destino y eliminar de origen)
                    destino->getListaVehiculos()->agregarAlInicio(v);
                    lvOrigen->eliminarVehiculo(v->getPlaca()); // usa el metodo que tenga tu ListaVehiculo
                    trasladados++;
                    movido = true;
                }
                np = np->getSiguiente();
            }
        }
        actual = actual->getSig();
    }

    cout << "\t\tTrasladados: " << trasladados << " vehiculos.\n";
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
    codigoSucursalEncontrado = "";
    NodoSucursal* actualSucursal = listaSucursales->getCab();

    while (actualSucursal != nullptr) {
        Sucursal* suc = actualSucursal->getDato();
        if (suc != nullptr) {
            ListaVehiculo* lv = suc->getListaVehiculos();
            if (lv != nullptr) {
                Vehiculo* v = lv->buscar(placa);
                if (v != nullptr) {
                    codigoSucursalEncontrado = suc->getCodigoSucursal();
                    return v;
                }
            }
        }
        actualSucursal = actualSucursal->getSiguiente();
    }
    return nullptr;
}

// ========================================================
// 2. IMPLEMENTACIoN DEL MeTODO DE PRESENTACIoN
//    (Este es el que tenia el error de llamada al 'buscar')
// ========================================================
void Utilidades::mostrarInformacionVehiculoGlobal(string placa) {
    string codigoSuc;
    Vehiculo* v = buscarVehiculoGlobal(placa, codigoSuc);
    if (v == nullptr) {
        cout << "\n\t\tNo se encontro el vehiculo con placa: " << placa << endl;
        return;
    }

    cout << "\n\t\t--- INFORMACION VEHICULO (GLOBAL) ---" << endl;
    cout << v->toString() << endl;
    cout << "\t\tSucursal donde se encontro: " << codigoSuc << endl;

    BitacoraEstado* b = v->getHistorialEstados();
    if (b != nullptr) {
        cout << b->toString() << endl;
    }
    else {
        cout << "\t\tNo hay bitacora registrada para este vehiculo." << endl;
    }
}

// -----------------------------
// CREAR SOLICITUD
// -----------------------------
void Utilidades::CrearSolicitud() {
    limpiarConsola();
    cout << "\n\t\t--- CREAR SOLICITUD DE ALQUILER ---" << endl;

    // Seleccionar sucursal
    Sucursal* suc = seleccionarSucursal();
    if (suc == nullptr) { pausa(); return; }

    // Datos mínimos: cliente (cedula), placa vehiculo, dias, fecha inicio
    string cedulaCliente;
    cout << "\t\tIngrese cedula del cliente: ";
    getline(cin, cedulaCliente);

    Cliente* cliente = suc->getClientes()->buscar(cedulaCliente);
    if (cliente == nullptr) {
        cout << "\t\tCliente no encontrado en la sucursal. Desea registrarlo ahora? (S/N): ";
        char r; cin >> r; cin.ignore(10000, '\n');
        if (r == 'S' || r == 's') {
            Cliente* c = leerDatosCliente();
            if (c != nullptr) {
                suc->getClientes()->agregarCliente(c);
                listaClientes->agregarCliente(c); // tambien global
                cliente = c;
            }
        }
    }

    string placa;
    cout << "\t\tIngrese placa del vehiculo (existente): ";
    getline(cin, placa);

    string codigoSucEncontrado;
    Vehiculo* veh = buscarVehiculoGlobal(placa, codigoSucEncontrado);
    if (veh == nullptr) {
        cout << "\t\tVehiculo no encontrado.\n";
        pausa(); return;
    }
    if (codigoSucEncontrado != suc->getCodigoSucursal()) {
        cout << "\t\tAdvertencia: el vehiculo no esta en la sucursal seleccionada.\n";
    }

    int dias = 0;
    cout << "\t\tIngrese dias de alquiler: ";
    while (!(cin >> dias) || dias <= 0) {
        cin.clear(); cin.ignore(10000, '\n');
        cout << "\t\tEntrada invalida. Ingrese dias: ";
    }
    cin.ignore(10000, '\n');

    string fechaInicio;
    cout << "\t\tIngrese fecha inicio (dd/mm/aaaa): ";
    getline(cin, fechaInicio);

    // Calcular precio diario y total
    double precioDiario = veh->getPrecioDiario();
    double total = precioDiario * dias;

    // Generar codigo de solicitud (ej: S-<sucursal>-<n>) -> simple con timestamp o contador
    string codigoS = "S-" + suc->getCodigoSucursal() + "-" + to_string(rand() % 10000 + 1);

    // Crear objeto SolicitudAlquiler (asumo constructor)
    SolicitudAlquiler* s = new SolicitudAlquiler(codigoS,cliente,nullptr,suc,veh,fechaInicio,"",total,"Pendiente");
    // Ajusta constructor segun tu clase SolicitudAlquiler.

    // Insertar en lista global y en la sucursal (si tienes lista por sucursal)
    listaSolicitudes->agregarSolicitud(s);
    suc->getListaSolicitudes()->agregarSolicitud(s); // si tu Sucursal tiene lista de solicitudes

    cout << "\t\tSolicitud creada con codigo: " << codigoS << endl;
    pausa();
}



// -----------------------------
// VER SOLICITUDES/CONTRATOS (interactivo) - por sucursal
// -----------------------------
void Utilidades::VerSolicitudesContratos() {
    limpiarConsola();
    cout << "\n\t\t--- VER SOLICITUDES / CONTRATOS POR SUCURSAL ---" << endl;
    Sucursal* s = seleccionarSucursal();
    if (s == nullptr) { pausa(); return; }

    // Mostrar solicitudes de la sucursal (si Sucursal tiene lista)
    ListaSolicitud* ls = s->getListaSolicitudes();
    if (ls != nullptr && !ls->estaVacia()) {
        cout << "\t\tSolicitudes en la sucursal:\n" << ls->toString() << endl;
    }
    else {
        cout << "\t\tNo hay solicitudes registradas en esta sucursal.\n";
    }

    // Mostrar contratos de la sucursal (si Sucursal tiene lista contratos)
    ListaContrato* lc = s->getListaContratos();
    if (lc != nullptr && !lc->estaVacia()) {
        cout << "\t\tContratos en la sucursal:\n" << lc->toString() << endl;
    }
    else {
        cout << "\t\tNo hay contratos registrados en esta sucursal.\n";
    }
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
            string ubicacion = "EN_USO_" + solicitud->getCodigoSoli();
            //string fechaActual = obtenerFechaActual();
            vehiculo->setEstado("Alquilado", ubicacion, idColaborador);
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
    string codigoContrato, idColaborador;
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
        cout << "\t\tIngrese el ID del Colaborador que recibe el vehículo: ";
        getline(cin, idColaborador);

        // 1. Finalizar el Contrato
        contrato->setEstado("Finalizado");

        // 2. Obtener Vehiculo y cambiar su estado
        Vehiculo* vehiculo = contrato->getSolicitud()->getVehiculo();
        string ubicacion = "RECEPCION_PENDIENTE_PARKING";
        // Transicion: Alquilado -> Devuelto (segun su logica interna)
        vehiculo->setEstado("Devuelto", ubicacion, idColaborador);

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
            Utilidades::visualizarPlantel();
            break;
        case 3:
            cout << "\n\t\t>> Ejecutando: Ingreso de Vehiculo..." << endl;
            Utilidades::ingresarVehiculo();
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