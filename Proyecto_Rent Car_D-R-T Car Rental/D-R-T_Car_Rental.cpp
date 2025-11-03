//D-R-T_Car_Rental.cpp
#include <iostream>
#include "Utilidades.h"
using namespace std;
int main() {
    cout << "EEEEEEaaaaaaa" << endl;
    cout << "madre mia willy" << endl;
    cout << "peroquehacesaquicompa"<<char(164)<<"ero" << endl;
    // 1. Crear una instancia de la clase Utilidades
    // Esto es el único punto de conexión con la clase.
    
    Utilidades miSistema;

    // 2. Llamar al método principal que inicia la lógica del menú
    miSistema.ejecutarSistema();

    miSistema.liberarMemoria();
    //prueba de clase vehiculo.
    
    
    /*char x;
    Vehiculo* n = new Vehiculo(); //este constructor esta malo pero aja.
    cout << "Categorias: " << endl;
    cout << "A, B, C, D" << endl;
    cin >> x;
    n->setCategoria(x);
    delete n;*/
    return 0;
}
