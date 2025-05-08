#include <iostream>
#include <thread>

using namespace std;
bool s1 = false;
bool s2 = false;
int turno = 2;
int suma = 0;

void P1() {
    while (true) {
        s1 = true;
        while (s2 == true) {
            if (turno == 2) {
                s1 = false;
                while (turno == 2);
                s1 = true;
            }
        }
        cout << "El proceso 1 se encuentra en su SC" << endl;
        suma = suma + 2;
        cout << "la suma total es: " << suma << endl;
        turno = 2;
        s1 = false;
    }
}

void P2() {
    while (true) {
        s2 = true;
        while (s1 == true) {
            if (turno == 1) {
                s2 = false;
                while (turno == 1);
                s2 = true;
            }
        }
        cout << "El proceso 2 se encuentra en su SC" << endl;
        suma = suma - 1;
        cout << "la suma total es: " << suma << endl;
        turno = 1;
        s2 = false;
    }
}

int main() {
    s1 = false;
    s2 = false;
    turno = 2;
    suma = 0;

    thread P_1(P1);
    thread P_2(P2);

    P_1.join();
    P_2.join();

    return 0;
}