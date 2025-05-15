#include <iostream>
#include <thread>

#include <algorithm>
using namespace std;

const int N = 3;
bool S[N] = {false, false, false}; // Indicador de si el proceso está tomando turno
int nt[N] = {0, 0, 0};             // Turnos de los procesos


int ntmax() {
    int maximo = 0;
    for (int i = 0; i < N; i++) {
        maximo = max(maximo, nt[i]); //se obtiene el valor de tiket maximo entre los 3 procesos
    }
    return maximo;
}

// Función para determinar prioridad entre turnos
bool ntmayorque(int i, int j) {
    if (nt[i] < nt[j]) return true;
    if (nt[i] == nt[j] && i < j) return true;
    return false;
}

// Proceso i (0, 1 o 2)
void proceso(int i) {
    // Entrada al algoritmo de Lamport
    S[i] = true;
    nt[i] = 1 + ntmax();  // Toma un turno
    S[i] = false;

    // Espera activa por su turno
    for (int j = 0; j < N; j++) {
        if (j == i) continue;

        while (S[j]) { // Espera a que el proceso anterior obtenga un turno, sino continua llamandose
            
        }

        while (nt[j] != 0 && !ntmayorque(i, j)) { // Espera a que su turno sea el más prioritario
             
        }
    }

    
    cout << "Seccion Critica del proceso [" << i << "]" << endl;
    

    
    nt[i] = 0; // Salida de sección crítica
}

int main() {
    // Lanzar tres hilos que representan los procesos
    thread p1(proceso, 0);
    thread p2(proceso, 1);
    thread p3(proceso, 2);

    p1.join();
    p2.join();
    p3.join();

    return 0;
}