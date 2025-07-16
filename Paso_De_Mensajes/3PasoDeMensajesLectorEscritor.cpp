#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>

using namespace std;

class LectoresEscritores {
public:
    void solicitarLectura();
    void finalizarLectura();
    void solicitarEscritura();
    void finalizarEscritura();
    void procesarMensajes();

private:
    mutex mtx;
    condition_variable cv_lector;
    condition_variable cv_escritor;
    condition_variable cv_coordinador;
    
    queue<string> mensajes; // "LEER" o "ESCRIBIR" o "TERMINAR_LECTURA" o "TERMINAR_ESCRITURA"
    bool mensaje_disponible = false;
    
    int lectores_activos = 0;
    bool escritor_activo = false;
    int lectores_esperando = 0;
    int escritores_esperando = 0;
};

void LectoresEscritores::solicitarLectura() {
    unique_lock<mutex> lock(mtx);
    mensajes.push("LEER");
    mensaje_disponible = true;
    cv_coordinador.notify_one();
    
    // Esperar confirmación
    cv_lector.wait(lock, [this] { return !escritor_activo && escritores_esperando == 0; });
    lectores_activos++;
}

void LectoresEscritores::finalizarLectura() {
    unique_lock<mutex> lock(mtx);
    mensajes.push("TERMINAR_LECTURA");
    mensaje_disponible = true;
    cv_coordinador.notify_one();
}

void LectoresEscritores::solicitarEscritura() {
    unique_lock<mutex> lock(mtx);
    mensajes.push("ESCRIBIR");
    mensaje_disponible = true;
    cv_coordinador.notify_one();
    
    // Esperar confirmación
    cv_escritor.wait(lock, [this] { return lectores_activos == 0 && !escritor_activo; });
    escritor_activo = true;
}

void LectoresEscritores::finalizarEscritura() {
    unique_lock<mutex> lock(mtx);
    mensajes.push("TERMINAR_ESCRITURA");
    mensaje_disponible = true;
    cv_coordinador.notify_one();
}

void LectoresEscritores::procesarMensajes() {
    unique_lock<mutex> lock(mtx);
    
    while (true) {
        if (!mensaje_disponible) {
            cv_coordinador.wait(lock, [this] { return mensaje_disponible; });
        }
        
        while (!mensajes.empty()) {
            string mensaje = mensajes.front();
            mensajes.pop();
            
            if (mensaje == "LEER") {
                if (escritor_activo || escritores_esperando > 0) {
                    lectores_esperando++;
                } else {
                    lectores_activos++;
                    cv_lector.notify_one();
                }
            }
            else if (mensaje == "TERMINAR_LECTURA") {
                lectores_activos--;
                if (lectores_activos == 0 && escritores_esperando > 0) {
                    escritores_esperando--;
                    escritor_activo = true;
                    cv_escritor.notify_one();
                }
            }
            else if (mensaje == "ESCRIBIR") {
                if (lectores_activos > 0 || escritor_activo) {
                    escritores_esperando++;
                } else {
                    escritor_activo = true;
                    cv_escritor.notify_one();
                }
            }
            else if (mensaje == "TERMINAR_ESCRITURA") {
                escritor_activo = false;
                if (lectores_esperando > 0) {
                    // Dar prioridad a los lectores
                    lectores_activos = lectores_esperando;
                    lectores_esperando = 0;
                    cv_lector.notify_all();
                } else if (escritores_esperando > 0) {
                    escritores_esperando--;
                    escritor_activo = true;
                    cv_escritor.notify_one();
                }
            }
        }
        
        mensaje_disponible = false;
    }
}

LectoresEscritores le;

void lector() {
    while (true) {
        le.solicitarLectura();
        cout << "Leyendo..." << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
        le.finalizarLectura();
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void escritor() {
    while (true) {
        le.solicitarEscritura();
        cout << "Escribiendo..." << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        le.finalizarEscritura();
        this_thread::sleep_for(chrono::milliseconds(2000));
    }
}

void coordinador() {
    le.procesarMensajes();
}

int main() {
    thread hilo_coordinador(coordinador);
    
    thread lectores[3], escritores[3];
    
    for (int i = 0; i < 3; i++) {
        lectores[i] = thread(lector);
        escritores[i] = thread(escritor);
    }
    
    hilo_coordinador.join();
    for (int i = 0; i < 3; i++) {
        lectores[i].join();
        escritores[i].join();
    }
    
    return 0;
}