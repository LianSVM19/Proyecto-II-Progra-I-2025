#include <iostream>
#include "Vehiculo.h";//vehiculo.h anadido para pruebas.
#include "Utilidades.h"
using namespace std;
int main() {
    cout << "EEEEEE" << endl;
    cout << "madre mia willy" << endl;
    cout << "peroquehacesaquicompa�ero" << endl;
    // 1. Crear una instancia de la clase Utilidades
    // Esto es el �nico punto de conexi�n con la clase.
    
    Utilidades miSistema;

    // 2. Llamar al m�todo principal que inicia la l�gica del men�
    miSistema.ejecutarSistema();


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
