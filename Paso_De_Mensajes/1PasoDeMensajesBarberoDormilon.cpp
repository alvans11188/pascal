#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

class BarberoDormilon {
public:
    void cortar_pelo(int id_cliente);
    void siguiente_cliente();

private:
    mutex mtx;
    condition_variable cv_barbero;
    condition_variable cv_cliente;
    queue<int> clientes_esperando;
    bool barbero_ocupado = false;
    bool mensaje_disponible = false;
};

void BarberoDormilon::cortar_pelo(int id_cliente) {
    unique_lock<mutex> lock(mtx);
    

    clientes_esperando.push(id_cliente);
    mensaje_disponible = true;
    cv_barbero.notify_one();
    
    cout << "Cliente " << id_cliente << " espera su turno." << endl;
    

    cv_cliente.wait(lock, [this, id_cliente] {
        return !barbero_ocupado && clientes_esperando.front() == id_cliente;
    });
    

    barbero_ocupado = true;
    cout << "Barbero cortando pelo al cliente " << id_cliente << endl;
    
    // Simular tiempo de corte
    this_thread::sleep_for(chrono::seconds(1));
    
    cout << "Barbero terminó con cliente " << id_cliente << endl;
    barbero_ocupado = false;
    
    
    clientes_esperando.pop();
    if (!clientes_esperando.empty()) {
        mensaje_disponible = true;
        cv_barbero.notify_one();
    }
}

void BarberoDormilon::siguiente_cliente() {
    unique_lock<mutex> lock(mtx);
    
    while (true) {
        if (!mensaje_disponible) {
            cout << "Barbero durmiendo..." << endl;
            cv_barbero.wait(lock, [this] { return mensaje_disponible; });
        }
        
        if (!clientes_esperando.empty()) {
            int cliente_actual = clientes_esperando.front();
            cout << "Barbero llama al cliente " << cliente_actual << endl;
            
            
            mensaje_disponible = false;
            cv_cliente.notify_one();
            
           
            cv_barbero.wait(lock, [this] { return !barbero_ocupado; });
        } else {
            mensaje_disponible = false;
        }
    }
}

BarberoDormilon bd;

void cliente(int id) {
    while (true) {
        bd.cortar_pelo(id);
        // Simular tiempo entre visitas al barbero
        this_thread::sleep_for(chrono::seconds(3));
    }
}

void barbero() {
    bd.siguiente_cliente();
}

int main() {
    thread hilo_barbero(barbero);

    thread hilos_clientes[3];  
    for (int i = 0; i < 3; i++) {
        hilos_clientes[i] = thread(cliente, i + 1);
    }

    hilo_barbero.join();
    for (int i = 0; i < 3; i++) {
        hilos_clientes[i].join();
    }

    return 0;
}