 
#include <iostream>
#include <iomanip>
#include <string>
#include <climits>
 
using namespace std;
 
const int NUM_ALMACENES = 6;
const int NUM_PRODUCTOS  = 15;
 
class Almacen {
private:
    int    stock[NUM_ALMACENES][NUM_PRODUCTOS]; 
    string nombresProductos[NUM_PRODUCTOS];     
    string nombresAlmacenes[NUM_ALMACENES];     
    int    umbralMinimo;                        
 
public:
    Almacen() : umbralMinimo(10) {
   
        for (int i = 0; i < NUM_ALMACENES; i++)
            for (int j = 0; j < NUM_PRODUCTOS; j++)
                stock[i][j] = 0;
 
       
        for (int i = 0; i < NUM_ALMACENES; i++)
            nombresAlmacenes[i] = "Almacen " + to_string(i + 1);
 
     
        for (int j = 0; j < NUM_PRODUCTOS; j++)
            nombresProductos[j] = "Producto " + to_string(j + 1);
    }
 

    void registrarExistencias() {
        int almacen, producto, cantidad;
 

        cout << ">>>>> REGISTRAR EXISTENCIAS <<<<<" << endl;
  
        cout << "  Almacén  (1-" << NUM_ALMACENES << "): ";
        cin  >> almacen;
        cout << "  Producto (1-" << NUM_PRODUCTOS  << "): ";
        cin  >> producto;
 
  
        if (almacen  < 1 || almacen  > NUM_ALMACENES ||
            producto < 1 || producto > NUM_PRODUCTOS) {
            cout << "\n  [!] Número fuera de rango. Intente de nuevo." << endl;
            return;
        }
 
        cout << "  Cantidad en stock: ";
        cin  >> cantidad;
 
        if (cantidad < 0) {
            cout << "\n  [!] La cantidad no puede ser negativa." << endl;
            return;
        }
 
        stock[almacen - 1][producto - 1] = cantidad;
        cout << "\n  Stock actualizado: "
             << nombresAlmacenes[almacen - 1] << " | "
             << nombresProductos[producto - 1]
             << " = " << cantidad << " unidades." << endl;
    }
 

    void detectarAgotados() {
   
        cout <<">>>>> PRODUCTOS AGOTADOS POR SUCURSAL <<<<<" << endl;
  
 
        bool hayAgotados = false;
 
        for (int i = 0; i < NUM_ALMACENES; i++) {
            bool cabeceraMostrada = false;
            for (int j = 0; j < NUM_PRODUCTOS; j++) {
                if (stock[i][j] == 0) {
                    if (!cabeceraMostrada) {
                        cout << "\n  " << nombresAlmacenes[i] << ":" << endl;
                        cabeceraMostrada = true;
                        hayAgotados = true;
                    }
                    cout << "    - " << nombresProductos[j]
                         << " [AGOTADO]" << endl;
                }
            }
        }
 
        if (!hayAgotados)
            cout << "\n Ningún producto agotado en este momento." << endl;
    }
 

    void almacenMenorStock() {
    
        cout << ">>>>> ALMACÉN CON MENOR STOCK TOTAL <<<<<" << endl;
   
        int menorTotal = INT_MAX;
        int indiceMenor = 0;
 
        for (int i = 0; i < NUM_ALMACENES; i++) {
            int totalAlmacen = 0;
            for (int j = 0; j < NUM_PRODUCTOS; j++)
                totalAlmacen += stock[i][j];
 
            cout << "  " << left << setw(14) << nombresAlmacenes[i]
                 << " -> Total: " << totalAlmacen << " unidades" << endl;
 
            if (totalAlmacen < menorTotal) {
                menorTotal  = totalAlmacen;
                indiceMenor = i;
            }
        }
 
        cout << "\n  ★  Menor stock: " << nombresAlmacenes[indiceMenor]
             << " con " << menorTotal << " unidades en total." << endl;
    }
 

