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
    cout << "\t\t--- SELECCIoN DE SUCURSAL ---\n";

    // 🔹 Limpia el buffer de entrada antes de leer con getline
    cin.clear();                // limpia errores previos
    cin.ignore(10000, '\n');    // elimina el Enter pendiente del buffer

    cout << "\t\tIngrese codigo de sucursal: ";
    string codigo;
    getline(cin, codigo); // ahora si, leera correctamente

    // 🔹 Buscar la sucursal
    NodoSucursal* actual = listaSucursales->getCab();
    while (actual != NULL) {
        Sucursal* suc = actual->getDato();
        if (suc != NULL && suc->getCodigoSucursal() == codigo) {
            return suc; // 
        }
        actual = actual->getSiguiente();
    }

    cout << "\t\tSucursal no encontrada.\n";
    return NULL;
}

void Utilidades::crearPlantelSucursal() {
    string codigoSucursal;
    limpiarConsola();
    cout << "\n\t\t--- CREAR PLANTEL EN SUCURSAL ---" << endl;
    cout << "\t\tIngrese codigo de sucursal: ";
    getline(cin, codigoSucursal);

    Sucursal* suc = listaSucursales->buscar(codigoSucursal);
    if (suc == NULL) {
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
    if (plantel == NULL) return NULL;

    // Si Plantel tiene un metodo recomendarEspacio() o similar, llamarlo.
    // Si no, implementamos una busqueda simple: primer espacio libre.
    MatrizEstacionamientos* matriz = plantel->getMatrizEstacionamientos();
    if (matriz == NULL) return NULL;

    for (int i = 0; i < matriz->getFilas(); ++i) {
        for (int j = 0; j < matriz->getColumnas(); ++j) {
            Estacionamiento* e = matriz->getEstacionamiento(i, j);
            if (e != NULL && !e->getOcupado()) {
                return e;
            }
        }
    }
    return NULL;
}




void Utilidades::ingresarVehiculo() {
    limpiarConsola();
    cout << "\n\t\t--- INGRESAR VEHICULO A SUCURSAL ---" << endl;

    Sucursal* suc = seleccionarSucursal();
    if (suc == NULL) {
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
    if (lp == NULL || lp->estaVacia()) {
        cout << "\t\tNo hay planteles en la sucursal. Primero cree uno.\n";
        delete v;
        pausa();
        return;
    }

    // Mostrar planteles brevemente
    cout << "\n\t\tPlanteles disponibles:\n" << lp->toString() << endl;
    cout << "\t\tDesea que el sistema recomiende plantel/espacio? (S/N): ";
    char res; cin >> res; cin.ignore(10000, '\n');

    Plantel* plantelSeleccionado = NULL;
    Estacionamiento* espacioSeleccionado = NULL;

    if (res == 'S' || res == 's') {
        // Intentar recomendar a partir de cada plantel: la primer plaza libre
        NodoPlantel* n = lp->getCab();
        while (n != NULL && espacioSeleccionado == NULL) {
            Plantel* p = n->getDato();
            espacioSeleccionado = obtenerRecomendacion(p);
            if (espacioSeleccionado != NULL) {
                plantelSeleccionado = p;
                break;
            }
            n = n->getSiguiente();
        }
        if (espacioSeleccionado == NULL) {
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
            espacioSeleccionado = NULL;
        }
    }

    if (espacioSeleccionado == NULL) {
        // pedir plantel y espacio directamente
        string codPlantel;
        cout << "\t\tIngrese codigo/nombre de plantel: ";
        getline(cin, codPlantel);
        plantelSeleccionado = lp->buscar(codPlantel);
        if (plantelSeleccionado == NULL) {
            cout << "\t\tPlantel no encontrado.\n";
            delete v;
            pausa();
            return;
        }
        plantelSeleccionado->mostrarMatriz();
        string codEsp; cout << "\t\tIngrese codigo de espacio (ej: A01): ";
        getline(cin, codEsp);
        MatrizEstacionamientos* m = plantelSeleccionado->getMatrizEstacionamientos();
        if (m == NULL) {
            cout << "\t\tPlantel no tiene matriz.\n";
            delete v;
            pausa();
            return;
        }
        espacioSeleccionado = m->buscarEstacionamiento(codEsp);
        if (espacioSeleccionado == NULL || espacioSeleccionado->getOcupado()) {
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
    cout << "\n\t\t===============================================" << endl;
    cout << "\t\t     VISUALIZACIoN DE PLANTEL DE ESTACIONAMIENTO" << endl;
    cout << "\t\t===============================================" << endl;

    // 1️ Seleccionar sucursal
    Sucursal* suc = seleccionarSucursal();
    if (suc == NULL) {
        pausa();
        return;
    }

    // 2️⃣ Obtener la lista de planteles
    ListaPlantel* listaPlanteles = suc->getListaPlantel();
    if (listaPlanteles == NULL || listaPlanteles->estaVacia()) {
        cout << "\n\t\tLa sucursal no tiene planteles registrados.\n";
        pausa();
        return;
    }

    // 3️⃣ Mostrar planteles disponibles
    cout << "\n\t\t--- PLANTELES DISPONIBLES EN LA SUCURSAL ---\n";
    NodoPlantel* actual = listaPlanteles->getCab();
    while (actual != NULL) {
        Plantel* p = actual->getDato();
        if (p != NULL) {
            cout << "\t\tCodigo: " << p->getCodigoPlantel()
                << " | Tipo: " << p->getTipoPlantel()
                << " | Tamaño: " << p->getCapacidadFilas()
                << "x" << p->getCapacidadColumnas() << endl;
        }
        actual = actual->getSiguiente();
    }

    // 4️⃣ Elegir el plantel
    string codPlantel;
    cout << "\n\t\tIngrese el codigo del plantel que desea visualizar: ";
    getline(cin, codPlantel);

    Plantel* plantel = listaPlanteles->buscar(codPlantel);
    if (plantel == NULL) {
        cout << "\t\tPlantel no encontrado.\n";
        pausa();
        return;
    }

    // 5️⃣ Mostrar la matriz de estacionamientos
    MatrizEstacionamientos* matriz = plantel->getMatrizEstacionamientos();
    if (matriz == NULL) {
        cout << "\t\tERROR: El plantel no tiene matriz inicializada.\n";
        pausa();
        return;
    }

    cout << "\n\t\t--- DISTRIBUCIoN DEL PLANTEL " << codPlantel << " ---\n";
    cout << "\t\tLeyenda: [D]=Disponible | [O]=Ocupado\n\n";

    for (int i = 0; i < plantel->getCapacidadFilas(); ++i) {
        cout << "\t\t";
        for (int j = 0; j < plantel->getCapacidadColumnas(); ++j) {
            Estacionamiento* e = matriz->getEstacionamiento(i, j);
            if (e != NULL)
                cout << "[" << (e->getOcupado() ? "O" : "D") << "] ";
        }
        cout << endl;
    }

    // 6️⃣ Calcular porcentaje de ocupacion
    int total = plantel->getTotalEspacios();
    int ocupados = plantel->getOcupados();
    double porcentaje = 0.0;

    if (total > 0) {
        porcentaje = (ocupados * 100.0) / total;
    }
    else {
        porcentaje = 0.0;
    }

    cout << "\n\t\tTotal de espacios: " << total
        << " | Ocupados: " << ocupados
        << " | Porcentaje de ocupación: " << porcentaje << "%" << endl;

    // 7️⃣ Consultar espacio especifico
    char opcion;
    cout << "\n\t\t¿Desea consultar un espacio especifico? (S/N): ";
    cin >> opcion;
    cin.ignore(); // este si es seguro y basico

    if (opcion == 'S' || opcion == 's') {
        string codEspacio;
        cout << "\t\tIngrese el codigo del espacio (ej: A01): ";
        getline(cin, codEspacio);

        Estacionamiento* espacio = matriz->buscarEstacionamiento(codEspacio);
        if (espacio == NULL) {
            cout << "\t\tEl codigo ingresado no existe.\n";
        }
        else if (!espacio->getOcupado()) {
            cout << "\t\tEl espacio " << codEspacio << " esta disponible.\n";
        }
        else if (espacio->getVehiculo() != NULL) {
            cout << "\t\tEl espacio " << codEspacio
                << " esta ocupado por el vehiculo con placa: "
                << espacio->getVehiculo()->getPlaca() << endl;
        }
        else {
            cout << "\t\tEl espacio figura como ocupado pero sin vehiculo asignado.\n";
        }
    }

    pausa();
}

// -----------------------------
// ELIMINAR VEHICULO 
// -----------------------------
void Utilidades::EliminarVehiculo() {
    limpiarConsola();
    cout << "\n\t\t======================================================" << endl;
    cout << "\t\t                 ELIMINAR VEHICULO                    " << endl;
    cout << "\t\t======================================================" << endl;

    // 1. Seleccionar sucursal
    Sucursal* sucursalSeleccionada = seleccionarSucursal();
    if (sucursalSeleccionada == NULL) {
        cout << "\t\tNo se selecciono ninguna sucursal.\n";
        pausa();
        return;
    }

    // 2. Obtener lista de vehiculos
    ListaVehiculo* listaVehiculos = sucursalSeleccionada->getListaVehiculos();
    if (listaVehiculos == NULL) {
        cout << "\t\tError: La sucursal no tiene lista de vehiculos.\n";
        pausa();
        return;
    }

    // 3. Ingresar placa
    string placa;
    cout << "\t\tIngrese la placa del vehiculo a eliminar: ";
    getline(cin, placa);

    // 4. Recorremos la lista
    NodoVehiculo* actual = listaVehiculos->getCabeza();
    NodoVehiculo* anterior = NULL;
    Vehiculo* vehiculo = NULL;

    while (actual != NULL) {
        Vehiculo* v = actual->getElemento();
        if (v != NULL && v->getPlaca() == placa) {
            vehiculo = v;
            break;
        }
        anterior = actual;
        actual = actual->getSig();
    }

    if (vehiculo == NULL) {
        cout << "\t\tVehiculo no encontrado.\n";
        pausa();
        return;
    }

    // 5. Liberar el espacio en el plantel si lo tiene
    Estacionamiento* espacio = vehiculo->getEspacio();
    if (espacio != NULL) {
        espacio->setVehiculo(NULL);
        espacio->setOcupado(false);
        cout << "\t\tEspacio " << espacio->getCodigo() << " liberado correctamente.\n";
    }

    // 6. Eliminar el nodo de la lista
    if (anterior == NULL) {
        // El nodo a eliminar esta en la cabeza
        listaVehiculos->setCabeza(actual->getSig());
    }
    else {
        anterior->setSig(actual->getSig());
    }

    delete actual; // Esto elimina tambien el vehiculo, porque el destructor de NodoVehiculo lo borra

    cout << "\t\tVehiculo con placa [" << placa << "] eliminado correctamente.\n";
    pausa();
}

// -----------------------------
// REUBICAR VEHICULO DENTRO DE UNA SUCURSAL 
// -----------------------------
void Utilidades::reubicarVehiculoSucursal() {
    limpiarConsola();
    cout << "\n\t\t--- REUBICAR VEHICULO ---" << endl;
    Sucursal* suc = seleccionarSucursal();
    if (suc == NULL) { pausa(); return; }

    string placa;
    cout << "\t\tIngrese placa del vehiculo a reubicar: ";
    getline(cin, placa);

    Vehiculo* v = suc->getListaVehiculos()->buscar(placa);
    if (v == NULL) {
        cout << "\t\tVehiculo no encontrado en la sucursal.\n";
        pausa();
        return;
    }

    Plantel* p = v->getPlantel();
    if (p == NULL) {
        cout << "\t\tVehiculo no tiene plantel asignado.\n";
        pausa();
        return;
    }

    p->mostrarMatriz();
    cout << "\t\tIngrese codigo de nuevo espacio (ej: A01): ";
    string cod; getline(cin, cod);

    MatrizEstacionamientos* m = p->getMatrizEstacionamientos();
    if (m == NULL) {
        cout << "\t\tError: plantel sin matriz.\n";
        pausa();
        return;
    }
    Estacionamiento* nuevo = m->buscarEstacionamiento(cod);
    if (nuevo == NULL || nuevo->getOcupado()) {
        cout << "\t\tEspacio invalido o ya ocupado.\n";
        pausa();
        return;
    }

    // Liberar espacio actual
    Estacionamiento* actual = v->getEspacio();
    if (actual != NULL) {
        actual->desocupar();
        actual->setVehiculo(NULL);
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
    if (suc == NULL) {
        cout << "\t\tNo se selecciono ninguna sucursal.\n";
        pausa();
        return;
    }

    // 2. Buscar vehiculo por placa
    string placa;
    cout << "\t\tIngrese la placa del vehiculo: ";
    getline(cin, placa);

    ListaVehiculo* lista = suc->getListaVehiculos();
    if (lista == NULL) {
        cout << "\t\tLa sucursal no tiene lista de vehiculos.\n";
        pausa();
        return;
    }

    Vehiculo* v = lista->buscar(placa);
    if (v == NULL) {
        cout << "\t\tVehiculo no encontrado.\n";
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
    cout << "\t\tIngrese la cedula o ID del colaborador que realiza el cambio: ";
    getline(cin, colaboradorId);

    // 5. Llamar directamente al setEstado (usa internamente FechaActual)
    v->setEstado(nuevoEstado, suc->getNombre(), colaboradorId);

    cout << "\n\t\tEl cambio de estado fue procesado correctamente.\n";
    cout << "\t\tVerifique la bitacora del vehiculo para confirmar el registro.\n";
    pausa();
}

// -----------------------------
// TRASLADO DE VEHICULOS ENTRE SUCURSALES 
// -----------------------------
void Utilidades::trasladarVehiculos() {
    limpiarConsola();
    cout << "\n\t\t--- TRASLADO DE VEHICULOS ENTRE SUCURSALES ---" << endl;

    // 1️⃣ Seleccionar sucursal origen
    cout << "\t\tSucursal origen:\n";
    Sucursal* origen = seleccionarSucursal();
    if (origen == NULL) { pausa(); return; }

    // 2️⃣ Seleccionar sucursal destino
    cout << "\t\tSucursal destino:\n";
    Sucursal* destino = seleccionarSucursal();
    if (destino == NULL) { pausa(); return; }

    // 3️⃣ Seleccionar PLANTEL ORIGEN dentro de la sucursal origen
    ListaPlantel* listaOrigen = origen->getListaPlantel();
    if (listaOrigen == NULL || listaOrigen->estaVacia()) {
        cout << "\t\tLa sucursal origen no tiene planteles registrados.\n";
        pausa();
        return;
    }

    cout << "\n\t\t--- PLANTELES EN SUCURSAL ORIGEN ---\n";
    NodoPlantel* nodoO = listaOrigen->getCab();
    while (nodoO != NULL) {
        Plantel* p = nodoO->getDato();
        cout << "\t\t- " << p->getCodigoPlantel() << " (" << p->getTipoPlantel() << ")\n";
        nodoO = nodoO->getSiguiente();
    }

    string codPlantelOrigen;
    cout << "\t\tIngrese el código del plantel ORIGEN: ";
    getline(cin, codPlantelOrigen);

    Plantel* plantelOrigen = listaOrigen->buscar(codPlantelOrigen);
    if (plantelOrigen == NULL) {
        cout << "\t\tPlantel origen no encontrado.\n";
        pausa();
        return;
    }

    // 4️⃣ Seleccionar PLANTEL DESTINO dentro de la sucursal destino
    ListaPlantel* listaDestino = destino->getListaPlantel();
    if (listaDestino == NULL || listaDestino->estaVacia()) {
        cout << "\t\tLa sucursal destino no tiene planteles registrados.\n";
        pausa();
        return;
    }

    cout << "\n\t\t--- PLANTELES EN SUCURSAL DESTINO ---\n";
    NodoPlantel* nodoD = listaDestino->getCab();
    while (nodoD != NULL) {
        Plantel* p = nodoD->getDato();
        cout << "\t\t- " << p->getCodigoPlantel() << " (" << p->getTipoPlantel() << ")\n";
        nodoD = nodoD->getSiguiente();
    }

    string codPlantelDestino;
    cout << "\t\tIngrese el código del plantel DESTINO: ";
    getline(cin, codPlantelDestino);

    Plantel* plantelDestino = listaDestino->buscar(codPlantelDestino);
    if (plantelDestino == NULL) {
        cout << "\t\tPlantel destino no encontrado.\n";
        pausa();
        return;
    }

    // 5️⃣ Seleccionar vehículo a trasladar
    ListaVehiculo* lvOrigen = origen->getListaVehiculos();
    if (lvOrigen == NULL || lvOrigen->estaVacia()) {
        cout << "\t\tNo hay vehículos en la sucursal origen.\n";
        pausa();
        return;
    }

    string placa;
    cout << "\n\t\tIngrese la placa del vehículo a trasladar: ";
    getline(cin, placa);

    Vehiculo* v = lvOrigen->buscar(placa);
    if (v == NULL) {
        cout << "\t\tVehículo no encontrado en la sucursal origen.\n";
        pausa();
        return;
    }

    // 6️⃣ Buscar un espacio disponible en el plantel destino
    Estacionamiento* rec = obtenerRecomendacion(plantelDestino);
    if (rec == NULL) {
        cout << "\t\tNo hay espacios disponibles en el plantel destino.\n";
        pausa();
        return;
    }

    // 7️⃣ Realizar traslado
    Estacionamiento* eo = v->getEspacio();
    if (eo != NULL) {
        eo->desocupar();
        eo->setVehiculo(NULL);
    }

    rec->setVehiculo(v);
    rec->ocupar();
    v->setPlantel(plantelDestino);
    v->setEspacio(rec);

    // 8️⃣ Mover vehículo entre listas
    destino->getListaVehiculos()->agregarAlInicio(v);
    lvOrigen->eliminarVehiculo(v->getPlaca());

    cout << "\n\t\tVehículo trasladado con éxito de " << origen->getNombre()
        << " (" << plantelOrigen->getCodigoPlantel() << ") a "
        << destino->getNombre() << " (" << plantelDestino->getCodigoPlantel() << ")\n";
    cout << "\t\tEspacio asignado: " << rec->getCodigo() << endl;

    pausa();
}

void Utilidades::reporteContratosPorVehiculo() {
    cout << "\n--- REPORTE DE CONTRATOS DE UN VEHICULO ESPECIFICO ---\n";

    string placa;
    cout << "Ingrese la placa del vehiculo: ";
    getline(cin, placa);

    bool encontrado = false;

    NodoContrato* actual = listaContratos->getCab();
    while (actual != NULL) {
        ContratoAlquiler* c = actual->getDato(); 
        SolicitudAlquiler* s = c->getSolicitud();
        if (s != NULL && s->getVehiculo() != NULL && s->getVehiculo()->getPlaca() == placa) {
            encontrado = true;
            cout << "\nContrato ID: " << c->getCodigoContrato() << endl;
            cout << "Cliente: " << s->getCliente()->getNombre() << endl;
            cout << "Dias de alquiler: " << s->getCanDiasAlqui() << endl;
            cout << "Fecha inicio: " << s->getFechIni() << endl;
            cout << "Fecha fin: " << s->getFechFin() << endl;
            cout << "Estado: " << c->getEstado() << endl;
            cout << "Precio total: " << c->getCostoTotal() << endl;
        }
        actual = actual->getSiguiente();
    }

    if (!encontrado) {
        cout << "No existen contratos asociados a esa placa.\n";
    }
}

void Utilidades::reporteHistorialCliente() {
    limpiarConsola();
    cout << "\n\t\t==============================================" << endl;
    cout << "\t\t        HISTORIAL COMPLETO DEL CLIENTE        " << endl;
    cout << "\t\t==============================================\n";

    string id;
    cout << "\t\tIngrese la cedula del cliente: ";
    getline(cin, id);

    bool encontrado = false;

    // 🔹 Mostrar todas las solicitudes del cliente
    cout << "\n\t\t--- SOLICITUDES DE ALQUILER ---" << endl;
    NodoSolicitud* sol = listaSolicitudes->getCab();
    int contadorSolicitudes = 0;

    while (sol != NULL) {
        SolicitudAlquiler* s = sol->getDato();
        if (s != NULL && s->getCliente() != NULL &&
            s->getCliente()->getCedula() == id) {

            encontrado = true;
            contadorSolicitudes++;

            cout << "\t\tSolicitud #" << contadorSolicitudes << endl;
            cout << "\t\t  Codigo: " << s->getCodigoSoli() << endl;
            cout << "\t\t  Vehiculo: "
                << (s->getVehiculo() ? s->getVehiculo()->getPlaca() : "N/A") << endl;
            cout << "\t\t  Estado: " << s->getEstado() << endl;
            cout << "\t\t----------------------------------------" << endl;
        }
        sol = sol->getSiguiente();
    }

    if (contadorSolicitudes == 0)
        cout << "\t\t(No hay solicitudes registradas)\n";

    // 🔹 Mostrar todos los contratos del cliente
    cout << "\n\t\t--- CONTRATOS DE ALQUILER ---" << endl;
    NodoContrato* con = listaContratos->getCab();
    int contadorContratos = 0;

    while (con != NULL) {
        ContratoAlquiler* c = con->getDato();
        if (c != NULL && c->getSolicitud() != NULL) {
            SolicitudAlquiler* s = c->getSolicitud();
            if (s->getCliente() != NULL && s->getCliente()->getCedula() == id) {

                encontrado = true;
                contadorContratos++;

                cout << "\t\tContrato #" << contadorContratos << endl;
                cout << "\t\t  Codigo: " << c->getCodigoContrato() << endl;
                cout << "\t\t  Vehiculo: "
                    << (s->getVehiculo() ? s->getVehiculo()->getPlaca() : "N/A") << endl;
                cout << "\t\t  Estado: " << c->getEstado() << endl;
                cout << "\t\t----------------------------------------" << endl;
            }
        }
        con = con->getSiguiente();
    }

    if (contadorContratos == 0)
        cout << "\t\t(No hay contratos registrados)\n";

    if (!encontrado) {
        cout << "\n\t\tEl cliente no tiene solicitudes ni contratos registrados.\n";
    }

    cout << "\n\t\t==============================================\n";
    pausa();
}

void Utilidades::reporteClientesPorContratos() {
    limpiarConsola();
    cout << "\n\t\t===============================================" << endl;
    cout << "\t\tREPORTE DE CLIENTES POR CANTIDAD DE CONTRATOS" << endl;
    cout << "\t\t===============================================\n";

    if (listaClientes == NULL || listaClientes->estaVacia()) {
        cout << "\t\tNo hay clientes registrados.\n";
        pausa();
        return;
    }

    // 1️⃣ Estructuras paralelas simples (max 100 clientes)
    const int MAX = 100;
    Cliente* clientes[MAX];
    int cantidades[MAX];
    string codigos[MAX];
    int totalClientes = 0;

    // 2️⃣ Recorremos todos los clientes
    NodoCliente* nodoC = listaClientes->getCab();
    while (nodoC != NULL && totalClientes < MAX) {
        Cliente* cli = nodoC->getDato();
        int cantidadContratos = 0;
        string listaCodigos = "";

        // Recorremos todos los contratos
        NodoContrato* nodoCon = listaContratos->getCab();
        while (nodoCon != NULL) {
            ContratoAlquiler* contrato = nodoCon->getDato();
            if (contrato != NULL && contrato->getSolicitud() != NULL) {
                SolicitudAlquiler* soli = contrato->getSolicitud();
                if (soli != NULL && soli->getCliente() != NULL &&
                    soli->getCliente()->getCedula() == cli->getCedula()) {
                    cantidadContratos++;
                    listaCodigos += contrato->getCodigoContrato() + " ";
                }
            }
            nodoCon = nodoCon->getSiguiente();
        }

        clientes[totalClientes] = cli;
        cantidades[totalClientes] = cantidadContratos;
        codigos[totalClientes] = listaCodigos;
        totalClientes++;

        nodoC = nodoC->getSiguiente();
    }

    // 3️⃣ Ordenamiento burbuja (descendente por cantidad)
    for (int i = 0; i < totalClientes - 1; i++) {
        for (int j = 0; j < totalClientes - i - 1; j++) {
            if (cantidades[j] < cantidades[j + 1]) {
                // intercambiar posiciones
                Cliente* tempC = clientes[j];
                clientes[j] = clientes[j + 1];
                clientes[j + 1] = tempC;

                int tempCant = cantidades[j];
                cantidades[j] = cantidades[j + 1];
                cantidades[j + 1] = tempCant;

                string tempCod = codigos[j];
                codigos[j] = codigos[j + 1];
                codigos[j + 1] = tempCod;
            }
        }
    }

    // 4️⃣ Mostrar resultados
    int sinContratos = 0;
    for (int i = 0; i < totalClientes; i++) {
        if (cantidades[i] == 0) {
            sinContratos++;
            continue;
        }

        cout << "\n\t\tCliente: " << clientes[i]->getNombre()
            << " (" << clientes[i]->getCedula() << ")" << endl;
        cout << "\t\tContratos realizados: " << cantidades[i] << endl;
        cout << "\t\tCodigos de contratos: " << codigos[i] << endl;
        cout << "\t\t---------------------------------------------" << endl;
    }

    cout << "\n\t\t===============================================" << endl;
    cout << "\t\tTotal clientes: " << totalClientes << endl;
    cout << "\t\tClientes sin contratos: " << sinContratos << endl;
    cout << "\t\t===============================================" << endl;

    pausa();
}

void Utilidades::reporteAlquileresPorColaborador() {
    limpiarConsola();
    cout << "\n\t\t===============================================" << endl;
    cout << "\t\tREPORTE DE ALQUILERES POR COLABORADOR" << endl;
    cout << "\t\t===============================================" << endl;

    if (listaColaboradores == NULL || listaColaboradores->estaVacia()) {
        cout << "\t\tNo hay colaboradores registrados.\n";
        pausa();
        return;
    }

    string idCol;
    cout << "\t\tIngrese el ID (cedula) del colaborador: ";
    getline(cin, idCol);

    Colaborador* colaboradorEncontrado = NULL;

    // Buscar colaborador
    NodoColaborador* nodoC = listaColaboradores->getCab();
    while (nodoC != NULL) {
        Colaborador* col = nodoC->getDato();
        if (col != NULL && col->getCedula() == idCol) {
            colaboradorEncontrado = col;
            break;
        }
        nodoC = nodoC->getSiguiente();
    }

    if (colaboradorEncontrado == NULL) {
        cout << "\t\tColaborador no encontrado.\n";
        pausa();
        return;
    }

    cout << "\n\t\tColaborador: " << colaboradorEncontrado->getNombre()
        << " (" << colaboradorEncontrado->getCedula() << ")" << endl;
    cout << "\t\t-----------------------------------------------" << endl;

    bool tieneContratos = false;
    int contadorContratos = 0;

    // Recorremos todos los contratos para buscar los asociados al colaborador
    NodoContrato* nodoCon = listaContratos->getCab();
    while (nodoCon != NULL) {
        ContratoAlquiler* contrato = nodoCon->getDato();

        if (contrato != NULL && contrato->getSolicitud() != NULL) {
            SolicitudAlquiler* soli = contrato->getSolicitud();

            if (soli != NULL && soli->getColaborador() != NULL &&
                soli->getColaborador()->getCedula() == idCol) {

                tieneContratos = true;
                contadorContratos++;

                Cliente* cli = soli->getCliente();
                Vehiculo* veh = soli->getVehiculo();

                cout << "\n\t\tContrato: " << contrato->getCodigoContrato() << endl;

                if (veh != NULL) {
                    cout << "\t\tVehiculo: " << veh->getPlaca() << endl;
                }
                else {
                    cout << "\t\tVehiculo: N/A" << endl;
                }

                if (cli != NULL) {
                    cout << "\t\tCliente ID: " << cli->getCedula() << endl;
                }
                else {
                    cout << "\t\tCliente ID: N/A" << endl;
                }

                cout << "\t\t-----------------------------------------------" << endl;
            }
        }

        nodoCon = nodoCon->getSiguiente();
    }

    if (!tieneContratos) {
        cout << "\n\t\tEl colaborador no tiene alquileres registrados.\n";
    }
    else {
        cout << "\n\t\tTotal de alquileres realizados por este colaborador: "
            << contadorContratos << endl;
    }

    cout << "\t\t===============================================" << endl;
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

    while (actualSucursal != NULL) {
        Sucursal* suc = actualSucursal->getDato();
        if (suc != NULL) {
            ListaVehiculo* lv = suc->getListaVehiculos();
            if (lv != NULL) {
                Vehiculo* v = lv->buscar(placa);
                if (v != NULL) {
                    codigoSucursalEncontrado = suc->getCodigoSucursal();
                    return v;
                }
            }
        }
        actualSucursal = actualSucursal->getSiguiente();
    }
    return NULL;
}

// ========================================================
// 2. IMPLEMENTACIoN DEL MeTODO DE PRESENTACIoN
//    (Este es el que tenia el error de llamada al 'buscar')
// ========================================================
void Utilidades::mostrarInformacionVehiculoGlobal(string placa) {
    string codigoSuc;
    Vehiculo* v = buscarVehiculoGlobal(placa, codigoSuc);
    if (v == NULL) {
        cout << "\n\t\tNo se encontro el vehiculo con placa: " << placa << endl;
        return;
    }

    cout << "\n\t\t--- INFORMACION VEHICULO (GLOBAL) ---" << endl;
    cout << v->toString() << endl;
    cout << "\t\tSucursal donde se encontro: " << codigoSuc << endl;

    BitacoraEstado* b = v->getHistorialEstados();
    if (b != NULL) {
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
    if (suc == NULL) { pausa(); return; }

    // Datos minimos: cliente (cedula), placa vehiculo, dias, fecha inicio
    string cedulaCliente;
    cout << "\t\tIngrese cedula del cliente: ";
    getline(cin, cedulaCliente);

    Cliente* cliente = suc->getClientes()->buscar(cedulaCliente);
    if (cliente == NULL) {
        cout << "\t\tCliente no encontrado en la sucursal. Desea registrarlo ahora? (S/N): ";
        char r; cin >> r; cin.ignore(10000, '\n');
        if (r == 'S' || r == 's') {
            Cliente* c = leerDatosCliente();
            if (c != NULL) {
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
    if (veh == NULL) {
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
    SolicitudAlquiler* s = new SolicitudAlquiler(codigoS,cliente,NULL,suc,veh,fechaInicio,"",total,"Pendiente");
    // Ajusta constructor segun tu clase SolicitudAlquiler.

    // Insertar en lista global y en la sucursal (si tienes lista por sucursal)
    listaSolicitudes->agregarSolicitud(s);
    suc->getListaSolicitudes()->agregarSolicitud(s); // si tu Sucursal tiene lista de solicitudes

    cout << "\t\tSolicitud creada con codigo: " << codigoS << endl;
    pausa();
}



// -----------------------------
// VER SOLICITUDES/CONTRATOS 
// -----------------------------
void Utilidades::VerSolicitudesContratos() {
    limpiarConsola();
    cout << "\n\t\t--- VER SOLICITUDES / CONTRATOS POR SUCURSAL ---" << endl;
    Sucursal* s = seleccionarSucursal();
    if (s == NULL) { pausa(); return; }

    // Mostrar solicitudes de la sucursal (si Sucursal tiene lista)
    ListaSolicitud* ls = s->getListaSolicitudes();
    if (ls != NULL && !ls->estaVacia()) {
        cout << "\t\tSolicitudes en la sucursal:\n" << ls->toString() << endl;
    }
    else {
        cout << "\t\tNo hay solicitudes registradas en esta sucursal.\n";
    }

    // Mostrar contratos de la sucursal (si Sucursal tiene lista contratos)
    ListaContrato* lc = s->getListaContratos();
    if (lc != NULL && !lc->estaVacia()) {
        cout << "\t\tContratos en la sucursal:\n" << lc->toString() << endl;
    }
    else {
        cout << "\t\tNo hay contratos registrados en esta sucursal.\n";
    }
    pausa();
}





//jaja
// -----------------------------
// APROBAR / RECHAZAR SOLICITUD
// -----------------------------
void Utilidades::AprobarRechazarSolicitud() {
    limpiarConsola();
    cout << "\n\t\t--- APROBAR / RECHAZAR SOLICITUD ---" << endl;
    string codigoS;
    cout << "\t\tIngrese codigo de la solicitud: ";
    getline(cin, codigoS);

    SolicitudAlquiler* s = listaSolicitudes->buscar(codigoS);
    if (s == NULL) {
        cout << "\t\tSolicitud no encontrada.\n";
        pausa(); return;
    }

    cout << s->toString() << endl;
    cout << "\t\tAprobar (A) / Rechazar (R) / Cancelar (C): ";
    char op; cin >> op; cin.ignore(10000, '\n');

    if (op == 'A' || op == 'a') {
        s->setEstado("Aprobada");
        // Crear contrato a partir de solicitud (asumir constructor)
        string codigoContrato = "C-" + s->getCodigoSoli() + "-" + to_string(rand() % 10000 + 1);
        ContratoAlquiler* c = new ContratoAlquiler(codigoContrato, s->getPrecioTotal(),"Activo",s);
        listaContratos->agregarContrato(c);
        Sucursal* su = s->getSucursal();
        if (su != NULL && su->getListaContratos() != NULL) su->getListaContratos()->agregarContrato(c);

        cout << "\t\tSolicitud aprobada. Contrato creado con codigo: " << codigoContrato << endl;
    }
    else if (op == 'R' || op == 'r') {
        s->setEstado("Rechazada");
        cout << "\t\tSolicitud rechazada.\n";
    }
    else {
        cout << "\t\tOperacion cancelada.\n";
    }
    pausa();
}




// -----------------------------
// RECEPCION DE VEHICULO Y FINALIZAR CONTRATO 
// -----------------------------
void Utilidades::RecepcionVehiculo() {
    limpiarConsola();
    cout << "\n\t\t--- RECEPCION Y FINALIZACION DE CONTRATO ---" << endl;
    cout << "\t\tIngrese codigo del contrato a finalizar: ";
    string codigoContrato; getline(cin, codigoContrato);

    ContratoAlquiler* contrato = listaContratos->buscar(codigoContrato);
    if (contrato == NULL) {
        cout << "\t\tContrato no encontrado.\n";
        pausa(); return;
    }

    if (contrato->getEstado() == "Finalizado") {
        cout << "\t\tContrato ya finalizado.\n";
        pausa(); return;
    }

    if (contrato->getEstado() != "Activo") {
        cout << "\t\tContrato no se encuentra en estado Activo.\n";
        pausa(); return;
    }

    // Cambiar estado del contrato y del vehiculo
    contrato->setEstado("Finalizado");

    SolicitudAlquiler* soli = contrato->getSolicitud();
    if (soli == NULL) {
        cout << "\t\tSolicitud asociada no encontrada. Finalizando contrato de todas formas.\n";
        pausa(); return;
    }

    Vehiculo* veh = soli->getVehiculo();
    if (veh == NULL) {
        cout << "\t\tVehiculo asociado no encontrado.\n";
        pausa(); return;
    }

    // Cambiar estado del vehiculo: Alquilado -> Devuelto
    veh->setEstado("Devuelto", "Recepcion", "Sistema");

    // Liberar espacio en plantel
    Estacionamiento* e = veh->getEspacio();
    if (e != NULL) {
        e->desocupar();
        e->setVehiculo(NULL);
    }

    cout << "\t\tContrato finalizado y vehiculo devuelto. Espacio liberado.\n";
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

    //USO EXPLiCITO DE cin >>
    while (!(cin >> opcion) || opcion < min || opcion > max) {
        cin.clear();
        cin.ignore(10000, '\n'); // Limpieza del buffer
        cout << "\t\tOpcion invalida. Ingrese un numero entre [" << min << "] y [" << max << "]: ";
    }
    cin.ignore(10000, '\n'); // Limpieza del buffer
    return opcion;
}

void Utilidades::liberarMemoria() {
    cout << "\n\t\tLiberando memoria antes de salir..." << endl;

    // ---------------------------
    // 1. Eliminar Contratos
    // ---------------------------
    if (listaContratos != NULL) {
        NodoContrato* actualC = listaContratos->getCab();
        while (actualC != NULL) {
            NodoContrato* temp = actualC;
            actualC = actualC->getSiguiente();
            delete temp->getDato(); // ContratoAlquiler*
            delete temp;
        }
        delete listaContratos;
        listaContratos = NULL;
    }

    // ---------------------------
    // 2. Eliminar Solicitudes
    // ---------------------------
    if (listaSolicitudes != NULL) {
        NodoSolicitud* actualS = listaSolicitudes->getCab();
        while (actualS != NULL) {
            NodoSolicitud* temp = actualS;
            actualS = actualS->getSiguiente();
            delete temp->getDato(); // SolicitudAlquiler*
            delete temp;
        }
        delete listaSolicitudes;
        listaSolicitudes = NULL;
    }

    // ---------------------------
    // 3. Eliminar Clientes
    // ---------------------------
    if (listaClientes != NULL) {
        NodoCliente* actualCli = listaClientes->getCab();
        while (actualCli != NULL) {
            NodoCliente* temp = actualCli;
            actualCli = actualCli->getSiguiente();
            delete temp->getDato(); // Cliente*
            delete temp;
        }
        delete listaClientes;
        listaClientes = NULL;
    }

    // ---------------------------
    // 4. Eliminar Colaboradores
    // ---------------------------
    if (listaColaboradores != NULL) {
        NodoColaborador* actualCol = listaColaboradores->getCab();
        while (actualCol != NULL) {
            NodoColaborador* temp = actualCol;
            actualCol = actualCol->getSiguiente();
            delete temp->getDato(); // Colaborador*
            delete temp;
        }
        delete listaColaboradores;
        listaColaboradores = NULL;
    }

    // ---------------------------
    // 5. Eliminar Sucursales (y todo su contenido interno)
    // ---------------------------
    if (listaSucursales != NULL) {
        NodoSucursal* actualSuc = listaSucursales->getCab();
        while (actualSuc != NULL) {
            Sucursal* suc = actualSuc->getDato();
            if (suc != NULL) {
                suc->liberarRecursosInternos(); // metodo explicado abajo
                delete suc;
            }
            NodoSucursal* temp = actualSuc;
            actualSuc = actualSuc->getSiguiente();
            delete temp;
        }
        delete listaSucursales;
        listaSucursales = NULL;
    }

    cout << "\t\tMemoria liberada correctamente.\n";
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
            Utilidades::mostrarSubmenuSucursales();
            break;
        case 2:
            // Llama al submenu de Colaboradores
            Utilidades::mostrarSubmenuColaboradores();
            break;
        case 3:
            // Llama al submenu de Carros y Planteles
            Utilidades::mostrarSubmenuCarrosPlanteles();
            break;
        case 4:
            // Llama al submenu de Solicitudes y Contratos
            Utilidades::mostrarSubmenuSolicitudesContratos();
            break;
        case 5:
            // Llama al submenu de Clientes
            Utilidades::mostrarSubmenuClientes();
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
            Utilidades::ingresarSucursal();
            break;
        case 2:
            cout << "\n\t\t>> Ejecutando: Mostrar Sucursales..." << endl;
            Utilidades::mostrarSucursales();
            break;
        case 3:
            cout << "\n\t\t>> Ejecutando: Eliminar Sucursal..." << endl;
            Utilidades::eliminarSucursal();
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
            Utilidades::gestionarColaboradoresPorSucursal(1);
            break;
        case 2:
            cout << "\n\t\t>> Ejecutando: Mostrar Colaborador..." << endl;
            Utilidades::gestionarColaboradoresPorSucursal(2);
            break;
        case 3:
            cout << "\n\t\t>> Ejecutando: Eliminar Colaborador..." << endl;
            Utilidades::gestionarColaboradoresPorSucursal(3);
            break;
        case 4:
            cout << "\n\t\t>> Ejecutando: Reporte de Alquileres..." << endl;
            Utilidades::reporteAlquileresPorColaborador();
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
            {
                string placa;
                cout << "\t\tIngrese placa del vehiculo a visualizar: ";
                getline(cin, placa);
                Utilidades::mostrarInformacionVehiculoGlobal(placa);
            }
            break;
        case 5:
            cout << "\n\t\t>> Ejecutando: Eliminacion de Vehiculo..." << endl;
            Utilidades::EliminarVehiculo();
            break;

        case 6:
            cout << "\n\t\t>> Ejecutando: Reasignacion de Vehiculo en Plantel..." << endl;
            Utilidades::reubicarVehiculoSucursal();
            break;
        case 7:
            cout << "\n\t\t>> Ejecutando: Cambio de Estado de Vehiculo..." << endl;
            Utilidades::cambiarEstadoVehiculo();
            break;
        case 8:
            cout << "\n\t\t>> Ejecutando: Estados de un Vehiculo especifico..." << endl;
            {
                string placa;
                cout << "\t\tIngrese placa del vehiculo: ";
                getline(cin, placa);
                Utilidades::mostrarInformacionVehiculoGlobal(placa);
            }
            break;
        case 9:
            cout << "\n\t\t>> Ejecutando: Reportaje de porcentaje de ocupacion de los planteles..." << endl;
            Utilidades::reporteOcupacionPlanteles();
            break;
        case 10:
            cout << "\n\t\t>> Ejecutando: Traslado de Vehiculos a Plantel (OPTATIVO)..." << endl;
            Utilidades::trasladarVehiculos();
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
            Utilidades::CrearSolicitud();
            break;
        case 2:
            cout << "\n\t\t>> Ejecutando: Visualizacion de solicitudes/contratos por sucursal..." << endl;
            Utilidades::VerSolicitudesContratos();
            break;
        case 3:
            cout << "\n\t\t>> Ejecutando: Visualizacion de solicitud/contratos especifica..." << endl;
            {
                string placa;
                cout << "\t\tIngrese placa del vehiculo: ";
                getline(cin, placa);
                Utilidades::mostrarInformacionVehiculoGlobal(placa);
            }
            break;
        case 4:
            cout << "\n\t\t>> Ejecutando: Aprobacion/rechazo de solicitud..." << endl;
            Utilidades::AprobarRechazarSolicitud();
            break;
        case 5:
            cout << "\n\t\t>> Ejecutando: Recepcion de vehiculo en prestado ..." << endl;
            // llamar a funcion RecibirVehiPrestado();
            Utilidades::RecepcionVehiculo();
            break;
        case 6:
            cout << "\n\t\t>> Ejecutando: Reporte de contratos para vehiculos especifico..." << endl;
            Utilidades::reporteContratosPorVehiculo();
            break;
        case 7:
            cout << "\n\t\t>> Ejecutando: Visualizacion de todas las solicitudes / contratos..." << endl;
            Utilidades::VerSolicitudesContratos();
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
            Utilidades::gestionarClientesPorSucursal(1);
            break;
        case 2:
            cout << "\n\t\t>> Ejecutando: Mostrar Cliente..." << endl;
            Utilidades::gestionarClientesPorSucursal(2);
            break;
        case 3:
            cout << "\n\t\t>> Ejecutando: Eliminar Cliente..." << endl;
            Utilidades::gestionarClientesPorSucursal(3);
            break;
        case 4:
            cout << "\n\t\t>> Ejecutando: Historial del Cliente..." << endl;
            Utilidades::reporteHistorialCliente();
            break;
        case 5:
            cout << "\n\t\t>> Ejecutando: Reporte de clientes..." << endl;
            Utilidades::reporteClientesPorContratos();
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