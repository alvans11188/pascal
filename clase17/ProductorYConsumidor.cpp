#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <random>
#include <chrono>

const int N = 10;

class Buffer {
public:
    Buffer() : tam(0), frente(0), final(0) {}

    void insertar(int elemento) {
        std::unique_lock<std::mutex> lock(mtx);
        while (tam == N) {
            clleno.wait(lock);
        }
        cola[final] = elemento;
        final = (final + 1) % N;
        tam++;
        cvacio.notify_one();
    }

    void extraer(int& x) {
        std::unique_lock<std::mutex> lock(mtx);
        while (tam == 0) {
            cvacio.wait(lock);
        }
        x = cola[frente];
        frente = (frente + 1) % N;
        tam--;
        clleno.notify_one();
    }

private:
    int tam, frente, final;
    int cola[N];
    std::mutex mtx;
    std::condition_variable clleno, cvacio;
};

Buffer buffer;

void productor() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);

    while (true) {
        int y = dis(gen);
        buffer.insertar(y);
        // std::cout << "El productor produce: " << y << std::endl;
    }
}

void consumidor() {
    while (true) {
        int a;
        buffer.extraer(a);
        // std::cout << a << std::endl;
        std::cout << "El consumidor consume: " << a << std::endl;
    }
}

int main() {
    std::thread t1(productor);
    std::thread t2(consumidor);

    t1.join();
    t2.join();

    return 0;
}
