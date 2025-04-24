#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

using namespace std;

double sum1 = 0;
double sum2 = 0;

struct myclass {
    bool operator()(int i, int j) { return (i < j); }
} myobject;

vector<int> myvector;

void task1() {
    cout << "Task1 iniciando...\n";
    double c = 0;
    while (c < 10) { c++; sum1 += c; }
    cout << "Task1 finalizando.\n";
}

void task2() {
    cout << "Task2 iniciando...\n";
    double c = 0;
    while (c < 5) { c++; sum2 += c; }
    cout << "Task2 finalizando.\n";
}

void task3() {
    cout << "Task3 iniciando...\n";
    myvector = {12, 33, 22, 44, 15, 66, 56, 39, 72};
    sort(myvector.begin(), myvector.end(), myobject);
    cout << "Task3 finalizando.\n";
}

int main() {
    // Creación de hilos
    thread t1(task1);
    thread t2(task2);
    thread t3(task3);

    // Obtención de IDs de hilos (corregido)
    thread::id id1 = t1.get_id();
    thread::id id2 = t2.get_id();  // Corregido: era t3.get_id() en la imagen
    thread::id id3 = t3.get_id();

    // Manejo de hilos con verificación joinable()
    if (t1.joinable()) {
        t1.join();
        cout << "t1 id = " << id1 << "\n";  // Corregido: %A -> t1
    }

    if (t2.joinable()) {
        t2.join();
        cout << "t2 id = " << id2 << "\n";
    }

    if (t3.joinable()) {
        t3.join();
        cout << "t3 id = " << id3 << "\n";

        // Mostrar vector ordenado
        for (int c = 0; c < myvector.size(); c++) {
            cout << "vector [" << c << "]: " << myvector[c] << "\n";  // Corregido: () -> []
        }
    }

    // Resultados finales
    cout << "sum1: " << sum1 << ", sum2: " << sum2 << "\n";  // Corregido: sumA -> sum1
    return 0;
}
