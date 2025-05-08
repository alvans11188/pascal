#include <iostream>
#include <thread>
//el problema esque puede entrar en ciclos inficnitos
using namespace std;

int turno = 1; 

void P1() {
    while (true) {
        while (turno == 2) {
            
        }
        
        cout << "Proceso 1 en su seccion critica" << endl;
        turno = 2; 
    }
}

void P2() {
    while (true) {
        while (turno == 1) {
           
        }
        
        cout << "Proceso 2 en su seccion critica" << endl;
        turno = 1; // Le pasa el turno a P1
    }
}

int main() {
    thread P_1(P1);
    thread P_2(P2);

    P_1.join();
    P_2.join();

    return 0;
}
