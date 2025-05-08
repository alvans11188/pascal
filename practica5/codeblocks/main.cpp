#include <iostream>
#include <thread>

using namespace std;

bool s1 = false, s2 = false; // inicianlizandolas porsiacaso no toman el valor de falso

void P1() {
    while (true) {
        while (s2 == true) {

        }
        s1 = true;

        cout << "Proceso 1 en su seccion critica" << endl;
        s1 = false;
    }
}

void P2() {
    while (true) {
        while (s1 == true) {

        }
        s2 = true;

        cout << "Proceso 2 en su seccion critica" << endl;
        s2 = false;
    }
}

int main() {
    thread P_1(P1);
    thread P_2(P2);

    P_1.join();
    P_2.join();

    return 0;
}
