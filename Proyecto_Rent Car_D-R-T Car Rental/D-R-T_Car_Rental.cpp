#include <iostream>
#include "Vehiculo.h";//vehiculo.h anadido para pruebas.
using namespace std;
int main() {
    cout << "EEEEEE" << endl;
    cout << "madre mia willy" << endl;
    cout << "peroquehacesaquicompañero" << endl;

    //prueba de clase vehiculo.
    char x;
    Vehiculo* n = new Vehiculo();
    cout << "Categorias: " << endl;
    cout << "A, B, C, D" << endl;
    cin >> x;
    n->setCategoria(x);
    delete n;
    return 0;
}
