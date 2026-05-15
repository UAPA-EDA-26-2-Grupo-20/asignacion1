/*
TEMÁTICA: USO DE ARREGLOS UNIDIMENSIONALES Y BIDIMENSIONALES EN LA SOLUCIÓN DE PROBLEMAS.


El sistema de una aerolínea requiere la
distribución organizada de los asientos disponibles
en un vuelo.
Cada avión cuenta con 3 clases: primera, segunda
y tercera. Los porcentajes de asignación de
asientos son:
✓ 15% para 1ra clase
✓ 25% para 2da clase
✓ 60% para 3ra clase
A cada pasajero se le asigna una clase, un número
de asiento y se registra su nombre completo.
Se debe permitir:
a) Registrar la venta de boletos hasta
completar la capacidad del avión.
b) Mostrar cuántos asientos fueron vendidos
por clase.
c) Calcular el ingreso estimado por clase
según precios predefinidos.
El sistema se apoya en arreglos unidimensionales
de pasajeros por clase y estructura orientada a
objetos para avión y vuelo
*/


#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Clase para representar a cada pasajero
class Pasajero {
public:
    string nombreCompleto;
    int numeroAsiento;

    Pasajero(string nombre, int asiento) : nombreCompleto(nombre), numeroAsiento(asiento) {}
};

// Clase para gestionar el Vuelo
class Vuelo {
private:
    int capacidadTotal;
    double precio1ra, precio2da, precio3ra;
    
    // Arreglos unidimensionales para cada clase
    vector<Pasajero> clase1ra;
    vector<Pasajero> clase2da;
    vector<Pasajero> clase3ra;

    int limite1ra, limite2da, limite3ra;

public:
    Vuelo(int capacidad) : capacidadTotal(capacidad) {
        // Cálculo de límites según porcentajes
        limite1ra = capacidad * 0.15;
        limite2da = capacidad * 0.25;
        limite3ra = capacidad - (limite1ra + limite2da);

        // Precios predefinidos
        precio1ra = 500.0;
        precio2da = 300.0;
        precio3ra = 150.0;
    }

    void registrarVenta() {
        if (clase1ra.size() + clase2da.size() + clase3ra.size() >= capacidadTotal) {
            cout << "¡Vuelo completo! No hay más asientos disponibles." << endl;
            return;
        }

        string nombre;
        int opcion;
        cout << "\nNombre del pasajero: ";
        getline(cin >> ws, nombre);
        cout << "Elija clase (1: Primera, 2: Segunda, 3: Tercera): ";
        cin >> opcion;

        if (opcion == 1 && clase1ra.size() < limite1ra) {
            clase1ra.push_back(Pasajero(nombre, clase1ra.size() + 1));
            cout << "Asiento asignado en Primera Clase." << endl;
        } else if (opcion == 2 && clase2da.size() < limite2da) {
            clase2da.push_back(Pasajero(nombre, limite1ra + clase2da.size() + 1));
            cout << "Asiento asignado en Segunda Clase." << endl;
        } else if (opcion == 3 && clase3ra.size() < limite3ra) {
            clase3ra.push_back(Pasajero(nombre, limite1ra + limite2da + clase3ra.size() + 1));
            cout << "Asiento asignado en Tercera Clase." << endl;
        } else {
            cout << "Lo sentimos, esa clase está llena o la opción no es válida." << endl;
        }
    }

    void mostrarEstadisticas() {
        cout << "\n--- RESUMEN DE VENTAS ---" << endl;
        cout << "Primera Clase: " << clase1ra.size() << " asientos." << endl;
        cout << "Segunda Clase: " << clase2da.size() << " asientos." << endl;
        cout << "Tercera Clase: " << clase3ra.size() << " asientos." << endl;
    }

    void calcularIngresos() {
        double total1 = clase1ra.size() * precio1ra;
        double total2 = clase2da.size() * precio2da;
        double total3 = clase3ra.size() * precio3ra;

        cout << fixed << setprecision(2);
        cout << "\n--- INGRESOS ESTIMADOS ---" << endl;
        cout << "Primera Clase: $" << total1 << endl;
        cout << "Segunda Clase: $" << total2 << endl;
        cout << "Tercera Clase: $" << total3 << endl;
        cout << "TOTAL VUELO:   $" << (total1 + total2 + total3) << endl;
    }
};

int main() {
    int cap;
    cout << "Ingrese la capacidad total del avión: ";
    cin >> cap;

    Vuelo miVuelo(cap);
    int menu;

    do {
        cout << "\n1. Registrar Venta\n2. Ver Asientos Vendidos\n3. Ver Ingresos\n4. Salir\nOpción: ";
        cin >> menu;

        switch (menu) {
            case 1: miVuelo.registrarVenta(); break;
            case 2: miVuelo.mostrarEstadisticas(); break;
            case 3: miVuelo.calcularIngresos(); break;
        }
    } while (menu != 4);

    return 0;
}

Explicación paso a paso
1. Estructura de Arreglos (Vectores)

Aunque el problema pide arreglos unidimensionales, en C++ moderno se utilizan std::vector porque permiten manejar el tamaño de forma dinámica. En este código, cada clase del avión tiene su propio arreglo independiente:

    clase1ra: Almacena objetos de tipo Pasajero.

    clase2da y clase3ra: Gestionan sus respectivos sectores.

2. Lógica de Distribución

En el Constructor de la clase Vuelo, se realiza el cálculo de los límites de asientos basándose en los porcentajes dados:

    Primera (15%): capacidad * 0.15

    Segunda (25%): capacidad * 0.25

    Tercera (60%): El resto de los asientos.

3. Registro de Pasajeros (Inciso A)

La función registrarVenta() verifica dos cosas antes de agregar a alguien:

    Si el avión en general tiene espacio.

    Si la clase específica seleccionada tiene asientos disponibles (comparando el tamaño actual del arreglo con su límite).

4. Conteo y Acumulación (Incisos B y C)

    Conteo: Se utiliza el método .size() de cada arreglo para saber cuántos boletos se han vendido por categoría.

    Ingresos: Se multiplica la cantidad de elementos en cada arreglo por el precio constante definido para esa clase ($500, $300 o $150).

5. Abstracción y Encapsulamiento

El uso de clases permite que los datos sensibles (como los límites de asientos y los precios) estén protegidos (private), y que la interacción del usuario se haga a través de métodos públicos claros, manteniendo el código organizado y escalable.







