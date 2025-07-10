#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

const int N = 5;

mutex mtx;
condition_variable cv_emisor, cv_traductor, cv_receptor;

queue<int> cola_emisor;
queue<int> cola_traductor;

bool emisor_listo = true;
bool traductor_listo = false;
bool receptor_listo = false;

void emisor() {
    for (int i = 1; i <= N; i++) {
        unique_lock<mutex> lock(mtx);
        cv_emisor.wait(lock, [] { return emisor_listo; });

        cola_emisor.push(i);
        cout << "Emisor emitio: " << i << endl;

        emisor_listo = false;
        traductor_listo = true;

        lock.unlock();
        cv_traductor.notify_one();
    }
}

void traductor() {
    for (int i = 1; i <= N; i++) {
        unique_lock<mutex> lock(mtx);
        cv_traductor.wait(lock, [] { return traductor_listo; });

        int valor = cola_emisor.front();
        cola_emisor.pop();
        int traducido = valor * 10;

        cola_traductor.push(traducido);
        cout << "Traductor proceso: " << valor << " a " << traducido << endl;

        traductor_listo = false;
        receptor_listo = true;

        lock.unlock();
        cv_receptor.notify_one();
    }
}

void receptor() {
    for (int i = 1; i <= N; i++) {
        unique_lock<mutex> lock(mtx);
        cv_receptor.wait(lock, [] { return receptor_listo; });

        int recibido = cola_traductor.front();
        cola_traductor.pop();

        cout << "Receptor recibio: " << recibido << endl;
        cout << "Emisor es notificado con recepcion, puede continuar o finalizar." << endl;

        receptor_listo = false;
        emisor_listo = true;

        lock.unlock();
        cv_emisor.notify_one();
    }
}

int main() {
    thread hilo_emisor(emisor);
    thread hilo_traductor(traductor);
    thread hilo_receptor(receptor);

    hilo_emisor.join();
    hilo_traductor.join();
    hilo_receptor.join();

    return 0;
}
