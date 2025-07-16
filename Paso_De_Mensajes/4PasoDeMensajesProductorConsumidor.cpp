#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>

using namespace std;

class BufferMensajes {
public:
    BufferMensajes(int capacidad) : capacidad_(capacidad) {}

    void producirComponente(int proveedor, int componente) {
        unique_lock<mutex> lock(mtx_);
        
        
        cv_prod_.wait(lock, [this] { return buffer_.size() < capacidad_; });
        
      
        buffer_.push(componente);
        cout << "Proveedor " << proveedor << " produce: " << componente << endl;
        
        
        cv_cons_.notify_one();
    }

    int consumirComponente(int cliente) {
        unique_lock<mutex> lock(mtx_);
        
      
        cv_cons_.wait(lock, [this] { return !buffer_.empty(); });
        
      
        int componente = buffer_.front();
        buffer_.pop();
        cout << "Cliente " << cliente << " consume: " << componente << endl;
        
       
        cv_prod_.notify_one();
        
        return componente;
    }

private:
    queue<int> buffer_;
    int capacidad_;
    mutex mtx_;
    condition_variable cv_prod_;  
    condition_variable cv_cons_;  
};

void productor(BufferMensajes& buf, int n, int proveedor) {
    for (int i = 0; i < n; i++) {
        int componente = rand() % 100;  
        buf.producirComponente(proveedor, componente);
    }
}

void consumidor(BufferMensajes& buf, int n, int cliente) {
    for (int i = 0; i < n; i++) {
        buf.consumirComponente(cliente);
    }
}

int main() {
    const int CAPACIDAD = 10;
    const int NUM_PROVEEDORES = 3;
    const int NUM_CLIENTES = 2;
    const int ITEMS_POR_HILO = 5;

    BufferMensajes buffer(CAPACIDAD);

    vector<thread> proveedores;
    vector<thread> clientes;

    
    for (int i = 0; i < NUM_PROVEEDORES; i++) {
        proveedores.emplace_back(productor, ref(buffer), ITEMS_POR_HILO, i+1);
    }

    
    for (int i = 0; i < NUM_CLIENTES; i++) {
        clientes.emplace_back(consumidor, ref(buffer), ITEMS_POR_HILO * NUM_PROVEEDORES / NUM_CLIENTES, i+1);
    }

    
    for (auto& hilo : proveedores) hilo.join();
    for (auto& hilo : clientes) hilo.join();

    return 0;
}