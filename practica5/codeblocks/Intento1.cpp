#include <iostream>
#include <thread>
#include <string>

using namespace std;

int estado;

void P1() {
    while(true) {
        while(estado == 0) {
            estado = 0;
            cout << "Proceso 1 esta en su seccion critica" << endl;
            estado = 1;
                    }
    }
}

void P2() {
    while(true) {
        while(estado == 0) {
            estado = 0;
            cout << "Proceso 2 esta en su seccion critica" << endl;
            estado = 1;
            }
        }
}

int main()
{
thread P_1(P1);
thread P_2(P2);

P_1.join();
P_2.join();
return 0;
}