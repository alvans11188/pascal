#include <iostream>
#include <omp.h>

using namespace std;

#define N 24

int main() {
    int tid, nthr;    
    int A[N];

    for (int i = 0; i < N; i++) {
        A[i] = 0;
    }

    // Sección paralela
    #pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        nthr = omp_get_num_threads();

        cout << "Thread " << tid << " de " << nthr << " en marcha" << endl;

        A[tid] = tid + 10;

        cout << "El thread " << tid << " ha terminado" << endl;
    }

    // Mostrar resultados
    for (int i = 0; i < N; i++) {
        cout << "A[" << i << "] = " << A[i] << endl;
    }

    return 0;
}