    void emitirAlertas() {
        cout << "\n┌─────────────────────────────────────────┐" << endl;
        cout << "│         ALERTAS DE STOCK BAJO           │" << endl;
        cout << "│   (Umbral actual: " << setw(3) << umbralMinimo
             << " unidades)          │" << endl;
        cout << "└─────────────────────────────────────────┘" << endl;
 
        bool hayAlertas = false;
 
        for (int i = 0; i < NUM_ALMACENES; i++) {
            for (int j = 0; j < NUM_PRODUCTOS; j++) {

                if (stock[i][j] > 0 && stock[i][j] < umbralMinimo) {
                    cout << "  ⚠  " << nombresAlmacenes[i]
                         << " | " << left << setw(12) << nombresProductos[j]
                         << " -> " << stock[i][j] << " unidades" << endl;
                    hayAlertas = true;
                }
            }
        }
 
        if (!hayAlertas)
            cout << "\n Sin alertas. Todo el stock está sobre el umbral." << endl;
    }
 
};
 

int main() {
    Almacen sistema;
    int opcion;
 
    cout << "==========================================" << endl;
    cout << "  SISTEMA DE INVENTARIO MULTI-SUCURSAL   " << endl;
    cout << "  " << NUM_ALMACENES << " almacenes | "
         << NUM_PRODUCTOS << " productos por almacén  " << endl;
    cout << "==========================================" << endl;
 
    do {
        cout << "\n  MENÚ PRINCIPAL" << endl;
        cout << "  ─────────────────────────────────────" << endl;
        cout << "  1. Registrar existencias" << endl;
        cout << "  2. Ver productos agotados por sucursal" << endl;
        cout << "  3. Almacén con menor stock total" << endl;
        cout << "  4. Emitir alertas de stock bajo" << endl;
        cout << "  5. Salir" << endl;
        cout << "  ─────────────────────────────────────" << endl;
        cout << "  Opción: ";
        cin  >> opcion;
 
        switch (opcion) {
            case 1: sistema.registrarExistencias(); break;
            case 2: sistema.detectarAgotados();     break;
            case 3: sistema.almacenMenorStock();    break;
            case 4: sistema.emitirAlertas();        break;
            case 5: cout << "\n  Saliendo del sistema. ¡Hasta luego!\n" << endl; break;
            default: cout << "\n  [!] Opción no válida." << endl;
        }
 
    } while (opcion != 5);
 
    return 0;
}
 
/*
 *EXPLICACIÓN PASO A PASO:
 *
 * 1. MATRIZ BIDIMENSIONAL (stock[6][15])
 *    Es el núcleo del programa. Cada fila representa un almacén y cada columna
 *    un producto. stock[i][j] = cantidad disponible del producto j en almacén i.
 *
 * 2. INCISO A — Registrar existencias
 *    El usuario elige almacén (1-6) y producto (1-15), se valida el rango y
 *    se asigna directamente en stock[almacen-1][producto-1].
 *
 * 3. INCISO B — Productos agotados
 *    Se recorre toda la matriz. Si stock[i][j] == 0, ese producto está agotado
 *    en esa sucursal y se reporta al usuario.
 *
 * 4. INCISO C — Almacén con menor stock total
 *    Se suma cada fila completa (todos los productos de un almacén) y se
 *    compara con INT_MAX para encontrar el mínimo acumulado.
 *
 * 5. INCISO D — Alertas por umbral
 *    Se compara stock[i][j] contra umbralMinimo (fijo en 10). Solo se alerta
 *    si el valor es mayor a 0 (no agotado) pero menor al umbral definido.
 *
 * 6. ENCAPSULAMIENTO
 *    Toda la lógica y los datos viven dentro de la clase Almacen. Los atributos
 *    son privados y solo accesibles mediante los métodos públicos, cumpliendo
 *    el principio de encapsulamiento de la POO.
 *
 */