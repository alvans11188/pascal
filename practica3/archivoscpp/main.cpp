#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <atomic>

using namespace std;
using namespace chrono;

// Variables compartidas
mutex mtx; // Para sincronizar salida
atomic<int> ejecuciones1(0), ejecuciones2(0), ejecuciones3(0);

// Función para mostrar tiempo formateado
void mostrarTiempo(const char* tarea, milliseconds tiempo) {
    int i;
    lock_guard<mutex> lock(mtx);
    cout << "Proceso 2 ejecución #" << ++ejecuciones2 << " (valor: " << i << ")\n";
}

// Proceso 1: Conteo ascendente
void proceso1() {
    auto inicio = high_resolution_clock::now();

    for (int i = 1; i <= 5; ++i) {
        {
            lock_guard<mutex> lock(mtx);
            cout << " Proceso 1 ejecucion #" << ++ejecuciones1 << " (valor: " << i << ")\n";
        }
        this_thread::sleep_for(milliseconds(300)); // Simular trabajo
    }

    auto fin = high_resolution_clock::now();
    mostrarTiempo("Proceso 1", duration_cast<milliseconds>(fin - inicio));
}

// Proceso 2: Conteo descendente
void proceso2() {
    auto inicio = high_resolution_clock::now();

    for (int i = 5; i >= 1; --i) {
        {
            lock_guard<mutex> lock(mtx);
            cout << " Proceso 2 ejecucion #" << ++ejecuciones2 << " (valor: " << i << ")\n";
        }
        this_thread::sleep_for(milliseconds(400)); // Simular trabajo
    }

    auto fin = high_resolution_clock::now();
    mostrarTiempo("Proceso 2", duration_cast<milliseconds>(fin - inicio));
}

// Proceso 3: Cálculo de cuadrados
void proceso3() {
    auto inicio = high_resolution_clock::now();

    for (int i = 1; i <= 5; ++i) {
        int cuadrado = i * i;
        {
            lock_guard<mutex> lock(mtx);
            cout << "Proceso 3 ejecucion #" << ++ejecuciones3 << " (" << i << "² = " << cuadrado << ")\n";
        }
        this_thread::sleep_for(milliseconds(200)); // Simular trabajo
    }

    auto fin = high_resolution_clock::now();
    mostrarTiempo("Proceso 3", duration_cast<milliseconds>(fin - inicio));
}

int main() {
    cout << "INICIANDO EJECUCIÓN CONCURRENTE\n";
    cout << "================================\n";

    // Crear hilos
    thread t1(proceso1);
    thread t2(proceso2);
    thread t3(proceso3);

    // Esperar a que terminen
    t1.join();
    t2.join();
    t3.join();

    // Resumen final
    cout << "\n RESUMEN FINAL:\n";
    cout << "--------------------------------\n";
    cout << "Total ejecuciones Proceso 1: " << ejecuciones1 << endl;
    cout << "Total ejecuciones Proceso 2: " << ejecuciones2 << endl;
    cout << "Total ejecuciones Proceso 3: " << ejecuciones3 << endl;
    cout << "================================\n";
    cout << " TODOS LOS PROCESOS HAN TERMINADO\n";

    return 0;
}
