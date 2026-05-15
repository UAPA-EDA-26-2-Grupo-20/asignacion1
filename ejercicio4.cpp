#include <iostream>
#include <cstdlib>   // abs
#include <algorithm> // min
using namespace std;

// Funciones
bool necesita(int cantidad, int umbral);
int excedente(int cantidad, int umbral);

int main() {
    // Matrices y arreglos
    int stock[6][15];
    int distancia[6][6];
    int umbral[15];

    // Contadores
    int totalMovimientos = 0;
    int costoTotal = 0;

    // Llenar umbral
    for (int p = 0; p < 15; p++) {
        umbral[p] = 10;
    }

    // Llenar stock (datos de prueba)
    for (int i = 0; i < 6; i++) {
        for (int p = 0; p < 15; p++) {
            stock[i][p] = 5 + i * 5;
        }
    }

    // Llenar distancias
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            distancia[i][j] = abs(i - j) + 1;
        }
    }

    cout << "=== INICIO DEL PROGRAMA ===" << endl;

    // ALGORITMO PRINCIPAL
    for (int p = 0; p < 15; p++) {
        for (int i = 0; i < 6; i++) {

            // Si necesita producto
            if (necesita(stock[i][p], umbral[p])) {

                // Buscar quien tiene excedente
                for (int j = 0; j < 6; j++) {

                    if (excedente(stock[j][p], umbral[p]) > 0) {

                        int falta = umbral[p] - stock[i][p];
                        int sobra = stock[j][p] - umbral[p];

                        int mover = min(falta, sobra);
                        int costo = mover * distancia[j][i];

                        // Actualizar
                        stock[i][p] += mover;
                        stock[j][p] -= mover;

                        totalMovimientos++;
                        costoTotal += costo;

                        // Mostrar movimiento
                        cout << "Producto " << p
                             << ": " << mover
                             << " unidades movidas de Almacen " << j
                             << " a Almacen " << i
                             << ". Costo: " << costo << endl;

                        // Si ya no necesita más, salir
                        if (stock[i][p] >= umbral[p]) {
                            break;
                        }
                    }
                }
            }
        }
    }

    // Resultado final
    cout << "---------------------------" << endl;
    cout << "Total de movimientos: " << totalMovimientos << endl;
    cout << "Costo total: " << costoTotal << endl;

    return 0;
}

// Función necesita
bool necesita(int cantidad, int umbral) {
    return cantidad < umbral;
}

// Función excedente
int excedente(int cantidad, int umbral) {
    if (cantidad > umbral)
        return cantidad - umbral;
    return 0;
}