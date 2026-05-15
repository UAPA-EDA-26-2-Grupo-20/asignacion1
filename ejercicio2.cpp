#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Habitacion {
public:
    int numero;
    string tipo;
    double precio;
    bool ocupada;

    Habitacion() {
        numero = 0;
        tipo = "";
        precio = 0.0;
        ocupada = false;
    }

    Habitacion(int n, string t, double p) {
        numero = n;
        tipo = t;
        precio = p;
        ocupada = false;
    }
};

class Hotel {
private:
    Habitacion habitaciones[50];
    int total;
public:
    Hotel() {
        total = 0;
    }

    void registrarHabitacion() {
        if (total >= 50) {
            cout << "\nLimite alcanzado.\n";
            return;
        }
        int n;
        string t;
        double p;
        cout << "\nNumero de habitacion: ";
        cin >> n;
        cout << "Tipo (sencilla/doble/suite): ";
        cin >> t;
        cout << "Precio: ";
        cin >> p;

        habitaciones[total] = Habitacion(n, t, p);
        total++;
        cout << "Registrada.\n";
    }

    /* a) Registrar reservas (máximo 50 habitaciones) */
    void registrarReserva() {
        int numBuscado;
        bool encontrada = false;

        cout << "\nNumero de habitacion a reservar: ";
        cin >> numBuscado;

        for (int i = 0; i < total; i++) {
            if (habitaciones[i].numero == numBuscado) {
                encontrada = true;
                if (!habitaciones[i].ocupada) {
                    habitaciones[i].ocupada = true;
                    cout << "Reserva registrada correctamente.\n";
                } else {
                    cout << "La habitacion ya esta ocupada.\n";
                }
                return;
            }
        }
        if (!encontrada) cout << "La habitacion no existe.\n";
    }

    /* b) Calcular la ocupación total y el ingreso estimado */
    void ocupacionIngreso() {
        int ocupadas = 0;
        double ingreso = 0;

        for (int i = 0; i < total; i++) {
            if (habitaciones[i].ocupada) {
                ocupadas++;
                ingreso += habitaciones[i].precio;
            }
        }
        cout << "\nOcupadas: " << ocupadas << endl;
        cout << "Disponibles: " << (total - ocupadas) << endl;
        cout << "Ingreso estimado: $" << ingreso << endl;
    }

    /* c) Mostrar habitaciones disponibles por tipo */
    void disponiblesPorTipo() {
        string tipoBuscado;
        cout << "\nTipo a buscar: ";
        cin >> tipoBuscado;
        cout << "\nDisponibles tipo " << tipoBuscado << ":\n";
        for (int i = 0; i < total; i++) {
            if (habitaciones[i].tipo == tipoBuscado && !habitaciones[i].ocupada) {
                cout << "- #" << habitaciones[i].numero << endl;
            }
        }
    }

    /* d) Consultar habitación más cara disponible */
    void masCaraDisponible() {
        int pos = -1;
        double max = -1;

        for (int i = 0; i < total; i++) {
            if (!habitaciones[i].ocupada && habitaciones[i].precio > max) {
                max = habitaciones[i].precio;
                pos = i;
            }
        }

        if (pos != -1) {
            cout << "\nHabitacion mas cara disponible: #" << habitaciones[pos].numero
                << " ($" << habitaciones[pos].precio << ")\n";
        } else {
            cout << "\nNo hay habitaciones disponibles.\n";
        }
    }
};

 int main() {
    Hotel miHotel;
    int op;
    do {
        cout << "\n--- Hotel equipo Azul ---\n1. Registrar habitacion\n2. Registrar reserva\n3. Ocupacion total e ingreso\n4. Buscar Por Tipo\n5. habitacion mas cara\n0. Salir\nOpcion: ";

        if (!(cin >> op)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (op) {
            case 1: miHotel.registrarHabitacion(); break;
            case 2: miHotel.registrarReserva(); break;
            case 3: miHotel.ocupacionIngreso(); break;
            case 4: miHotel.disponiblesPorTipo(); break;
            case 5: miHotel.masCaraDisponible(); break;
        }
    } while (op != 0);

    return 0;
 }
