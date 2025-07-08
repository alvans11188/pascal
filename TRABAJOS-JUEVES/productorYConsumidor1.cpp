#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <random>
#include <chrono>

const int N = 10;
using namespace std;
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
        unique_lock<mutex> lock(mtx);
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
    mutex mtx;
    condition_variable clleno, cvacio;
};

Buffer buffer;

void productor() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 9);

    while (true) {
        int y = dis(gen);
        buffer.insertar(y);
        cout << "El productor produce: " << y << endl;
    }
}

void consumidor() {
    while (true) {
        int a;
        buffer.extraer(a);
        // cout << a << endl;
        cout << "El consumidor consume: " << a << endl;
    }
}

int main() {
    thread t1(productor);
    thread t2(consumidor);

    t1.join();
    t2.join();

    return 0;
}