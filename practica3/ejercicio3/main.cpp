#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void independentThread() {
    cout << "Iniciando el hilo concurrente.\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout << "Finalizando del hilo concurrente.\n";
}

void threadCaller() {
    std::cout << "Iniciando a manejar el hilo.\n";
    std::thread t(independentThread);
    t.detach();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Finalizando de la maneja del hilo.\n";
}

int main() {
    threadCaller();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}
