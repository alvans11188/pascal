#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

const int N = 5;
const int PENSANDO = 0;
const int COMIENDO = 1;

class ComidaFilosofos {
public:
    void cogerPalillos(int id_filosofo);
    void soltarPalillos(int id_filosofo);
    void procesarMensajes();

private:
    mutex mtx;
    condition_variable cv_filosofos[N];
    condition_variable cv_coordinador;
    queue<int> mensajes;
    int estado[N] = {PENSANDO, PENSANDO, PENSANDO, PENSANDO, PENSANDO};
    bool mensaje_disponible = false;
    
    void verificarDisponibilidad(int id_filosofo);
};

void ComidaFilosofos::verificarDisponibilidad(int id_filosofo) {
    int izquierda = (id_filosofo + N - 1) % N;
    int derecha = (id_filosofo + 1) % N;
    
    if (estado[id_filosofo] == PENSANDO && 
        estado[izquierda] != COMIENDO && 
        estado[derecha] != COMIENDO) {
        estado[id_filosofo] = COMIENDO;
        cv_filosofos[id_filosofo].notify_one();
    }
}

void ComidaFilosofos::cogerPalillos(int id_filosofo) {
    unique_lock<mutex> lock(mtx);
    
    mensajes.push(id_filosofo);
    mensaje_disponible = true;
    cv_coordinador.notify_one();
    
    cv_filosofos[id_filosofo].wait(lock, [this, id_filosofo] {
        return estado[id_filosofo] == COMIENDO;
    });
}

void ComidaFilosofos::soltarPalillos(int id_filosofo) {
    unique_lock<mutex> lock(mtx);
    
    estado[id_filosofo] = PENSANDO;
    cout << "Filosofo " << id_filosofo + 1 << " solto los palillos." << endl;
    
    int izquierda = (id_filosofo + N - 1) % N;
    int derecha = (id_filosofo + 1) % N;
    
    mensajes.push(izquierda);
    mensajes.push(derecha);
    mensaje_disponible = true;
    cv_coordinador.notify_one();
}

void ComidaFilosofos::procesarMensajes() {
    unique_lock<mutex> lock(mtx);
    
    if (!mensaje_disponible) {
        cv_coordinador.wait(lock, [this] { return mensaje_disponible; });
    }
    
    while (!mensajes.empty()) {
        int id_filosofo = mensajes.front();
        mensajes.pop();
        verificarDisponibilidad(id_filosofo);
    }
    
    mensaje_disponible = false;
}

ComidaFilosofos cf;

void coordinador() {
    while (true) {
        cf.procesarMensajes();
    }
}

void filosofo(int id) {
    while (true) {
        cout << "Filosofo " << id + 1 << " esta pensando." << endl;
        this_thread::sleep_for(chrono::milliseconds(500));

        cf.cogerPalillos(id);
        cout << "Filosofo " << id + 1 << " esta comiendo." << endl;
        this_thread::sleep_for(chrono::milliseconds(500));

        cf.soltarPalillos(id);
    }
}

int main() {
    thread hilo_coordinador(coordinador);
    
    thread filosofos[N];
    for (int i = 0; i < N; i++) {
        filosofos[i] = thread(filosofo, i);
    }

    hilo_coordinador.join();
    for (int i = 0; i < N; i++) {
        filosofos[i].join();
    }

    return 0;
}